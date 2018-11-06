#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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
    //input example => ./search 500 10 100
    int generation = atoi(argv[1]);
    int chromesome_number = atoi(argv[2]);
    int bits = atoi(argv[3]);

    if (chromesome_number % 2 != 0)
    { //確保染色體數目是偶數
        chromesome_number += 1;
    }

    srand(time(NULL));
    vector<vector<int>> vec2;
    vector<int> vec_fitness;
    vector<int> cal_roulette_p;
    int Roulette_sum = 0;
    int value = 0, bestValue = 0;

    cal_roulette_p.push_back(0);                //從0開始算，先丟到第一個
    for (int i = 0; i < chromesome_number; i++) //創造染色體數量
    {
        vector<int> vec1 = init(bits);
        vec2.push_back(vec1);                   //存到二維陣列
        value = fitness(vec1, bits);            //初始一維陣列評估值
        vec_fitness.push_back(value);           //存所有評估值
        Roulette_sum += value;                  // 計算輪盤分母值
        cal_roulette_p.push_back(Roulette_sum); //計算輪盤每個機率的分布
    }

    //show(vec2, chromesome_number);

    while (generation--)
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
    }
    cout << "bestValu : " << bestValue << endl;

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
    Roulette_sum = 0;

    for (int i = 0; i < chromesome_number; i++) //有多少染色體執行多少次射飛鏢
    {
        int tmp = chromesome_number + 1;
        float random = ((double)(rand() % 10)) / 10; //隨機產生0~1的值
        for (int j = 1; j < tmp; j++)                //檢查本次機率落在哪個範圍
        {
            if (random >= (double)cal_roulette_p[j - 1] / cal_roulette_p[tmp - 1] && random <= (double)cal_roulette_p[j] / cal_roulette_p[tmp - 1])
            {
                Roulette_sum += vec_fitness[j - 1];
                vec_fitness.push_back(vec_fitness[j - 1]);
                cal_roulette_p.push_back(Roulette_sum);
                child_vec.push_back(vec2[j - 1]);
                break;
            }
        }
    }
    vec_fitness.erase(vec_fitness.begin(), vec_fitness.begin() + chromesome_number);
    cal_roulette_p.erase(cal_roulette_p.begin() + 1, cal_roulette_p.begin() + chromesome_number + 1);

    return child_vec;
}

vector<vector<int>> crossover(vector<vector<int>> &vec2, int chromesome_number, int bits)
{
    vector<vector<int>> vec_cross;
    vector<int> fragment1, fragment2;

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
            vec2[i][random] = !vec2[i][random];
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
