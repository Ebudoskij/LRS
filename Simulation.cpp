#include "Simulation.h"
#include <iostream>

Simulation::Simulation(Generator& gen, int total)
    : generator(gen), totalGenerations(total) {}

void Simulation::operator()() {
    results.clear();

    for (int i = 0; i < totalGenerations; ++i) {
        auto curItem = generator();
        results[curItem]++;
    }
}

const std::map<int, int>& Simulation::getResults() const {
    return results;
}

int Simulation::getTotalGenerations() const {
    return totalGenerations;
}
