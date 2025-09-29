#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <vector>

#include "Data.h"

class Statistics {
 private:
  // TODO(@Ebudoskij): shared ownership should use shared_ptr
  const std::shared_ptr<std::vector<Item>> items;
  const std::shared_ptr<std::map<int, int>> results;
  int totalGenerations;

 public:
  Statistics(const std::shared_ptr<std::vector<Item>> items,
             const std::shared_ptr<std::map<int, int>> results,
             int totalGenerations);

  void printStatistics(std::ostream& os = std::cout) const;
  void printTableData(std::ostream& os = std::cout) const;
  double calculateMaxDifference() const;

 private:
  // TODO(@Ebudoskij): make some of these functions free
  int calculateTotalFrequency() const;
  double calculateExpected(int frequency, int totalFreq) const;
  double calculateActual(int num) const;
};

#endif  // STATISTICS_H