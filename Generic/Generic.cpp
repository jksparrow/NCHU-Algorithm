#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

#define p_cross 0.8
#define p_mutate 0.1

using namespace std;

void show(vector<vector<int>> &vec2, int chromesome_number);
vector<int> init(int bits);
int fitness(vector<int> &vec1, int bits);
vector<vector<int>> select(vector<vector<int>> &vec2, vector<int> &vec_fitness, vector<int> &cal_roulette_p, int chromesome_number, int Roulette_sum);
vector<vector<int>> crossover(vector<vector<int>> &vec2, int chromesome_number, int bits);
vector<vector<int>> mutate(vector<vector<int>> &vec2, int chromesome_number, int bits);
int fitness_2(vector<vector<int>> &vec2, int chromesome_number, int bits, int bestValue);

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
                vector<int> vec1 = init(bits);
                vec2.push_back(vec1);                   //存到二維陣列
                value = fitness(vec1, bits);            //初始一維陣列評估值
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
                vec2 = select(vec2, vec_fitness, cal_roulette_p, chromesome_number, Roulette_sum); //選擇完留下新的子代
                //crossover
                float random = ((double)(rand() % 10)) / 10; //隨機產生0~1的值
                if (random < p_cross)                        //決定要不要交配
                {
                    vec2 = crossover(vec2, chromesome_number, bits);
                }
                //mutation
                vec2 = mutate(vec2, chromesome_number, bits);
                //fitness for 二維陣列
                bestValue = fitness_2(vec2, chromesome_number, bits, bestValue);

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

void show(vector<vector<int>> &vec2, int chromesome_number)
{
    for (int i = 0; i < chromesome_number; i++) // 檢查染色體亂數產生 & 每條的值
    {
        for (int j = 0; j < vec2[i].size(); j++)
        {
            cout << vec2[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

vector<int> init(int bits)
{
    vector<int> myNumber;
    myNumber.clear();

    for (int i = 0; i < bits; i++)
    {
        int num = rand() % 2;
        myNumber.push_back(num);
    }

    return myNumber;
}

int fitness(vector<int> &vec1, int bits)
{
    int value = 0;
    for (int i = 0; i < bits; i++)
    {
        if (vec1[i])
            value++;
    }

    return value;
}

vector<vector<int>> select(vector<vector<int>> &vec2, vector<int> &vec_fitness, vector<int> &cal_roulette_p, int chromesome_number, int Roulette_sum)
{
    vector<vector<int>> child_vec;
    child_vec.clear();
    Roulette_sum = 0;

    for (int i = 0; i < chromesome_number; i++) //有多少染色體執行多少次射飛鏢
    {
        int tmp = chromesome_number + 1;
        float random = ((double)(rand() % 10)) / 10; //隨機產生0~1的值
        //cout << "select random number : " << random << endl;
        for (int j = 1; j < tmp; j++) //檢查本次機率落在哪個範圍
        {
            //cout << "last p : " << cal_roulette_p[tmp - 1] << endl;
            if (random >= (double)cal_roulette_p[j - 1] / cal_roulette_p[tmp - 1] && random <= (double)cal_roulette_p[j] / cal_roulette_p[tmp - 1])
            {
                Roulette_sum += vec_fitness[j - 1];
                //cout << "Roulette P : " << vec_fitness[j - 1] << " sum : " << Roulette_sum << endl;
                vec_fitness.push_back(vec_fitness[j - 1]); //將射中的機率值保存
                cal_roulette_p.push_back(Roulette_sum);    //新的輪盤每個機率的分布
                child_vec.push_back(vec2[j - 1]);
                break;
            }
        }
    }
    //刪除原本多出來的機率值跟機率分布
    vec_fitness.erase(vec_fitness.begin(), vec_fitness.begin() + chromesome_number);                  //刪掉原本染色體數量的值
    cal_roulette_p.erase(cal_roulette_p.begin() + 1, cal_roulette_p.begin() + chromesome_number + 1); //刪掉原本輪盤的機率分布，但第一個依舊是零
    //cout << "size of vec_fitness : " << vec_fitness.size() << endl;
    //cout << "size of cal_roulette_p : " << cal_roulette_p.size() << endl;
    //cout << "-------------\n";

    return child_vec;
}

vector<vector<int>> crossover(vector<vector<int>> &vec2, int chromesome_number, int bits)
{
    vector<vector<int>> vec_cross;
    vector<int> fragment1, fragment2;
    vec_cross.clear();

    for (int i = 1; i < chromesome_number; i += 2)
    {
        fragment1.clear();
        fragment2.clear();
        int random = rand() % bits;
        //cout << "cross number : " << random << endl;
        for (int j = 0; j < random; j++)
        {
            fragment1.push_back(vec2[i - 1][j]);
            fragment2.push_back(vec2[i][j]);
        }
        for (int j = random; j < bits; j++)
        {
            fragment1.push_back(vec2[i][j]);
            fragment2.push_back(vec2[i - 1][j]);
        }
        vec_cross.push_back(fragment1);
        vec_cross.push_back(fragment2);
    }

    return vec_cross;
}

vector<vector<int>> mutate(vector<vector<int>> &vec2, int chromesome_number, int bits)
{
    vector<vector<int>> vec_mutate;
    vec_mutate.clear();

    for (int i = 0; i < chromesome_number; i++)
    {
        float random = ((double)(rand() % 10)) / 10; //隨機產生0~1的值
        //cout << "mutate probability : " << random << endl;
        if (random > p_mutate)
        {
            //cout << "no mutate" << endl;
            vec_mutate.push_back(vec2[i]);
        }
        else
        {
            int trans_pos = rand() % bits;
            //cout << "mutate position : " << trans_pos << endl;
            vec2[i][trans_pos] = !vec2[i][trans_pos];
            vec_mutate.push_back(vec2[i]);
        }
    }

    return vec_mutate;
}

int fitness_2(vector<vector<int>> &vec2, int chromesome_number, int bits, int bestValue)
{
    for (int i = 0; i < chromesome_number; i++)
    {
        int value = 0;
        for (int j = 0; j < bits; j++)
        {
            if (vec2[i][j])
                value++;
        }
        if (value > bestValue)
            bestValue = value;
    }

    return bestValue;
}
