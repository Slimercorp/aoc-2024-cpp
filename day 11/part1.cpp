#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>


int main() {
    std::ifstream file("day 11/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    getline(file, line);

    std::istringstream stream(line);
    std::vector<unsigned long long> stones;
    unsigned long long num;
    while (stream >> num) {
        stones.push_back(num);
    }

    for (int i = 0; i < 25; i++) {
        std::vector<unsigned long long> stonesNew;
        for (const auto &stone: stones) {
            std::string stoneStr = std::to_string(stone);
            if (stone == 0) {
                stonesNew.push_back(1);
            } else if (stoneStr.size() % 2 == 0) {
                unsigned long long firstPart = std::stoull(stoneStr.substr(0, stoneStr.size() / 2));
                unsigned long long secondPart = std::stoull(stoneStr.substr(stoneStr.size() / 2, stoneStr.size() / 2));
                stonesNew.push_back(firstPart);
                stonesNew.push_back(secondPart);
            } else {
                stonesNew.push_back(stone * 2024);
            }
        }
        stones = stonesNew;
    }

    std::cout << stones.size() << std::endl;
    return 0;
}
