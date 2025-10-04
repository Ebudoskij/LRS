#pragma once

#include <vector>
#include <random>

using namespace std;

class Generator {
  private:
    mt19937 gen;
    uniform_int_distribution<int> dist;
  public:
    explicit Generator() {};

    vector<int> generate(long vol);

};