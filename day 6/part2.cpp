#include <fstream>
#include <iostream>
#include <vector>

constexpr int MAX_STEPS = 30000;

bool checkLoop(int x, int y, std::vector<std::string> &map) {
    int counter = 0;

    int yaw = 0;
    while ((x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) && counter < MAX_STEPS) {
        int nextX = x;
        int nextY = y;
        switch (yaw) {
            case 0:
                --nextX;
                break;
            case 90:
                ++nextY;
                break;
            case 180:
                ++nextX;
                break;
            case 270:
                --nextY;
                break;
        }

        if (nextX >= 0 && nextX < map.size() && nextY >= 0 && nextY < map[0].size() && map[nextX][nextY] == '#') {
            yaw += 90;
            yaw = yaw >= 360 ? yaw - 360 : yaw;
        } else {
            x = nextX;
            y = nextY;
        }
        ++counter;
    }

    return counter == MAX_STEPS;
}

int main() {
    std::ifstream file("day 6/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    int x, y;
    while (getline(file, line)) {
        map.push_back(line);
        auto position = line.find('^');
        if (position != std::string::npos) {
            x = map.size() - 1;
            y = position;
        }
    }

    int counter = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (i == x && j == y) {
                continue;
            }

            std::vector<std::string> mapNew = map;
            mapNew[i][j] = '#';
            if (checkLoop(x, y, mapNew)) {
                ++counter;
            }

            std::cout << i << "/" << map.size() - 1 << std::endl;
        }
    }

    std::cout << counter << std::endl;

    return 0;
}
