
using namespace std;

class MultiThread{
  private:
    vector<int> data;
  public:
    MultiThread(vector<int>& data): data(data){};

    int operator()();
}