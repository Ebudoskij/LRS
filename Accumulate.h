
#include <vector>

using namespace std;

class MultiThread{
  private:
    vector<int> data;
    int threads;
  public:
    MultiThread(vector<int>& data, size_t threads): data(data), threads(threads){};

    int operator()();
};