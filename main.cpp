#include "Data.h"
#include "Generator.h"
#include "Simulation.h"
#include "Statistics.h"
#include <iostream>

int main() {
    try {
        Data data;
        data.readFromFile("input.txt");
        data.printInputData();

        auto gen = std::make_shared<Generator>(data.getItems());

        Simulation simulate(gen, data.getN());
        simulate();

        Statistics stats(data.getItems(), simulate.getResults(), simulate.getTotalGenerations());
        stats.printStatistics();  
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}
