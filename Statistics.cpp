#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Statistics::Statistics(const std::vector<Item>& items,
                       const std::map<int, int>& results,
                       int totalGenerations)
    : items(items), results(results), totalGenerations(totalGenerations) {}

void Statistics::operator()() const {
      std::cout << "\n--- Statistics ---\n";
        int totalFreq = 0;
        for (const auto& item : items) {
            totalFreq += item.frequency;
        }

        double maxDiff = 0.0;

       std::cout << "Number | Expected | Actual\n";
        for (const auto& item : items) {
            
            double expected = static_cast<double>(item.frequency) / totalFreq;
            int actualCount = 0;
            if (results.count(item.num)) {
                actualCount = results.at(item.num);
            }
            double actual = static_cast<double>(actualCount) / totalGenerations;

            double diff = fabs(expected - actual);
            if (diff > maxDiff) maxDiff = diff;

            printf("%6i | %8.5f | %.5f\n", item.num, expected, actual);
        }

        std::cout << "---------------------------------\n";
        std::cout << "Max difference: " << maxDiff << '\n';
    
}
