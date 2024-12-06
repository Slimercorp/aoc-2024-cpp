#include <fstream>
#include <iostream>
#include <regex>

int calculateSum(std::string &line) {
    const std::regex patternMul(R"(mul\((\d{1,3}),(\d{1,3})\))");

    int sum = 0;
    for (std::sregex_iterator iter(line.begin(), line.end(), patternMul), end; iter != end; ++iter) {
        const std::smatch &match = *iter;
        int firstNumber = std::stoi(match[1].str());
        int secondNumber = std::stoi(match[2].str());

        sum += firstNumber * secondNumber;
    }
    return sum;
}

void maskRanges(std::string &line) {
    const std::regex patternDo(R"(do\(\))");
    const std::regex patternDont(R"(don't\(\))");

    bool mulEnabled = true;
    std::sregex_iterator end;
    std::sregex_iterator iterDo(line.begin(), line.end(), patternDo);
    std::sregex_iterator iterDont(line.begin(), line.end(), patternDont);
    size_t currentPos = 0;
    while (iterDont != end || iterDo != end) {
        if (mulEnabled) {
            currentPos = iterDont->position();
            mulEnabled = false;
            size_t posDo = iterDo->position();
            while (posDo < currentPos && iterDo != end) {
                ++iterDo;
                posDo = iterDo->position();
            }
        } else {
            size_t posDo = iterDo != end ? iterDo->position() : line.size();
            std::fill(line.begin() + currentPos, line.begin() + posDo, '*');
            currentPos = posDo;
            mulEnabled = true;
            size_t posDont = iterDont->position();
            while (posDont < currentPos && iterDont != end) {
                ++iterDont;
                posDont = iterDont->position();
            }
        }
    }
}

int main() {
    std::ifstream file("day 3/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string line = buffer.str();

    maskRanges(line);

    std::cout <<  calculateSum(line) << std::endl;

    return 0;
}
