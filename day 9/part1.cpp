#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("day 9/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    getline(file, line);

    std::vector<int> disk;
    int id = 0;
    for (int i = 0; i < line.size(); i++) {
        int size = line[i] - '0';
        if (i % 2 == 0) {
            disk.insert(disk.begin() + disk.size(), size, id);
            ++id;
        } else {
            disk.insert(disk.begin() + disk.size(), size, -1);
        }
    }

    auto itEnd = disk.end() - 1;
    auto itBegin = disk.begin();
    while (true) {
        while (*itEnd == -1) {
            --itEnd;
        }

        while (*itBegin != -1) {
            ++itBegin;
        }

        if (itBegin > itEnd) {
            break;
        }

        *itBegin = *itEnd;
        *itEnd = -1;
    }

    unsigned long long sum = 0;
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] == -1) {
            break;
        }

        sum += i * disk[i];
    }

    std::cout << sum << std::endl;
    return 0;
}
