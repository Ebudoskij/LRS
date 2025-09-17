#include "Generator.h"

Generator::Generator(const std::vector<Item>& items)
    : data(items), gen(std::random_device{}()) 
{
    int total = 0;
    for (const auto& i : data) {
        total += i.freq;
        prefix.push_back(total);
    }

    dist = std::uniform_int_distribution<int>(1, total);
}

int Generator::operator()() {
    auto rand = dist(gen);
    auto it = std::lower_bound(prefix.begin(), prefix.end(), rand);
    size_t idx = std::distance(prefix.begin(), it);
    return data[idx].num; 
}
