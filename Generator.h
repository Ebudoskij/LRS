#pragma once

#include <random>

using namespace std;

class Generator {
  private:
    long vol;
    mt19937 gen;
    uniform_int_distribution<int> dist;
  public:
    explicit Generator(long userVol): vol(userVol){};

    vector<int> operator()();

};