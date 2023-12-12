#include <vector>

using namespace std;

struct ICombinationsValue
{
  string id;
  double value;
};

vector<vector<ICombinationsValue>> combineByValue(const vector<ICombinationsValue> &list, double target);
