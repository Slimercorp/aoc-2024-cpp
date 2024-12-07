#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

int main() {
    std::ifstream file("day 5/input.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int> > rules;
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        std::pair rule = {std::stoi(line.substr(0, 2)), std::stoi(line.substr(3, 2))};
        rules.push_back(rule);
    }

    std::vector<std::vector<int> > updates;
    std::regex pattern(R"(\d+)");
    while (std::getline(file, line)) {
        std::vector<int> update;
        for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), pattern), end; it != end; ++it) {
            const std::smatch &match = *it;
            const std::string digitString = match[0].str();
            update.push_back(std::stoi(match[0].str()));
        }
        updates.push_back(update);
    }

    int counter = 0;
    for (auto &update: updates) {
        bool isUpdateOk = true;
        for (size_t i = 0; i < update.size() - 1; i++) {
            for (size_t j = i + 1; j < update.size(); j++) {
                int &first = update[i];
                int &second = update[j];
                std::pair rule = {second, first};
                auto it = std::find(rules.begin(), rules.end(), rule);
                if (it != rules.end()) {
                    isUpdateOk = false;
                    break;
                }
            }

            if (!isUpdateOk) {
                break;
            }
        }

        if (isUpdateOk) {
            counter += update[update.size() / 2];
        }
    }

    std::cout << counter << std::endl;

    return 0;
}
