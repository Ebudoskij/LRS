#include <iostream>

#include "Data.h"
#include "Generator.h"
#include "Simulation.h"
#include "Statistics.h"

int main() {
  try {
    Data data;
    data.readFromFile("input.txt");
    data.printInputData();

    auto gen = std::make_shared<Generator>(data.getItems());

    Simulation simulate(gen, data.getN());
    simulate();

    Statistics stats(
        std::make_shared<std::vector<Item>>(data.getItems()),
        std::make_shared<std::map<int, int>>(simulate.getResults()),
        simulate.getTotalGenerations());
    stats.printStatistics();
  } catch (const std::exception& e) {
    std::cerr << "[ERROR] " << e.what() << '\n';
    return 1;
  }

  return 0;
}
