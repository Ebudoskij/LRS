#include <string>
#include <map>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

//number - frequency pair
struct Item{
  int num;
  int frequency;
  Item(int n, int f): num(n), frequency(f){}; 
};

//reading file
class Data {
private:
    int n;
    vector<Item> items;

public:
    Data(const string& filename) {
        readFromFile(filename);
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
       
        file >> n;
       
        string line;
        getline(file, line); 
        getline(file, line);
        istringstream numbersStream(line);
        vector<int> numbers;
        int num;
        while (numbersStream >> num) {
            numbers.push_back(num);
        }

        getline(file, line);
        istringstream freqStream(line);
        vector<int> frequencies;
        int freq;
        while (freqStream >> freq) {
            frequencies.push_back(freq);
        }

        for (size_t i = 0; i < numbers.size(); ++i) {
            items.emplace_back(numbers[i], frequencies[i]);
        }

        file.close();
    }

    int getN() const { return n; }
    const vector<Item>& getItems() const { return items; }

    void printInputData() const {
        cout<< "Input data:"<<'\n';
        cout << "n = " << n << '\n';
        cout << "Numbers: ";
        for (const auto& item : items) {
            cout << item.num << ' ';
        }
        cout << '\n';
        cout << "Frequency: ";
        for (const auto& item : items) {
            cout << item.frequency << ' ';
        }
        cout << '\n';
    }
};

//generating 1 random number
class  Generator{
  private:
    vector<Item> data;
    vector<int> prefix;
    mt19937 gen;
    uniform_int_distribution<int> dist;
  public:
    Generator(const vector<Item>& items): data(items), gen(random_device{}()){
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
class Simulation{
  private:
    Generator& generator;
    int totalGenerations;
    map<int, int> results;
  public:
    Simulation (Generator& gen, int total): generator(gen), totalGenerations(total){};

    void operator ()(){
      cout << "\nGeneration " << totalGenerations << " random numbers...\n";
      results.clear();

      for (size_t i = 0; i< totalGenerations; ++i){
        Item curItem = generator();
        results[curItem.num]++;
      }
    }

    const map<int, int>& getResults(){
      return results;
    }

    int getTotalGenerations(){
      return totalGenerations;
    }
};

//printing stats
class Statistics {
private:
    const vector<Item>& items;      
    const map<int, int>& results;  
    int totalGenerations;           

public:
    Statistics(const vector<Item>& items,
               const map<int, int>& results,
               int totalGenerations)
        : items(items), results(results), totalGenerations(totalGenerations) {}

    void operator()() const {
        cout << "\n--- Statistics ---\n";
        int totalFreq = 0;
        for (const auto& item : items) {
            totalFreq += item.frequency;
        }

        double maxDiff = 0.0;

        cout << "Number | Expected | Actual\n";
        for (const auto& item : items) {
            
            double expected = static_cast<double>(item.frequency) / totalFreq;
            int actualCount = 0;
            if (results.count(item.num)) {
                actualCount = results.at(item.num);
            }
            double actual = static_cast<double>(actualCount) / totalGenerations;

            double diff = fabs(expected - actual);
            if (diff > maxDiff) maxDiff = diff;

            cout << "   " << item.num
                 << "   | " << fixed << setprecision(5) << expected
                 << " | " << fixed << setprecision(5) << actual << '\n';
        }

        cout << "---------------------------------\n";
        cout << "Max difference: " << maxDiff << '\n';
    }
};


int main(){

  Data data("input.txt");
  cout<<"Checking printInputData"<<endl;

  data.printInputData();

  cout << "\nchecking getN : " << data.getN() << endl;

  Generator gen(data.getItems());

  Simulation simulate(gen, data.getN());
  simulate();

  for (const auto& [num, times] : simulate.getResults()){
    cout << "Number " << num << " was generated " << times << " times" << '\n';
  }

  cout << "Total generations: " << simulate.getTotalGenerations() << '\n';

   Statistics stats(data.getItems(), simulate.getResults(), simulate.getTotalGenerations());
    stats();

  return 0;
}