#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

void calculateAntinodes(std::unordered_map<std::string, int> &antinodes, char c, std::vector<std::string> &map, int x,
                        int y) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (i != x && j != y && c == map[i][j]) {
                int xDist = x - i; // 2 - 4
                int yDist = y - j; //6 - 5

                int antinode1X = x;
                int antinode1Y = y;
                while (true) {
                    antinode1X += xDist;// 0
                    antinode1Y += yDist; //7
                    if (antinode1X >= 0 && antinode1X < map.size() && antinode1Y >= 0 && antinode1Y < map[0].size()) {
                        std::string coordinate = std::to_string(antinode1X) + ";" + std::to_string(antinode1Y);
                        antinodes[coordinate]++;
                    } else {
                      break;
                    }
                }

                int antinode2X = i;
                int antinode2Y = j;
                while (true) {
                    antinode2X -= xDist; //6
                    antinode2Y -= yDist; //4
                    if (antinode2X >= 0 && antinode2X < map.size() && antinode2Y >= 0 && antinode2Y < map[0].size()) {
                        std::string coordinate = std::to_string(antinode2X) + ";" + std::to_string(antinode2Y);
                        antinodes[coordinate]++;
                    } else {
                        break;
                    }
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

    std::unordered_map<std::string, int> antinodes;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            char c = map[i][j];
            if (c < '0' || c > 'z') {
                continue;
            }
            std::string coordinate = std::to_string(i) + ";" + std::to_string(j);
            antinodes[coordinate]++;
            calculateAntinodes(antinodes, c, map, i, j);
        }
    }

    int counter = 0;
    for (auto &[first, second] : antinodes) {
        counter++;
    }
    std::cout << counter << std::endl;

    return 0;
}
