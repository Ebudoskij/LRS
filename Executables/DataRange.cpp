#include "../Generator.h"

#include <iostream>
#include <chrono>

using namespace std;

int main(){
  Generator gen(10000000);
  vector<int> data = gen();

  auto start = chrono::high_resolution_clock::now();

  auto min = min_element(data.begin(), data.end());

  auto end = chrono::high_resolution_clock::now();

  auto duration_ms = chrono::duration_cast<chrono::milliseconds> (end-start);

  cout << *min << endl;

  cout << duration_ms;
}