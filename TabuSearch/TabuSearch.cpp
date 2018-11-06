#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

vector<int> init(int, int);
int transition(vector<int> &vec, int);
int evaluation(vector<int> &vec);
int determination(vector<int> &vec, vector<string> &tabulist, int, int, int);
int get_tabu(vector<int> &vec, vector<string> &tabulist, int);

int main(int argc, char *argv[])
{
	//./search 500 100
	int iter = atoi(argv[1]);
	int bits = atoi(argv[2]);
	int score = 0;

	vector<string> tabulist;
	tabulist.clear();
	vector<int> v = init(bits, score);
	cout << "Frist score:" << score << endl;
	int flag = get_tabu(v, tabulist, bits);

	clock_t start, finish;
	start = clock();
	while (iter--)
	{
		int trans_num = 0, tmp_score = 0;
		//transition
		trans_num = transition(v, bits);
		//get_tabu
		flag = get_tabu(v, tabulist, bits);
		if (flag)
		{ //不在tabulist內要去評估
			//evaluation
			tmp_score = evaluation(v);
			//determination
			score = determination(v, tabulist, trans_num, tmp_score, score);
		}
		else
		{
			v[trans_num] = !v[trans_num];
		}
		/*
		for (int i = 0; i < bits; i++)
			cout << v[i];
		cout << endl;
		*/
		cout << "score : " << score << endl;
	}
	finish = clock();
	cout << "score : " << score << endl;
	double duration = (double)(finish - start);
	cout << "total use time : " << duration << " millisec." << endl;

	return 0;
}

vector<int> init(int bits, int score)
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

int get_tabu(vector<int> &vec, vector<string> &tabulist, int bits)
{
	stringstream ss;
	string road, temp;
	road.empty();
	temp.empty();
	int flag;

	for (int i = 0; i < bits; i++) //將路徑透過ss從temp擷取到road儲存
	{
		ss.clear();
		ss << vec[i];
		ss >> temp;
		road.append(temp);
	}

	vector<string>::iterator it = find(tabulist.begin(), tabulist.end(), road); //去Tabu裡面找有沒有存在的road

	if (it != tabulist.end()) //find the same road in TabuList
		flag = 0;			  //continue
	else
	{
		tabulist.push_back(road);
		flag = 1; //need evaluation
	}

	return flag;
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

int determination(vector<int> &vec, vector<string> &tabulist, int trans_num, int tmp_score, int score)
{
	if (tmp_score > score)
	{
		//cout << "original score = " << score << ", tmp_score = " << tmp_score << endl;
		score = tmp_score;
		if (tabulist.size() > 7) //設定TabuList最多存6個，超過擦掉第一個
			tabulist.erase(tabulist.begin());
	}
	else
	{
		vec[trans_num] = !vec[trans_num];
		if (tabulist.size() > 7) //設定TabuList最多存6個，超過擦掉第一個
			tabulist.erase(tabulist.begin());
	}
	return score;
}
