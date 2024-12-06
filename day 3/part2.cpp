#include <fstream>
#include <iostream>
#include <regex>

int main() {
    std::ifstream file("day 3/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string lineTmp;
    std::string line;
    while (std::getline(file, lineTmp)) {
        line = line.append(lineTmp);
    }

    std::regex patternMul(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex patternDo(R"(do\(\))");
    std::regex patternDont(R"(don't\(\))");
    int sum = 0;
    bool mulEnabled = true;
    std::sregex_iterator end;
    std::sregex_iterator iterDo(line.begin(), line.end(), patternDo);
    std::sregex_iterator iterDont(line.begin(), line.end(), patternDont);
    int pos = 0;
    while (true) {
        if (mulEnabled) {
            pos = iterDont->position();
            mulEnabled = false;
            int posDo = iterDo->position();
            while (posDo < pos && iterDo != end) {
                ++iterDo;
                posDo = iterDo->position();
            }
        } else {
            int posDo = iterDo != end ? iterDo->position() : line.size();
            for (size_t i = pos; i <= posDo && i < line.size(); ++i) {
                line[i] = '*';
            }
            pos = posDo;
            mulEnabled = true;
            int posDont = iterDont->position();
            while (posDont < pos && iterDont != end) {
                ++iterDont;
                posDont = iterDont->position();
            }
        }

        if (iterDont == end && iterDo == end) {
            break;
        }
    }

    for (std::sregex_iterator iter(line.begin(), line.end(), patternMul); iter != end; ++iter) {
        const std::smatch &match = *iter;
        int firstNumber = std::stoi(match[1].str());
        int secondNumber = std::stoi(match[2].str());

        sum += firstNumber * secondNumber;
    }

    std::cout << sum << std::endl;
    return 0;
}
