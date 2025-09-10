#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <iostream>

struct Item {
    int num;
    int frequency;
    Item(int n, int f) : num(n), frequency(f) {}
};

class Data {
private:
    int n;                       
    std::vector<Item> items;   

public:
    explicit Data(const std::string& filename);

    int getN() const;
    const std::vector<Item>& getItems() const;

    void printInputData() const;

private:
    void readFromFile(const std::string& filename);
};

#endif
