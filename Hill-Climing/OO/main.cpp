#include <iostream>
#include "hc.h"


using namespace std;

int score = 0;

int main(int argc, char *argv[])
{
	int iter = atoi(argv[1]);
	int bits = atoi(argv[2]);

    hc hill_climbing;
	
	vector<int> v = hill_climbing.init(bits, score);
	clock_t start, finish;
	double duration;
	
	cout << "now score:" << score << endl;
	start = clock();
	while( iter-- )
	{
		if( score==bits )
			break;
		int trans_num, tmp_score;
		cout << "\n-\n";
		//transition
		trans_num = hill_climbing.transition( v, bits );
		//evaluation
		tmp_score = hill_climbing.evaluation( v, trans_num );
		//determination
		hill_climbing.determination( v, trans_num, tmp_score, score );
		for(int i=0; i<bits; i++)
			cout << v[i];
		cout << endl;
	}
	finish = clock();
	
	duration = (double)(finish - start);
	cout << "total use time : " << duration << " millisec." << endl;
		
	
return 0;
}