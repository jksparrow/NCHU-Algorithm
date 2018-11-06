#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "TS.h"

vector<int> TS::init(int bits, int &score)
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

	return myNumber;
}

int TS::get_tabu(vector<int> &vec, vector<string> &tabulist, int bits)
{
	stringstream ss;
	string road, temp;
	road.empty();
	temp.empty();
	int flag;

	for (int i = 0; i < bits; i++) //撠楝敺?ss敺emp?瑕??郢oad?脣?
	{
		ss.clear();
		ss << vec[i];
		ss >> temp;
		road.append(temp);
	}

	vector<string>::iterator it = find(tabulist.begin(), tabulist.end(), road); //?蓉abu鋆⊿?暹?瘝?摮?oad

	if (it != tabulist.end()) //find the same road in TabuList
		flag = 0;			  //continue
	else
	{
		tabulist.push_back(road);
		flag = 1; //need evaluation
	}

	return flag;
}

int TS::transition(vector<int> &vec, int bits)
{
	int trans_num = rand() % bits;
	vec[trans_num] = !vec[trans_num];

	return trans_num;
}

int TS::evaluation(vector<int> &vec)
{
	int tmp_score = 0;
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (*it == 1)
			tmp_score++;
	}

	return tmp_score;
}

int TS::determination(vector<int> &vec, vector<string> &tabulist, int trans_num, int tmp_score, int &score)
{
	if (tmp_score > score)
	{
		//cout << "original score = " << score << ", tmp_score = " << tmp_score << endl;
		score = tmp_score;
		if (tabulist.size() > 7) //閮剖?TabuList?憭?6??頞??行?蝚砌???
			tabulist.erase(tabulist.begin());
	}
	else
	{
		vec[trans_num] = !vec[trans_num];
		if (tabulist.size() > 7) //閮剖?TabuList?憭?6??頞??行?蝚砌???
			tabulist.erase(tabulist.begin());
	}
	return score;
}