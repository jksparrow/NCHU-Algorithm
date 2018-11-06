#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

#define tao_ 1.0
#define alpha 1.0
#define beta 5.0
#define lol 0.5
#define Q 100

using namespace std;

vector<int> init(int ant, int begin);
vector<double> Best_length(vector<vector<int>> &ant_route, vector<vector<double>> &dis_table, int ant, double &bestValue);
void create_tao(vector<vector<double>> &Tao, int ant, double tao);
void cal_distance(vector<int> &x, vector<int> &y, vector<vector<double>> &dis_table, int ant);
void create_delta_tao(vector<vector<double>> &delta_Tao, int ant);
void Moving(vector<vector<int>> &ant_route, vector<vector<int>> &list, vector<vector<double>> &dis_table, vector<vector<double>> &Tao, int ant);
void update(vector<vector<int>> &ant_route, vector<double> &sum_route, vector<vector<double>> &Tao, vector<vector<double>> &delta_Tao, int ant);

int main(int argc, char *argv[])
{
    //./search 51 10000 = ant iteration
    int ant = atoi(argv[1]);
    int iter = atoi(argv[2]);

    //read file
    fstream fin("eil51.txt");
    int coordinate[ant][3];
    if (!fin)
    {
        cout << "fail to read file.";
        return 0;
    }
    else
    {
        for (int i = 0; i < ant; i++)
            for (int j = 0; j < 3; j++)
            {
                fin >> coordinate[i][j];
            }
    }

    // create distance table
    vector<int> x;
    vector<int> y;
    vector<vector<double>> dis_table;
    x.push_back(0);
    y.push_back(0);
    for (int i = 0; i <= ant; i++)
    {
        x.push_back(coordinate[i][1]);
        y.push_back(coordinate[i][2]);
        //cout << "x = " << x[i] << " y = " << y[i] << endl;
    }
    cal_distance(x, y, dis_table, ant);

    /*//check 52*52 dis_table
    for (int i = 0; i <= ant; i++)
    {
        for (int j = 0; j <= ant; j++)
        {
            cout << dis_table[i][j] << " ";
        }
        cout << endl;
    }
    */

    srand(time(NULL));

    //init tao
    vector<vector<double>> Tao;
    create_tao(Tao, ant, tao_);

    //check Tao table
    /*
    for (int i = 0; i < Tao.size(); i++)
    {
        for (int j = 0; j < Tao.size(); j++)
        {
            cout << Tao[i][j] << " ";
        }
        cout << endl;
    }
    */

    double bestValue = 99999; // set the shortest route
    //main loop
    while (iter--)
    {
        //init ant's path
        vector<int> path;
        vector<vector<int>> ant_route;

        for (int i = 1; i <= ant; i++)
        {
            path = init(ant, i);
            ant_route.push_back(path);
        }

        /*//check ant_route
        for (int i = 0; i < ant; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                cout << ant_route[i][j] << " ";
            }
            cout << endl;
        }
        */

        //init list for ant to choose
        vector<vector<int>> list;
        for (int i = 1; i <= ant; i++)
        {
            vector<int> to_list;
            for (int j = 1; j <= ant; j++)
            {
                if (i != j)
                {
                    to_list.push_back(j);
                }
            }
            list.push_back(to_list);
        }

        /* //check list
        for (int i = 0; i < ant; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                cout << list[i][j] << " ";
            }
            cout << endl;
        }
        */

        Moving(ant_route, list, dis_table, Tao, ant);

        /*//check 51*51 ant_route
        for (int i = 0; i < ant; i++)
        {
            for (int j = 0; j < ant; j++)
            {
                cout << ant_route[i][j] << " ";
            }
            cout << endl;
        }
        */

        //cout << "ant_route size = " << ant_route.size() << endl;
        vector<double> sum_route;
        sum_route = Best_length(ant_route, dis_table, ant, bestValue);

        /*//check sum_route
        for (int i = 0; i < sum_route.size(); i++)
        {
            cout << i + 1 << " : " << sum_route[i] << endl;
        }
        */

        cout << "\nIteration " << iter << " done." << endl;
        cout << "shortest path length = " << bestValue << endl;

        //init delta_tao table
        vector<vector<double>> delta_Tao;
        create_delta_tao(delta_Tao, ant);

        //cout << "tao size : " << Tao.size() << endl;
        //cout << "delta tao size : " << delta_Tao.size() << endl;

        /*//check delta_tao table
        for (int i = 0; i < ant; i++)
        {
            for (int j = 0; j < ant; j++)
            {
                cout << delta_Tao[i][j] << " ";
            }
            cout << endl;
        }
        */

        update(ant_route, sum_route, Tao, delta_Tao, ant);

        /*//check updated delta_tao table
        for (int i = 0; i <= ant; i++)
        {
            for (int j = 0; j <= ant; j++)
            {
                cout << delta_Tao[i][j] << " ";
            }
            cout << endl;
        }
        */

        //sum original Tao table and delta_Tao table together
        for (int i = 0; i <= ant; i++)
        {
            for (int j = 0; j <= ant; j++)
            {
                Tao[i][j] = Tao[i][j] + delta_Tao[i][j];
            }
        }

        cout << "---" << endl;
    }
    return 0;
}

void cal_distance(vector<int> &x, vector<int> &y, vector<vector<double>> &dis_table, int ant)
{
    double value = 0;

    for (int i = 0; i <= ant; i++)
    {
        vector<double> dis;
        for (int j = 0; j <= ant; j++)
        {
            if (i == 0 || j == 0)
            {
                dis.push_back(0);
                continue;
            }
            else if (i == j) //diagonal line is zero
                dis.push_back(0);
            else
            {
                value = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                dis.push_back(value);
            }
        }
        dis_table.push_back(dis);
    }
} //end cal_distance funciton

vector<int> init(int ant, int begin)
{
    vector<int> r;
    r.push_back(begin);

    return r;
} //end init function

void create_tao(vector<vector<double>> &Tao, int ant, double tao)
{
    for (int i = 0; i <= ant; i++)
    {
        vector<double> r;
        for (int j = 0; j <= ant; j++)
        {
            if (i == 0 || j == 0)
                r.push_back(0);
            else
                r.push_back(tao);
        }
        Tao.push_back(r);
    }
} //end create_tao function

void Moving(vector<vector<int>> &ant_route, vector<vector<int>> &list, vector<vector<double>> &dis_table, vector<vector<double>> &Tao, int ant)
{
    for (int i = 0; i < ant; i++)
    {
        int stand = i + 1;
        //if (stand == 51) // be careful about stand position
        //    stand -= 1;
        int nextCity = 0;
        for (int j = 0; j < ant - 1; j++) //ramein 50 position to choose
        {
            double SumP = 0;
            vector<double> roulette_p;
            roulette_p.push_back(0);
            double random = (double)rand() / (RAND_MAX + 1.0);
            //cout << "r = " << random << endl;
            //cout << "list size = " << list[i].size() << endl;
            //cout << "stand = " << stand << endl;
            for (int k = 0; k < list[i].size(); k++)
            {
                //cout << k + 1 << "  ";
                //cout << "list value = " << list[i][k] << endl;
                //cout << Tao[stand][list[i][k]] << "   /  ";
                //cout << dis_table[stand][list[i][k]] << endl;
                double ans = pow(Tao[stand][list[i][k]], alpha) * pow(1 / dis_table[stand][list[i][k]], beta);
                SumP += ans;
                roulette_p.push_back(SumP);
            }

            /*
            cout << "sum = " << SumP << endl;
            cout << "size of roulette  = " << roulette_p.size() << endl;
            for (int L = 0; L < roulette_p.size(); L++)
            {
                cout << L << "  ";
                cout << roulette_p[L] / SumP << endl;
            }
            */

            for (int L = 1; L <= roulette_p.size(); L++)
            {
                if (random >= roulette_p[L - 1] / SumP && random <= roulette_p[L] / SumP)
                {
                    nextCity = L - 1;
                    break;
                }
            }

            //cout << "nextcity index = " << nextCity << endl;
            //cout << "to_pos : " << list[i][nextCity] << endl;

            ant_route[i].push_back(list[i][nextCity]);
            stand = list[i][nextCity];
            list[i].erase(list[i].begin() + nextCity);
            //cout << "list i size = " << list[i].size() << endl;

        } //end 50 times position choose

        /*//check ant_route for sure
        for (int n = 0; n < ant_route[i].size(); n++)
        {
            cout << ant_route[i][n] << " ";
        }
        cout << endl;
        cout << "Finish route " << i << endl;
        */
    } //end 51 routes
} //end moving function

vector<double> Best_length(vector<vector<int>> &ant_route, vector<vector<double>> &dis_table, int ant, double &bestValue)
{
    vector<double> r;
    for (int i = 0; i < ant; i++)
    {
        double Value = 0;
        for (int j = 1; j < ant; j++) // sum 51 distances
        {
            //dis = i => j
            //cout << ant_route[i][j - 1] << " / " << ant_route[i][j] << endl;
            Value += dis_table[ant_route[i][j]][ant_route[i][j - 1]];
            //cout << Value << endl;
        }
        Value += dis_table[ant_route[i][50]][ant_route[i][0]]; // add the last-position to the first-positioin
        //cout << Value << endl;
        r.push_back(Value);
        if (Value < bestValue)
            bestValue = Value;
    }
    return r;
} //end Best_length function

void create_delta_tao(vector<vector<double>> &delta_Tao, int ant)
{
    vector<double> r;
    for (int i = 0; i <= ant; i++)
    {
        for (int j = 0; j <= ant; j++)
        {
            r.push_back(0);
        }
        delta_Tao.push_back(r);
    }
} //end create_delta_tao function

void update(vector<vector<int>> &ant_route, vector<double> &sum_route, vector<vector<double>> &Tao, vector<vector<double>> &delta_Tao, int ant)
{
    //cout << "sum_route size : " << sum_route.size() << endl;
    double delta_value = 0;
    for (int i = 0; i < ant; i++)
    {
        delta_value = Q / sum_route[i];
        //cout << "delta_value = " << delta_value << endl;
        for (int j = 1; j < ant; j++)
        {
            //cout << ant_route[i][j] << " ";
            //cout << j << " / from " << ant_route[i][j - 1] << " to " << ant_route[i][j] << endl;
            delta_Tao[ant_route[i][j]][ant_route[i][j - 1]] += delta_value;
        }
        //cout << "51 / from " << ant_route[i][50] << " to " << ant_route[i][0] << endl;
        delta_Tao[ant_route[i][50]][ant_route[i][0]] += delta_value;
        //cout << endl;
    }
} //end update funtion