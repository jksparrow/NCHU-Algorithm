#include <vector>
#include <ctime>
using namespace std;

class TS
{
private:
public:
  vector<int> init(int, int &);
  int get_tabu(vector<int> &vec, vector<string> &tabulist, int);
  int transition(vector<int> &vec, int);
  int evaluation(vector<int> &vec);
  int determination(vector<int> &vec, vector<string> &tabulist, int, int, int &);
};