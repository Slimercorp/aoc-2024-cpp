#include <algorithm>
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
            disk.insert(disk.end(), size, id);
            ++id;
        } else {
            disk.insert(disk.end(), size, -1);
        }
    }

    for (int currentID = id - 1; currentID >= 0; --currentID) {
        auto fileBegin = std::find(disk.begin(), disk.end(), currentID);
        if (fileBegin == disk.end()) {
            continue;
        }

        auto fileEnd = std::find_if(fileBegin, disk.end(), [currentID](int value) {
            return value != currentID;
        });

        size_t fileSize = std::distance(fileBegin, fileEnd);

        auto freespaceBegin = disk.begin();
        while (true) {
            freespaceBegin = std::find(freespaceBegin, disk.end(), -1);
            if (freespaceBegin == disk.end()) {
                break;
            }

            auto freespaceEnd = std::find_if(freespaceBegin, disk.end(), [](int value) {
                return value != -1;
            });

            size_t freespaceSize = std::distance(freespaceBegin, freespaceEnd);

            if (freespaceSize >= fileSize && freespaceBegin < fileBegin) {
                std::fill(freespaceBegin, freespaceBegin + fileSize, currentID);
                std::fill(fileBegin, fileEnd, -1);
                break;
            }

            freespaceBegin = freespaceEnd;
        }
    }

    unsigned long long sum = 0;
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] != -1) {
            sum += i * disk[i];
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
