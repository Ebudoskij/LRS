#include "Generator.h"

Generator::Generator(const std::vector<Item>& items)
    : data(items), gen(std::random_device{}()) 
{
    int total = 0;
    for (auto& i : data) {
        total += i.frequency;
        prefix.push_back(total);
    }

    dist = std::uniform_int_distribution<int>(1, total);
}

Item Generator::operator()() {
    int rand = dist(gen);
    for (size_t i = 0; i < prefix.size(); ++i) {
        if (rand <= prefix[i]) {
            return data[i];
        }
    }
    return data.back(); 
}
