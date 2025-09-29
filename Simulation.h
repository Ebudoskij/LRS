#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include <memory>

#include "Generator.h"

class Simulation {
 private:
  std::shared_ptr<Generator> generator;
  int totalGenerations;
  std::map<int, int> results;

 public:
  Simulation(std::shared_ptr<Generator> gen, int total);

  void operator()();

  const std::map<int, int>& getResults() const;
  int getTotalGenerations() const;
};

#endif  // SIMULATION_H
