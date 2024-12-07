#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

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

    int yaw = 0;
    std::unordered_map<std::string, int> visited;
    while (x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) {
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
            ++visited[std::to_string(x) + ";" + std::to_string(y)];
        }
    }

    std::cout << visited.size() - 1 << std::endl;


    return 0;
}
