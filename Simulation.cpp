#include "Simulation.h"

#include <iostream>

Simulation::Simulation(std::shared_ptr<Generator> gen, int total)
    : generator(std::move(gen)), totalGenerations(total) {}

void Simulation::operator()() {
  results.clear();
  // TODO(@oleksandrasafranchuk): use prefix and postfix ++ consistently
  for (int i = 0; i < totalGenerations; ++i) {
    const auto curItem = (*generator)();
    ++results[curItem];
  }
}

const std::map<int, int>& Simulation::getResults() const { return results; }

int Simulation::getTotalGenerations() const { return totalGenerations; }
