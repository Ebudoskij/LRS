#include "Data.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

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
  // TODO(@oleksandrasafranchuk): consider using std::transform
  std::transform(numbers.cbegin(), numbers.cend(), frequencies.cbegin(),
                 std::back_inserter(items), [](auto number, auto frequency) {
                   // TODO(@oleksandrasafranchuk): consider checking earlier
                   if (frequency <= 0) {
                     throw std::runtime_error(
                         "Error: Frequency must be positive for number " +
                         std::to_string(number));
                   }
                   return std::make_pair(number, frequency);
                 });
}

int Data::getN() const { return n; }

const std::vector<Item>& Data::getItems() const { return items; }

std::ostream& Data::formatInputData(std::ostream& os) const {
  os << "Input data:\n";
  os << "n = " << n << '\n';
  // TODO(@oleksandrasafranchuk): no extra space before newline
  os << "Numbers:";
  for (const auto& item : items) {
    os << ' ' << item.num;
  }
  os << '\n';
  os << "Frequency:";
  for (const auto& item : items) {
    os << ' ' << item.freq;
  }
  os << '\n';
  return os;
}

void Data::printInputData() const { formatInputData(std::cout); }

std::ostream& operator<<(std::ostream& os, const Data& data) {
  return data.formatInputData(os);
}
