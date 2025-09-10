#include "Simulation.h"
#include <iostream>

Simulation::Simulation(Generator& gen, int total)
    : generator(gen), totalGenerations(total) {}

void Simulation::operator()() {
    std::cout << "\nGeneration " << totalGenerations << " random numbers...\n";
    results.clear();

    for (int i = 0; i < totalGenerations; ++i) {
        Item curItem = generator();
        results[curItem.num]++;
    }
}

const std::map<int, int>& Simulation::getResults() const {
    return results;
}

int Simulation::getTotalGenerations() const {
    return totalGenerations;
}
