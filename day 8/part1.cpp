#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>

void calculateAntinodes(std::unordered_set<std::string> &antinodes, char c, std::vector<std::string> &map, int x,
                        int y) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (i != x && j != y && c == map[i][j]) {
                int xDist = x - i; // 2 - 4
                int yDist = y - j; //6 - 5

                int antinode1X = x + xDist;// 0
                int antinode1Y = y + yDist; //7
                if (antinode1X >= 0 && antinode1X < map.size() && antinode1Y >= 0 && antinode1Y < map[0].size()) {
                    std::string coordinate = std::to_string(antinode1X) + ";" + std::to_string(antinode1Y);
                    antinodes.insert(coordinate);
                }

                int antinode2X = i - xDist; //6
                int antinode2Y = j - yDist; //4
                if (antinode2X >= 0 && antinode2X < map.size() && antinode2Y >= 0 && antinode2Y < map[0].size()) {
                    std::string coordinate = std::to_string(antinode2X) + ";" + std::to_string(antinode2Y);
                    antinodes.insert(coordinate);
                }
            }
        }
    }
}

int main() {
    std::ifstream file("day 8/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    std::unordered_set<std::string> antinodes;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            char c = map[i][j];
            if (c < '0' || c > 'z') {
                continue;
            }
            calculateAntinodes(antinodes, c, map, i, j);
        }
    }

    std::cout << antinodes.size() << std::endl;

    return 0;
}
