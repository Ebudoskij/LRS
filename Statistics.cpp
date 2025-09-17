#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>

Statistics::Statistics(const std::vector<Item>& items,
                       const std::map<int, int>& results,
                       int totalGenerations)
    : items(items), results(results), totalGenerations(totalGenerations) {}

void Statistics::printStatistics(std::ostream& os) const {
    os << "\n--- Statistics ---\n";
    printTableData(os);
    os << "---------------------------------\n";
    os << "Max difference: " << calculateMaxDifference() << '\n';
}



void Statistics::printTableData(std::ostream& os) const {
    os << "Number | Expected | Actual\n";
   int totalFreq = calculateTotalFrequency();
    
    for (const auto& item : items) {
        double expected = calculateExpected(item.freq, totalFreq);
        double actual = calculateActual(item.num);
        
        if (&os == &std::cout) {
            printf("%6i | %8.5f | %.5f\n", item.num, expected, actual);
        } else {
              os << std::setw(6) << item.num << " | " 
               << std::setw(8) << std::fixed << std::setprecision(5) << expected << " | " 
               << std::fixed << std::setprecision(5) << actual << "\n";
        }
    }
}

double Statistics::calculateMaxDifference() const {
    int totalFreq = calculateTotalFrequency();
    double maxDiff = 0.0;
    
    for (const auto& item : items) {
        double expected = calculateExpected(item.freq, totalFreq);
        double actual = calculateActual(item.num);
        double diff = fabs(expected - actual);
        
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }
    
    return maxDiff;
}

int Statistics::calculateTotalFrequency() const {
    int totalFreq = 0;
    for (const auto& item : items) {
        totalFreq += item.freq;
    }
    return totalFreq;
}

double Statistics::calculateExpected(int freq, int totalFreq) const {
    return static_cast<double>(freq) / totalFreq;
}

double Statistics::calculateActual(int num) const {
    int actualCount = 0;
    if (results.count(num)) {
        actualCount = results.at(num);
    }
    return static_cast<double>(actualCount) / totalGenerations;
}