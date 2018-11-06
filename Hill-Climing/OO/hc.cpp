#include <iostream>
#include <string>
#include <cstdlib>
#include "hc.h"

vector<int> hc::init(int bits, int &score)
{
	vector<int> myNumber;
	myNumber.clear();
	srand (time(NULL));
	
	int num;
    
    for( int i=0; i<bits; i++ )
	{
	    num = rand() % 2;
	    if( num==1 )
	    	score++;
	    myNumber.push_back(num);
	}
	cout << "Init number:" << endl;
	for(vector<int>::iterator it=myNumber.begin(); it!=myNumber.end(); it++)
		cout << *it;	
	cout << endl;
	
	return myNumber;
}

int hc::transition(vector <int> &vec, int bits)
{
	int trans_num = rand() % bits;
	cout << "trans_num = " << trans_num << endl;
	vec[trans_num] = !vec[trans_num];	
	
	return trans_num;
}

int hc::evaluation(vector <int> &vec, int trans_num)
{
	int tmp_score = 0;
	for(vector<int>::iterator it=vec.begin(); it!=vec.end(); it++) {
		if( *it==1 )
			tmp_score++;
	}

	return tmp_score;	
}

void hc::determination(vector <int> &vec, int trans_num, int tmp_score, int &score)
{
	if( tmp_score > score )
		{
			cout << "original score = " << score << ", tmp_score = " << tmp_score << endl;
			score = tmp_score;	
		}
	else
	{
		vec[trans_num] = !vec[trans_num];
	}
}