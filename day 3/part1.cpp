#include <fstream>
#include <iostream>
#include <regex>

int main() {
    std::ifstream file("day 3/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    std::regex patternMul(R"(mul\((\d{1,3}),(\d{1,3})\))");
    int sum = 0;
    while (std::getline(file, line)) {
        for (std::sregex_iterator iter(line.begin(), line.end(), patternMul), end; iter != end; ++iter) {
            const std::smatch &match = *iter;
            int firstNumber = std::stoi(match[1].str());
            int secondNumber = std::stoi(match[2].str());

            sum += firstNumber * secondNumber;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
