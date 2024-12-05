#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("day 1/input.txt");
    if (!file) {
        std::cerr << "File is not found" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> firstColumn;
    std::vector<int> secondColumn;
    while (std::getline(file, line)) {
        std::regex pattern(R"((\d+)\s+(\d+))");
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            if (match.size() >= 3) {
                std::string firstNumber = match[1];
                std::string secondNumber = match[2];

                firstColumn.push_back(std::stoi(firstNumber));
                secondColumn.push_back(std::stoi(secondNumber));
            } else {
                std::cerr << "Match did not return enough groups." << std::endl;
            }
        } else {
            std::cerr << "No match found." << std::endl;
        }
    }

    std::sort(firstColumn.begin(), firstColumn.end());
    std::sort(secondColumn.begin(), secondColumn.end());

    int sum = 0;
    for (size_t i = 0; i < firstColumn.size(); ++i) {
        sum += std::abs(firstColumn[i] - secondColumn[i]);
    }

    std::cout << sum << std::endl;
    return 0;
}
