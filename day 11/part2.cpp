#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

int main() {
    std::ifstream file("day 11/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    getline(file, line);

    std::istringstream stream(line);
    std::unordered_map<unsigned long long, unsigned long long> stones;
    unsigned long long num;
    while (stream >> num) {
        stones[num] = 1;
    }

    for (int i = 0; i < 75; i++) {
        std::unordered_map<unsigned long long, unsigned long long> stonesNew;
        for (const auto &[stone, number]: stones) {
            std::string stoneStr = std::to_string(stone);
            if (stone == 0) {
                stonesNew[1] += number;
            } else if (stoneStr.size() % 2 == 0) {
                unsigned long long firstPart = std::stoull(stoneStr.substr(0, stoneStr.size() / 2));
                unsigned long long secondPart = std::stoull(stoneStr.substr(stoneStr.size() / 2, stoneStr.size() / 2));
                stonesNew[firstPart] += number;
                stonesNew[secondPart] += number;
            } else {
                stonesNew[stone * 2024] += number;
            }
        }
        stones = stonesNew;
        std::cout << i << std::endl;
    }

    unsigned long long sum = 0;
    for (const auto &[stone, number]: stones) {
        sum += number;
    }
    std::cout << sum << std::endl;
    return 0;
}
