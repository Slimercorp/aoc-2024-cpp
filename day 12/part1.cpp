#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <regex>

const std::vector<std::pair<int, int> > directions = {
    {0, 1}, // right
    {0, -1}, // left
    {-1, 0}, // up
    {1, 0}, // down
};

std::string getStringCoord(int x, int y) {
    return std::to_string(x) + ";" + std::to_string(y);
}

void getCoordFromString(const std::string &str, int &x, int &y) {
    std::regex regex(R"((\d+);(\d+))");
    std::smatch match;
    if (std::regex_match(str, match, regex)) {
        x = std::stoi(match[1].str());
        y = std::stoi(match[2].str());
    }
}

bool checkNeighbor(const std::vector<std::string> &map, int x, int y, int maxX, int maxY, char value) {
    if (x < 0 || y < 0 || x >= maxX || y >= maxY) {
        return false;
    }
    return map[x][y] == value;
}

int getPerimeterForPlant(const std::vector<std::string> &map, int x, int y) {
    int perimeter = 0;

    for (const auto &[dx, dy]: directions) {
        if (!checkNeighbor(map, x + dx, y + dy, map.size(), map[x].size(), map[x][y])) {
            ++perimeter;
        }
    }
    return perimeter;
}

int getPriceForRegionStartsIn(int i,
                              int j,
                              const std::vector<std::string> &map,
                              std::vector<std::vector<bool> > &visited,
                              const std::unordered_map<std::string, std::vector<std::string> > &connections) {
    int area = 1;
    int perimeter = getPerimeterForPlant(map, i, j);
    visited[i][j] = true;
    std::string coordinate = getStringCoord(i, j);

    std::deque<std::string> plants;
    plants.push_back(coordinate);
    while (!plants.empty()) {
        std::string plant = plants.front();
        plants.pop_front();
        if (connections.find(plant) != connections.end()) {
            for (const auto &neighbor: connections.at(plant)) {
                int x, y;
                getCoordFromString(neighbor, x, y);
                if (!visited[x][y]) {
                    ++area;
                    perimeter += getPerimeterForPlant(map, x, y);
                    plants.push_back(neighbor);
                    visited[x][y] = true;
                }
            }
        }
    }
    return area * perimeter;
}

int main() {
    std::ifstream file("day 12/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    std::unordered_map<std::string, std::vector<std::string> > connections;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            std::string coord = getStringCoord(i, j);

            for (const auto &[dx, dy]: directions) {
                if (checkNeighbor(map, i + dx, j + dy, map.size(), map[i].size(), map[i][j])) {
                    std::string coordNeighboor = getStringCoord(i + dx, j + dy);
                    connections[coord].push_back(coordNeighboor);
                }
            }
        }
    }

    std::vector<std::vector<bool> > visited(map.size(), std::vector<bool>(map[0].size(), false));
    int totalPrice = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (!visited[i][j]) {
                totalPrice += getPriceForRegionStartsIn(i, j, map, visited, connections);
            }
        }
    }

    std::cout << totalPrice << std::endl;

    return 0;
}
