#include <fstream>
#include <iostream>
#include <vector>

bool checkPoint(const std::vector<std::string> &words, int x, int y, int maxX, int maxY, char letter) {
    return x >= 0 && y >= 0 && x < maxX && y < maxY && words[x][y] == letter;
}

int findXmasWord(const std::vector<std::string> &words, int x, int y, int maxX, int maxY) {
    int count = 0;

    const std::vector<std::pair<int, int> > directions = {
        {-1, 1}, // right-up
        {-1, -1}, // left-up
        {1, 1}, // right-down
        {1, -1} // left-down
    };

    int countMletter = 0;
    for (const auto &[dx, dy]: directions) {
        if (checkPoint(words, x + dx, y + dy, maxX, maxY, 'M')) {
            ++countMletter;
        }
    }

    int countSletter = 0;
    for (const auto &[dx, dy]: directions) {
        if (checkPoint(words, x + dx, y + dy, maxX, maxY, 'S')) {
            ++countSletter;
        }
    }

    if (countMletter == 2 && countSletter == 2 && words[x - 1][y - 1] != words[x + 1][y + 1]) {
        ++count;
    }
    return count;
}

int main() {
    std::ifstream file("day 4/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    const int maxX = lines.size();
    const int maxY = maxX > 0 ? lines[0].size() : 0;

    int sum = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].length(); ++j) {
            if (lines[i][j] == 'A') {
                sum += findXmasWord(lines, i, j, maxX, maxY);
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
