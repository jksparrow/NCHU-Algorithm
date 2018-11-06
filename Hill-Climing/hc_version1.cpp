#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;
vector<int> init(int bits);
int transition(vector<int> &vec, int bits);
int evaluation(vector<int> &vec);
void determination(vector<int> &vec, int trans_num, int tmp_score);

int score = 0;

int main(int argc, char *argv[])
{
	//ex input:./search 500 100 (iteration/bits/runs)
	int iter = atoi(argv[1]);
	int bits = atoi(argv[2]);

	vector<int> v = init(bits);
	clock_t start, finish;
	double duration;

	cout << "now score:" << score << endl;
	start = clock();
	while (iter--)
	{
		if (score == bits)
		{
			cout << "iteration : " << iter << endl;
			break;
		}
		int trans_num, tmp_score;
		//transition
		trans_num = transition(v, bits);
		//evaluation
		tmp_score = evaluation(v);
		//determination
		determination(v, trans_num, tmp_score);
		for (int i = 0; i < bits; i++)
			cout << v[i];
		cout << endl;
	}
	finish = clock();

	duration = (double)(finish - start);
	cout << "total use time : " << duration << " millisec." << endl;

	return 0;
}

vector<int> init(int bits)
{
	vector<int> myNumber;
	myNumber.clear();
	srand(time(NULL));

	int num;

	for (int i = 0; i < bits; i++)
	{
		num = rand() % 2;
		if (num == 1)
			score++;
		myNumber.push_back(num);
	}
	cout << "Init number:" << endl;
	for (vector<int>::iterator it = myNumber.begin(); it != myNumber.end(); it++)
		cout << *it;
	cout << endl;

	return myNumber;
}

int transition(vector<int> &vec, int bits)
{
	int trans_num = rand() % bits;
	cout << "trans_num = " << trans_num << endl;
	vec[trans_num] = !vec[trans_num];

	return trans_num;
}

int evaluation(vector<int> &vec)
{
	int tmp_score = 0;
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (*it == 1)
			tmp_score++;
	}

	return tmp_score;
}

void determination(vector<int> &vec, int trans_num, int tmp_score)
{
	if (tmp_score > score)
	{
		cout << "original score = " << score << ", tmp_score = " << tmp_score << endl;
		score = tmp_score;
	}
	else
	{
		vec[trans_num] = !vec[trans_num];
	}
}
