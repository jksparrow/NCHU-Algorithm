#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

vector<int> init(int , int );
int transition(vector <int> &vec, int );
int evaluation(vector <int> &vec);
int determination(vector <int> &vec, int , int , int );

int main(int argc, char *argv[])
{
	//ex input:./search 500 100 30 (iteration/bits/runs)
	int iter = atoi(argv[1]);
	int bits = atoi(argv[2]);
	int runs = atoi(argv[3]);
	
    fstream fp;
    fp.open("Output.csv", ios::out);
    fp<< "Iteration" << "," << "Value" << endl;
    fp.close();
	//clock_t start, finish;
	//start = clock();
	for(int i=0; i<=iter; i+=10)
	{
		vector<int> average;
		for(int j=0; j<runs; j++)
		{
			int score = 0, trans_num = 0, tmp_score = 0, cost = 0;
			vector<int> v = init(bits, score);
			while( cost < i )
			{
				if( cost != 0 ) {
					//transition
					trans_num = transition( v, bits );
				}
				//evaluation
				tmp_score = evaluation( v );
				//determination
				score = determination( v, trans_num, tmp_score, score );

				cost++;
			}
			average.push_back( score );
		}
		int sum = 0;
		for(vector<int>::iterator it = average.begin(); it!=average.end(); it++) {
			sum += *it;
		}

	//finish = clock();
	//double duration = (double)(finish - start);
	//cout << "total use time : " << duration << " millisec." << endl;

    fstream fp;
    fp.open("Output.csv", ios::out|ios::app);
    fp << i << "," << sum/runs << endl;
    fp.close();
    cout <<"Iter: " << i << "  AvgMax: " << sum/runs << endl;
	}	
	
return 0;
}

vector<int> init(int bits, int score)
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

int transition(vector <int> &vec, int bits)
{
	int trans_num = rand() % bits;
	cout << "trans_num = " << trans_num << endl;
	vec[trans_num] = !vec[trans_num];	
	
	return trans_num;
}

int evaluation(vector <int> &vec)
{
	int tmp_score = 0;
	for(vector<int>::iterator it=vec.begin(); it!=vec.end(); it++) {
		if( *it==1 )
			tmp_score++;
	}

	return tmp_score;	
}

int determination(vector <int> &vec, int trans_num, int tmp_score, int score)
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
    return score;
}
