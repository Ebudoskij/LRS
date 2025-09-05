#include <string>
#include <map>
#include <random>
#include <iostream>

using namespace std;

//number - frequency pair
struct Item{
  int num;
  int frequency;
  Item(int n, int f): num(n), frequency(f){}; 
};

//reading file
class Data{};

//generating 1 random number
class  Generator{
  private:
    vector<Item> data;
    vector<int> prefix;
    mt19937 gen;
    uniform_int_distribution<int> dist;
  public:
    Generator(const vector<Item>& items): data(items), gen(random_device()){
      int total = 0;
      for (auto& i : data){
        total += i.frequency;
        prefix.push_back(total);
      }
      dist = uniform_int_distribution<int>(1, total);
    }

    Item operator() (){
      int rand = dist(gen);
      for (size_t i = 0; i < prefix.size(); ++i){
        if(rand <= prefix[i]){
          return data[i];
        }
      }
      return data.back();
    }
};

//generating n random numbers
class Simulation{};

//printing stats
class Statistics{};


int main(){

  return 0;
}