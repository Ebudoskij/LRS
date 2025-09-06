#include <string>
#include <map>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
class Simulation{};

//printing stats
class Statistics{};


int main(){

  Data data("input.txt");
  cout<<"Checking printInputData"<<endl;
  '\n';
  data.printInputData();

  cout << "\nchecking getN : " << data.getN() << endl;


  const auto& items = data.getItems();
        cout << "\nChecking the first element: "
             << items[0].num << " (freq = " << items[0].frequency << ")"<<endl;


  return 0;
}