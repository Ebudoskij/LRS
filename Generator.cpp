#include "Generator.h"

using namespace std;

vector<int> Generator::generate(long vol){
  vector<int> nums;
  nums.reserve(vol);
  int randNum;
  
  for (size_t i = 0; i < vol; i++){
    randNum = dist(gen);
    nums.push_back(randNum);
  }

  return nums;
}