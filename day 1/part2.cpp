#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>

int main() {
    std::ifstream file("day 1/input.txt");
    if (!file) {
        std::cerr << "File is not found" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> firstNumbers;
    const std::regex pattern(R"((\d+)\s+(\d+))");
    std::unordered_map<int, int> frequencyMap;

    while (std::getline(file, line)) {
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            int firstNumber = std::stoi(match[1]);
            int secondNumber = std::stoi(match[2]);

            firstNumbers.push_back(firstNumber);
            frequencyMap[secondNumber]++;
        } else {
            std::cerr << "No match found." << std::endl;
        }
    }

    int sum = 0;
    for (const int &value: firstNumbers) {
        auto it = frequencyMap.find(value);
        if (it != frequencyMap.end()) {
            sum += std::abs(value * it->second);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
