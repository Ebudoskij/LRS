#include "Accumulate.h"

#include <thread>
#include <iostream>
#include <algorithm>

int MultiThread::operator()() {
    int n = data.size();
    if (n == 0) return std::numeric_limits<int>::max();

    int threadsNum = std::min(threads, n);
    std::vector<int> mins(threadsNum);

    int blockSize = n / threadsNum;
    int remainder = n % threadsNum;
    int start = 0;

    {
      std::vector<std::jthread> jthreads;
      jthreads.reserve(threadsNum);

      for (int i = 0; i < threadsNum; ++i) {
            int end = start + blockSize + (i < remainder ? 1 : 0);

            jthreads.emplace_back(
                [&, i, s = start, e = end](std::stop_token) {
                    mins[i] = *std::min_element(data.data() + s, data.data() + e);
                }
            );

            start = end;
        }
    }

    return *std::min_element(mins.begin(), mins.end());
}