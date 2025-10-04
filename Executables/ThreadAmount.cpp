#include "../Generator.h"
#include "../Accumulate.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <format>

int main(){
  Generator gen;

  const long volume = 100000000;
  vector<int> threadsAmount = {1, 2, 4, 8, 9, 10, 16};
  std::vector<int> data = gen.generate(volume);

  for (auto amount : threadsAmount){
    MultiThread func(data, amount);

    auto startM = std::chrono::high_resolution_clock::now();

    auto minM = func();

    auto endM = std::chrono::high_resolution_clock::now();

    auto durationM_ms = std::chrono::duration_cast<std::chrono::microseconds> (endM-startM);

    std::cout << std::format("Data set: {}, Algorithm: {}, Threads: {}, Time: {} micros, Result: {}\n", volume, "concurrent", amount, durationM_ms.count(), minM);
  }
}