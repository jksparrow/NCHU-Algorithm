#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> vec(100,0);
	int point = 0;
	int bestpoint = 0;
	int c = 0;
	
	while( bestpoint<100 ) {
		vec[99]++;
		for(int i=99; i>=0; i--) {
			if(c+vec[i]==1) {
				c = 0;
				vec[i] = 1;
			}
			else if(c+vec[i]==2) {
				c = 1;
				vec[i] = 0;	
			}
			else {
				c = 0;
				vec[i] = 0;
				break;
			}
		}
		
		//看單round有幾個1 
		for(int j=0; j<100; j++) {
			cout << vec[j];
			if( vec[j]==1 )
				point++;
		}
		cout << endl;
		
		if( point > bestpoint ) {
			bestpoint = point;
			point = 0;
		}
		else
			point = 0;
			
		cout << "point: " << bestpoint << endl;
	}
	
	return 0;
}
