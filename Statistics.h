#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <map>
#include "Data.h"

class Statistics {
private:
    const std::vector<Item>& items;
    const std::map<int, int>& results;
    int totalGenerations;

public:
    Statistics(const std::vector<Item>& items,
               const std::map<int, int>& results,
               int totalGenerations);

    void printStatistics(std::ostream& os = std::cout) const;
    void printTableData(std::ostream& os = std::cout) const;
    double calculateMaxDifference() const;

private:
    int calculateTotalFrequency() const;
    double calculateExpected(int frequency, int totalFreq) const;
    double calculateActual(int num) const;
};

#endif //STATISTICS_H