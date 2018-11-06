#include <iostream>
#include <fstream>
#include "TS.h"

using namespace std;

int score = 0;

int main(int argc, char *argv[])
{
	// 範例執行 ./search 500 100 30
	int iter = atoi(argv[1]);
	int bits = atoi(argv[2]);
	int runs = atoi(argv[3]);

	TS ts;

	fstream fp;
	fp.open("Output.csv", ios::out);
	fp << "Iteration"
	   << ","
	   << "Value" << endl;
	fp.close();

	//clock_t start, finish;
	//start = clock();
	for (int i = 0; i <= iter; i += 10)
	{
		vector<int> average;
		for (int j = 0; j < runs; j++)
		{
			int trans_num = 0, tmp_score = 0, score = 0, cost = 0;

			vector<string> tabulist;
			tabulist.clear();
			vector<int> v = ts.init(bits, score);
			int flag = ts.get_tabu(v, tabulist, bits);

			while (cost < i)
			{
				//transition
				trans_num = ts.transition(v, bits);
				//get_tabu
				flag = ts.get_tabu(v, tabulist, bits);
				if (flag)
				{
					//evaluation
					tmp_score = ts.evaluation(v);
					//determination
					score = ts.determination(v, tabulist, trans_num, tmp_score, score);
				}
				else
				{
					v[trans_num] = !v[trans_num];
				}
				cost++;
			}
			average.push_back(score);
		}
		int sum = 0;
		for (auto it = average.begin(); it != average.end(); it++)
		{
			sum += *it;
		}

		fstream fp;
		fp.open("Output.csv", ios::out | ios::app);
		fp << i << "," << sum / runs << endl;
		fp.close();
		cout << "Iter: " << i << "  AvgMax: " << sum / runs << endl;
	}

	return 0;
}