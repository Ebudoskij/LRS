#include "Statistics.h"

// TODO(@Ebudoskij): sort your includes
#include <cmath>
#include <cstdio>
#include <format>
#include <iomanip>
#include <iostream>

Statistics::Statistics(const std::shared_ptr<std::vector<Item>> items,
                       const std::shared_ptr<std::map<int, int>> results,
                       int totalGenerations)
    : items(std::move(items)),
      results(std::move(results)),
      totalGenerations(totalGenerations) {}

void Statistics::printStatistics(std::ostream& os) const {
  os << "\n--- Statistics ---\n";
  printTableData(os);
  os << "---------------------------------\n";
  os << std::format("{:.5f}\n", calculateMaxDifference());
}

void Statistics::printTableData(std::ostream& os) const {
  os << "Number | Expected | Actual\n";
  const auto totalFreq = calculateTotalFrequency();

  for (const auto& item : *items) {
    const auto expected = calculateExpected(item.freq, totalFreq);
    const auto actual = calculateActual(item.num);

    // format into a string and send to the given stream
    os << std::format("{:6d} | {:8.5f} | {:.5f}\n", item.num, expected, actual);
  }
}

double Statistics::calculateMaxDifference() const {
  const auto totalFreq = calculateTotalFrequency();
  double maxDiff = 0.0;

  for (const auto& item : *items) {
    const auto expected = calculateExpected(item.freq, totalFreq);
    const auto actual = calculateActual(item.num);
    const auto diff = fabs(expected - actual);

    if (diff > maxDiff) {
      maxDiff = diff;
    }
  }

  return maxDiff;
}

int Statistics::calculateTotalFrequency() const {
  int totalFreq = 0;
  for (const auto& item : *items) {
    totalFreq += item.freq;
  }
  return totalFreq;
}

double Statistics::calculateExpected(int freq, int totalFreq) const {
  return static_cast<double>(freq) / totalFreq;
}

double Statistics::calculateActual(int num) const {
  int actualCount = 0;
  if (results->count(num)) {
    actualCount = results->at(num);
  }
  return static_cast<double>(actualCount) / totalGenerations;
}