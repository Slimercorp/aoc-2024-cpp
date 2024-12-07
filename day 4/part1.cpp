#include <fstream>
#include <iostream>
#include <vector>

bool checkDirection(const std::vector<std::string> &words, int x, int y, int dx, int dy, int maxX, int maxY) {
    for (int i = 1; i <= 3; ++i) {
        x += dx;
        y += dy;
        if (x < 0 || y < 0 || x >= maxX || y >= maxY ||
            (i == 1 && words[x][y] != 'M') ||
            (i == 2 && words[x][y] != 'A') ||
            (i == 3 && words[x][y] != 'S')) {
            return false;
        }
    }
    return true;
}

int findXmasWord(const std::vector<std::string> &words, int x, int y, int maxX, int maxY) {
    int count = 0;

    const std::vector<std::pair<int, int> > directions = {
        {0, 1}, // right
        {0, -1}, // left
        {-1, 0}, // up
        {1, 0}, // down
        {-1, 1}, // right-up
        {-1, -1}, // left-up
        {1, 1}, // right-down
        {1, -1} // left-down
    };

    for (const auto &[dx, dy]: directions) {
        if (checkDirection(words, x, y, dx, dy, maxX, maxY)) {
            ++count;
        }
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
            if (lines[i][j] == 'X') {
                sum += findXmasWord(lines, i, j, maxX, maxY);
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
