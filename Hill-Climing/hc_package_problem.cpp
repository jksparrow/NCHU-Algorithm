#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
vector<int> init();
vector<int> getWeight();
vector<int> getProfit();
int transition(int take_num);
int evaluation_determination(vector <int> &v, vector <int> &w, vector <int> &p, int take_num, int total_weight, int total_profit, int capacity);

int main()
{
	int t = 1000; // run 1000 times
	int capacity = 6404180;
	int take_num;
	vector<int> v = init();
	vector<int> w = getWeight();
	vector<int> p = getProfit();
	clock_t start, finish;
	double duration;	
	
	int total_weight = v[v.size()-2];
	int total_profit = v[v.size()-1];
	cout << "first get total weight: " << total_weight << endl;
	cout << "first get total profit: " << total_profit << endl;
	cout << "first taking number:" << endl;
	for(vector<int>::iterator it=v.begin(); it!=v.end(); it++)
		cout << *it <<endl;
	
	start = clock();
	while( t-- )
	{
		//transition
		take_num = rand() % 24;
		cout << "take number " << take_num << " bag."<< endl;
		
		//evaluation&determination
		if( v[take_num]==0 ) // no take
		{
		    total_weight += w.at(take_num);
		    if( total_weight > capacity )
		    {
		        total_weight -= w.at(take_num)   ;
		    }
		    else
		    {
		        v.erase(v.begin()+take_num);
			    v.insert(v.begin()+take_num,1);
			    total_profit += p.at(take_num);
		    }
		}
		else
			cout << "item already taken.\n";

		cout << "Get weight: " << total_weight << endl;
		cout << "Get profit: " << total_profit << endl;
		cout << "\n- \n" ;
	}
	finish = clock();
	
	duration = (double)(finish - start);
	cout << "total use time : " << duration << " millisec." << endl;

return 0;
}

vector<int> init()
{
	vector<int> myNumber;
	vector<int> w = getWeight();
	vector<int> p = getProfit();
	myNumber.clear();
	srand (time(NULL));
	
	int rnum, input;
	int total_weight = 0;
	int total_profit = 0;
	int capacity = 6404180;
	

    for( int i=0; i<24; i++ )
	{
	    rnum = rand() % 2;
	    myNumber.push_back(rnum);
	    if( rnum==1 ) // random 1 take
	    {
	        total_weight += w[i];
	        total_profit += p[i];
	    }
	}
	
	if( total_weight > capacity )
	{
		cout << "exceed capacity." << endl;
		cout << "total_weight = " << total_weight << ", init again."<< endl;
		init();	
	}
	else
	{
	    myNumber.push_back(total_weight);
	    myNumber.push_back(total_profit);
	}
	
	return myNumber;
}

vector<int> getWeight()
{
	vector<int> weight;

	weight.push_back(382745), weight.push_back(799601), weight.push_back(909247), weight.push_back(729069), weight.push_back(467902), weight.push_back(44328), 
	weight.push_back(34610), weight.push_back(698150), weight.push_back(823460), weight.push_back(903959), weight.push_back(853665), weight.push_back(551830), 
	weight.push_back(610856), weight.push_back(670702), weight.push_back(488960), weight.push_back(951111), weight.push_back(323046), weight.push_back(446298), 
	weight.push_back(931161), weight.push_back(31385), weight.push_back(496951), weight.push_back(264724), weight.push_back(224916), weight.push_back(169684);

	return weight;
}

vector<int> getProfit()
{
	vector<int> profit;
	
	profit.push_back(825594), profit.push_back(1677009), profit.push_back(1676628), profit.push_back(1523970), profit.push_back(943972), profit.push_back(97426), 
	profit.push_back(69666), profit.push_back(1296457), profit.push_back(1679693), profit.push_back(1902996), profit.push_back(1844992), profit.push_back(1049289), 
	profit.push_back(1252836), profit.push_back(1319836), profit.push_back(953277), profit.push_back(2067538), profit.push_back(675367), profit.push_back(853655), 
	profit.push_back(1826027), profit.push_back(65731), profit.push_back(901489), profit.push_back(577243), profit.push_back(466257), profit.push_back(369261);
	
	return profit;
}
