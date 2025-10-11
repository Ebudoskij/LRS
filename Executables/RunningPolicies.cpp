#include "../Generator.h"
#include "../Accumulate.h"
#include "../LoggerCSV.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <format>

int main(int argc, char* argv[]){
  CsvLogger logger("experiment_results.csv"); 

  //логування рівня оптимізації при запуску
  std::string optimization_level = (argc > 1) ? argv[1] : "N/A";

  Generator gen;
  vector<int> volumes = {100000, 1000000, 10000000, 100000000};
  for (auto volume : volumes){
    std::vector<int> data = gen.generate(volume);

    auto start = std::chrono::high_resolution_clock::now();

    auto min = std::min_element(data.begin(), data.end());

    auto end = std::chrono::high_resolution_clock::now();

    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds> (end-start);

    logger.log("standard",
      optimization_level, 
      volume, 
      1,                  
      duration_us.count(), 
      *min);  
  }
}
