#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <cmath>

constexpr int MAX_STEP = 3;
constexpr int MIN_STEP = 1;

bool isSafeReport(const std::vector<int>& report) {
    if (report.size() < 2) return true;

    bool isMustIncrease = report[1] > report[0];
    for (size_t i = 1; i < report.size(); ++i) {
        const int step = std::abs(report[i] - report[i - 1]);
        const bool isIncreasing = report[i] > report[i - 1];
        if ((isIncreasing != isMustIncrease) || (step < MIN_STEP) || (step > MAX_STEP)) {
            return false;
        }
    }
    return true;
}

bool isSafeWithDampener(const std::vector<int>& report) {
    if (isSafeReport(report)) return true;

    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i);
        if (isSafeReport(modifiedReport)) return true;
    }
    return false;
}

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

        if (isSafeWithDampener(report)) {
            ++safeReportsCount;
        }
    }

    std::cout << safeReportsCount << std::endl;
    return 0;
}
