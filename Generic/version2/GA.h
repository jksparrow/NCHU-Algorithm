#include <vector>
#include <ctime>
using namespace std;

class GA
{
private:
public:
  void show(vector<vector<int>> &vec2, int chromesome_number);
  vector<int> init(int bits);
  int fitness(vector<int> &vec1, int bits);
  vector<vector<int>> select(vector<vector<int>> &vec2, vector<int> &vec_fitness, vector<int> &cal_roulette_p, int chromesome_number, int Roulette_sum);
  vector<vector<int>> crossover(vector<vector<int>> &vec2, int chromesome_number, int bits);
  vector<vector<int>> mutate(vector<vector<int>> &vec2, int chromesome_number, int bits);
  int fitness_2(vector<vector<int>> &vec2, int chromesome_number, int bits, int bestValue);

};