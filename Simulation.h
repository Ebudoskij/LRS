#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include "Generator.h"

class Simulation {
private:
    Generator& generator;
    int totalGenerations;
    std::map<int, int> results;

public:
    Simulation(Generator& gen, int total);

    void operator()();

    const std::map<int, int>& getResults() const;
    int getTotalGenerations() const;
};

#endif
