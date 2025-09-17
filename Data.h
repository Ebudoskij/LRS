#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <iostream>

struct Item {
    int num;
    int freq;
    Item(int n, int f) : num(n), freq(f) {}
};

class Data {
private:
    int n{};
    std::vector<Item> items;

public:
    Data() = default;  
    void readFromFile(const std::string& filename);

    int getN() const;
    const std::vector<Item>& getItems() const;
    std::ostream& formatInputData(std::ostream& os) const;
    void printInputData() const; 
    friend std::ostream& operator<<(std::ostream& os, const Data& data);
};

#endif // DATA_H
