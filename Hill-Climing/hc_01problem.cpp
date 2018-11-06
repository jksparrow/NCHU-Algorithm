#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
vector<int> init();
int transition(int trans_num);
int evaluation(vector <int> &vec, int trans_num, int tmp_score);
void determination(vector <int> &vec, int trans_num, int tmp_score);

int score = 0;
int iter, bits;

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; ++i) {
    	printf("[%d] %s\n", i, argv[i]);
	}
	iter = argv[1];
	bits = argv[2];
	
	vector<int> v = init();
	clock_t start, finish;
	double duration;
	int count=0;
	
	cout << "now score:" << score << endl;
	start = clock();
	while( score!=100 )
	{
		int trans_num, tmp_score=0;
		cout << "\n-\n";
		//transition
		trans_num = transition(trans_num);
		//evaluation
		trans_num, tmp_score = evaluation( v, trans_num, tmp_score );
		//determination
		determination( v, trans_num, tmp_score );
		count++;
	}
	finish = clock();
	
	duration = (double)(finish - start);
	cout << "use " << count << " times to get optimal." << endl;
	cout << "total use time : " << duration << " millisec." << endl;
		
	
	
return 0;
}

vector<int> init()
{
	vector<int> myNumber;
	srand (time(NULL));
	
	int num;
    
    for( int i=0; i<100; i++ )
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

int transition(int trans_num)
{
	trans_num = rand() % 100;
	cout << "trans_num = " << trans_num << endl;	
	
	return trans_num;
}

int evaluation(vector <int> &vec, int trans_num, int tmp_score)
{
	
}

void determination(vector <int> &vec, int trans_num, int tmp_score)
{
	if( tmp_score > score )
		{
			cout << "original score = " << score << ", tmp_score = " << tmp_score << endl;
			score = tmp_score;	
		}
	else
	{
		//cout << "this transition no better than last one." << endl;
		vec.erase(vec.begin()+trans_num); // change back
		vec.insert(vec.begin()+trans_num,1);
	}
}
