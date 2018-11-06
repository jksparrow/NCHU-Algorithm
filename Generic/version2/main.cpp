#include <iostream>
#include <fstream>
#include "GA.h"

#define p_cross 0.8

using namespace std;

int score = 0;

int main(int argc, char *argv[])
{
    //input example => ./search 300 10 100 30
    int generation = atoi(argv[1]);
    int chromesome_number = atoi(argv[2]);
    int bits = atoi(argv[3]);
    int runs = atoi(argv[4]);

    if (chromesome_number % 2 != 0)
    { //確保染色體數目是偶數
        chromesome_number += 1;
    }

	GA ga;

    fstream fp;
    fp.open("Output.csv", ios::out);
    fp << "Iteration"
       << ","
       << "Value" << endl;
    fp.close();

    srand(time(NULL));

    for (int i = 0; i <= generation; i += 10)
    {
        vector<int> average;
        for (int j = 0; j < runs; j++)
        {
            int Roulette_sum = 0, value = 0, bestValue = 0, cost = 0;
            vector<vector<int>> vec2;
            vector<int> vec_fitness;
            vector<int> cal_roulette_p;

            cal_roulette_p.push_back(0);                //從0開始算，先丟到第一個
            for (int i = 0; i < chromesome_number; i++) //創造染色體數量
            {
                vector<int> vec1 = ga.init(bits);
                vec2.push_back(vec1);                   //存到二維陣列
                value = ga.fitness(vec1, bits);            //初始一維陣列評估值
                vec_fitness.push_back(value);           //存所有評估值
                Roulette_sum += value;                  //計算輪盤分母值
                cal_roulette_p.push_back(Roulette_sum); //計算輪盤每個機率的分布
            }
            /*
            cout << "size of vec_fitness : " << vec_fitness.size() << endl;
            for (int i = 0; i < vec_fitness.size(); i++)
            {
                cout << vec_fitness[i] << endl;
            }
            cout << "size of cal_roulette_p : " << cal_roulette_p.size() << endl;
            for (int i = 0; i < cal_roulette_p.size(); i++)
            {
                cout << cal_roulette_p[i] << endl;
            }
            cout << "-------------\n";
            */

            while (cost < i)
            {
                //select
                vec2 = ga.select(vec2, vec_fitness, cal_roulette_p, chromesome_number, Roulette_sum); //選擇完留下新的子代
                //crossover
                float random = ((double)(rand() % 10)) / 10; //隨機產生0~1的值
                if (random < p_cross)                        //決定要不要交配
                {
                    vec2 = ga.crossover(vec2, chromesome_number, bits);
                }
                //mutation
                vec2 = ga.mutate(vec2, chromesome_number, bits);
                //fitness for 二維陣列
                bestValue = ga.fitness_2(vec2, chromesome_number, bits, bestValue);

                cost++;
            }
            average.push_back(bestValue);
        }
        int sum = 0;
        for (auto it = average.begin(); it != average.end(); it++)
        {
            sum += *it;
        }
        fstream fp;
        fp.open("Output.csv", ios::out | ios::app);
        fp << i << "," << sum / runs << endl;
        fp.close();
        cout << "Iter: " << i << " AvgMax: " << sum / runs << endl;
    }

    //cout << "bestValue : " << bestValue << endl;

    return 0;
}