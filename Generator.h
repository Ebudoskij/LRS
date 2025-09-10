#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <random>
#include "Data.h"

class Generator {
private:
    std::vector<Item> data;
    std::vector<int> prefix;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    explicit Generator(const std::vector<Item>& items);

    Item operator()();
};

#endif
