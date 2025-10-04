#include "../Generator.h"
#include "../Accumulate.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <format>

int main(){
  Generator gen;
  vector<int> volumes = {100000, 1000000, 10000000, 100000000};
  for (auto volume : volumes){
    std::vector<int> data = gen.generate(volume);

    auto start = std::chrono::high_resolution_clock::now();

    auto min = std::min_element(data.begin(), data.end());

    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds> (end-start);

    std::cout << std::format("Data set: {}, Algorithm: {}, Time: {} micros , Result: {}\n", volume, "standard", duration_ms.count(), *min);
  }
}