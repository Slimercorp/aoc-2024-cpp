#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>

void calculateRatingForTrail(const std::string &node,
                            const std::unordered_map<std::string, char> &nodes,
                            std::unordered_map<std::string, int> &ratings,
                            const std::unordered_map<std::string, std::vector<std::string> > &connections) {
    std::unordered_set<std::string> checkedPaths;
    std::deque<std::string> nodesToCheckDeque;
    nodesToCheckDeque.push_back(node);
    while (!nodesToCheckDeque.empty()) {
        nodesToCheckDeque.clear();
        nodesToCheckDeque.push_back(node);
        std::string path = node;
        while (!nodesToCheckDeque.empty()) {
            std::string checkNode = nodesToCheckDeque.front();
            path.append(checkNode);
            nodesToCheckDeque.pop_front();
            if (checkedPaths.find(path) == checkedPaths.end() && nodes.at(checkNode) == '9') {
                checkedPaths.insert(path);
                break;
            }

            if (connections.find(checkNode) != connections.end()) {
                for (const auto &neighboor: connections.at(checkNode)) {
                    nodesToCheckDeque.push_back(neighboor);
                }
            }
        }
    }

    ratings[node] = checkedPaths.size();
}

bool checkDirection(std::vector<std::string> &map, int x, int y, int dx, int dy, int maxX, int maxY) {
    int value = map[x][y] - '0';

    x += dx;
    y += dy;

    if (x < 0 || y < 0 || x >= maxX || y >= maxY) {
        return false;
    }

    int valueNeighbor = map[x][y] - '0';
    int diff = valueNeighbor - value;
    return diff == 1;
}

int main() {
    std::ifstream file("day 10/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    std::unordered_map<std::string, char> nodes;
    std::unordered_set<std::string> nodesToCheck;
    std::unordered_map<std::string, std::vector<std::string> > connections;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            std::string coord = std::to_string(i) + ";" + std::to_string(j);
            char value = map[i][j];
            nodes[coord] = map[i][j];
            if (value == '0') {
                nodesToCheck.insert(coord);
            }

            const std::vector<std::pair<int, int> > directions = {
                {0, 1}, // right
                {0, -1}, // left
                {-1, 0}, // up
                {1, 0}, // down
            };

            for (const auto &[dx, dy]: directions) {
                if (checkDirection(map, i, j, dx, dy, map.size(), map[i].size())) {
                    std::string coordNeighboor = std::to_string(i + dx) + ";" + std::to_string(j + dy);
                    connections[coord].push_back(coordNeighboor);
                }
            }
        }
    }

    std::unordered_map<std::string, int> ratings;
    for (const std::string &node: nodesToCheck) {
        calculateRatingForTrail(node, nodes, ratings, connections);
    }

    int generalRating = 0;
    for (const auto &[_, rating]: ratings) {
        generalRating += rating;
    }

    std::cout << generalRating << std::endl;

    return 0;
}
