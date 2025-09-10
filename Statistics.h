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

    void operator()() const;
};

#endif
