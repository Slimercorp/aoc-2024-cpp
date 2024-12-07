#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

bool findExpression(const std::vector<unsigned long long>& numbers, unsigned long long target, size_t index, unsigned long long currentValue) {
    if (index == numbers.size()) {
        return currentValue == target;
    }

    unsigned long long nextNumber = numbers[index];

    bool foundPlus = findExpression(numbers, target, index + 1, currentValue + nextNumber);

    bool foundMultiply = findExpression(numbers, target, index + 1, currentValue * nextNumber);

    bool foundConcat = findExpression(numbers, target, index + 1, std::stoull(std::to_string(currentValue) + std::to_string(nextNumber)));

    return foundPlus || foundMultiply || foundConcat;
}

int main() {
    std::ifstream file("day 7/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    unsigned long long totalSum = 0;

    while (std::getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) {
            std::cerr << "Invalid format in line: " << line << std::endl;
            return 1;
        }

        unsigned long long target = std::stoull(line.substr(0, colonPos));

        std::stringstream ss(line.substr(colonPos + 1));
        std::vector<unsigned long long> numbers;
        unsigned long long num;
        while (ss >> num) {
            numbers.push_back(num);
        }

        if (findExpression(numbers, target, 1, numbers[0])) {
            totalSum += target;
        }
    }

    file.close();

    std::cout << totalSum << std::endl;

    return 0;
}
