#include "Data.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Data::Data(const std::string& filename) {
    readFromFile(filename);
}

void Data::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    if (!(file >> n) || n <= 0) {
        throw std::runtime_error("Error: Invalid n (must be positive integer)");
    }

    std::string line;
    getline(file, line); 

   
    if (!getline(file, line)) {
        throw std::runtime_error("Error: Missing numbers line");
    }
    std::istringstream numbersStream(line);
    std::vector<int> numbers;
    int num;
    while (numbersStream >> num) {
        numbers.push_back(num);
    }

    if (!getline(file, line)) {
        throw std::runtime_error("Error: Missing frequencies line");
    }
    std::istringstream freqStream(line);
    std::vector<int> frequencies;
    int freq;
    while (freqStream >> freq) {
        frequencies.push_back(freq);
    }

    if (numbers.size() != frequencies.size()) {
        throw std::runtime_error("Error: Numbers and frequencies count mismatch");
    }
    if (numbers.empty()) {
        throw std::runtime_error("Error: No numbers provided");
    }

    items.clear();
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (frequencies[i] <= 0) {
            throw std::runtime_error("Error: Frequency must be positive for number " + std::to_string(numbers[i]));
        }
        items.emplace_back(numbers[i], frequencies[i]);
    }
}

int Data::getN() const { return n; }

const std::vector<Item>& Data::getItems() const { return items; }

void Data::printInputData() const {
    std::cout << "Input data:\n";
    std::cout << "n = " << n << '\n';
    std::cout << "Numbers: ";
    for (const auto& item : items) {
        std::cout << item.num << ' ';
    }
    std::cout << '\n';
    std::cout << "Frequency: ";
    for (const auto& item : items) {
        std::cout << item.frequency << ' ';
    }
    std::cout << '\n';
}
