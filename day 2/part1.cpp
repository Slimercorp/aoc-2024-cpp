#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

constexpr int MAX_STEP = 3;
constexpr int MIN_STEP = 1;

int main() {
    std::ifstream file("day 2/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    const std::regex pattern(R"(\d+)");
    int safeReportsCount = 0;
    while (std::getline(file, line)) {

        std::vector<int> report;
        for (std::sregex_iterator it(line.begin(), line.end(), pattern), end; it != end; ++it) {
            report.push_back(std::stoi(it->str()));
        }

        bool isSafeReport = true;
        bool isMustIncrease = report[0] < report[1];
        for (size_t i = 1; i < report.size(); i++) {
            const bool currentIsIncreasing = report[i-1] < report[i];
            const int step = std::abs(report[i] - report[i-1]);
            if ((isMustIncrease != currentIsIncreasing) || (step < MIN_STEP) || (step > MAX_STEP)) {
                isSafeReport = false;
                break;
            }
        }

        if (isSafeReport) {
            ++safeReportsCount;
        }
    }

    std::cout << safeReportsCount << std::endl;
    return 0;
}