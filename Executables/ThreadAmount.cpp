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
  const long volume = 100000000;

  vector<int> threadsAmount = {1, 2, 4, 8, 9, 10, 16};
  std::vector<int> data = gen.generate(volume);

  for (auto amount : threadsAmount){
    MultiThread func(data, amount);

    auto start = std::chrono::high_resolution_clock::now();

    auto min = func();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds> (end-start);

  logger.log("parallel", 
    optimization_level, 
    volume, 
    amount,                  
    duration_us.count(), 
    min);  
  }  
}
