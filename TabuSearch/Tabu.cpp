#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

vector<int> init(int);
vector<int> transition(vector<int> &r, int *, int *, int);
int evaluation(vector<int> &r, int *, int *, int);
int determination(vector<int> &r, vector<string> &TabuList, int distance, int bestDistance, int change_num1, int change_num2);
int cal_dist(vector<int> &r, int *, int *, int);
int get_Tabu(vector<int> &r, vector<string> &TabuList, int);
int C, D, I, r;

int main(int argc, char *argv[])
{
	//範例輸入: ./檔名 座標數目 每組有多少資料 迭代次數 單run次數 51 3 1000 30
	C = atoi(argv[1]); //座標數目
	D = atoi(argv[2]); //一列有多少資料數
	I = atoi(argv[3]); //迭代次數
	r = atoi(argv[4]); //單run次數

	printf("total coordinate %d points.\neach set have %d datas.\niterator %d times.\nrun %d time.\n", C, D, I, r);

	int tmpI, tmpR = r;

	FILE *fp = fopen("eil51.txt", "r");
	int coordinate[C][D];
	int x[C];
	int y[C];

	for (int i = 0; i < C; i++)
		for (int j = 0; j < D; j++)
			fscanf(fp, "%d", &coordinate[i][j]);

	for (int i = 0; i < C; i++)
	{
		x[i] = coordinate[i][1];
		y[i] = coordinate[i][2];
	}

	int c_num1, c_num2, flag;
	int distance, bestDistance;
	double average_val;
	vector<string> TabuList; //create TabuList
	srand(time(NULL));

	while (r--) //R = run的次數
	{
		distance = 0, bestDistance = 0; //每次都要初始化

		TabuList.clear();
		vector<int> R = init(C);
		flag = get_Tabu(R, TabuList, C); //將init的資料放到TabuList
		distance = cal_dist(R, x, y, C); //init的初始距離
		bestDistance = distance;

		tmpI = I;	  // tmpI取得Iteration
		while (tmpI--) //Iteration次數
		{
			//transition
			vector<int> change = transition(R, x, y, C);
			c_num1 = change.at(0); //取出交換的點一
			c_num2 = change.at(1); //取出交換的點二
			change.clear();
			//get_Tabu
			flag = get_Tabu(R, TabuList, C);
			if (!flag) //已經走過
				continue;
			//evaluation
			distance = evaluation(R, x, y, C);
			//determination
			bestDistance = determination(R, TabuList, distance, bestDistance, c_num1, c_num2);
		}
		cout << "bestDistance: " << bestDistance << endl;
		average_val += bestDistance;
		//cout << average_val << endl;
	}
	cout << "average_val: " << (double)(average_val / tmpR) << endl;

	return 0;
}

//transition
vector<int> transition(vector<int> &r, int *arr_x, int *arr_y, int C)
{
	int change_num1, change_num2;
	int tmpr1, tmpr2;
	//一次選兩個點交換路徑
	change_num1 = rand() % C;
	change_num2 = rand() % C;

	do
	{
		change_num2 = rand() % C;
	} while (change_num2 == change_num1);
	//點的值
	tmpr1 = r[change_num1];
	tmpr2 = r[change_num2];
	//交換路徑
	r.erase(r.begin() + change_num1);
	r.insert(r.begin() + change_num1, tmpr2);
	r.erase(r.begin() + change_num2);
	r.insert(r.begin() + change_num2, tmpr1);

	vector<int> change;
	change.push_back(change_num1);
	change.push_back(change_num2);

	return change;
}
//evaluation
int evaluation(vector<int> &r, int *arr_x, int *arr_y, int C)
{
	int distance = 0;
	distance = cal_dist(r, arr_x, arr_y, C);

	return distance;
}
//determination
int determination(vector<int> &r, vector<string> &TabuList, int distance, int bestDistance, int change_num1, int change_num2)
{
	if (distance < bestDistance) //路徑較短較佳
	{
		bestDistance = distance;
		if (TabuList.size() >= 6) //設定TabuList最多存6個，超過擦掉第一個
			TabuList.erase(TabuList.begin());
	}
	else //結果沒有比較好要將值換回去
	{
		int tmpr1, tmpr2;
		tmpr1 = r[change_num1];
		tmpr2 = r[change_num2];

		r.erase(r.begin() + change_num1);
		r.insert(r.begin() + change_num1, tmpr2);
		r.erase(r.begin() + change_num2);
		r.insert(r.begin() + change_num2, tmpr1);

		TabuList.erase(TabuList.end() - 1);
	}
	return bestDistance;
}
//calculate distance
int cal_dist(vector<int> &r, int *arr_x, int *arr_y, int C)
{
	int dis = 0;
	for (int i = 1; i < C; i++)
	{
		dis += sqrt((arr_x[r[i]] - arr_x[r[i - 1]]) * (arr_x[r[i]] - arr_x[r[i - 1]]) + (arr_y[r[i]] - arr_y[r[i - 1]]) * (arr_y[r[i]] - arr_y[r[i - 1]]));
	}

	dis += sqrt((arr_x[r[0]] - arr_x[r[C - 1]]) * (arr_x[r[0]] - arr_x[r[C - 1]]) + (arr_y[r[0]] - arr_y[r[C - 1]]) * (arr_y[r[0]] - arr_y[r[C - 1]]));

	return dis;
}
//init
vector<int> init(int C)
{
	vector<int> route;
	//route.clear();

	int num;
	for (int i = 0; i < C; i++)
	{
		num = rand() % C;
		route.push_back(num);
	}
	cout << "Init route:" << endl;
	for (vector<int>::iterator it = route.begin(); it != route.end(); it++)
		cout << *it << " ";
	cout << endl;

	return route;
}
//get TabuList
int get_Tabu(vector<int> &R, vector<string> &TabuList, int C)
{
	stringstream ss;
	string road, temp;
	road.empty();
	temp.empty();
	int flag;

	for (int i = 0; i < C; i++) //將路徑透過ss從temp擷取到road儲存
	{
		ss.clear();
		ss << R[i];
		ss >> temp;
		road.append(temp);
	}

	vector<string>::iterator it = find(TabuList.begin(), TabuList.end(), road); //去Tabu裡面找有沒有存在的road

	if (it != TabuList.end()) //find the same road in TabuList
		flag = 0;			  //continue
	else
	{
		TabuList.push_back(road);
		flag = 1; //need evaluation
	}

	return flag;
}