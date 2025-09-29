#include "Generator.h"

Generator::Generator(const std::vector<Item>& items)
    : data(items), gen(std::random_device{}()) {
  // TODO(@Ebudoskij): use as much STL as possible
  std::transform(data.cbegin(), data.cend(), back_inserter(prefix),
                 [](auto item) { return item.freq; });
  std::partial_sum(prefix.cbegin(), prefix.cend(), prefix.begin());
  dist = std::uniform_int_distribution<int>(1, prefix.back());
}

int Generator::operator()() {
  // TODO(@Ebudoskij): use as much const as possible
  const auto it{std::lower_bound(prefix.begin(), prefix.end(), dist(gen))};
  return data[std::distance(prefix.begin(), it)].num;
}
