#include "Generator.h"

using namespace std;

vector<int> Generator::operator()(){
  vector<int> nums;
  int randNum;
  
  for (size_t i = 0; i < vol; i++){
    randNum = dist(gen);
    nums.push_back(randNum);
  }

  return nums;
}