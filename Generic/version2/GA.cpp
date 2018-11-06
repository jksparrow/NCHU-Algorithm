#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "GA.h"

#define p_mutate 0.1

void GA::show(vector<vector<int>> &vec2, int chromesome_number)
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

vector<int> GA::init(int bits)
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

int GA::fitness(vector<int> &vec1, int bits)
{
    int value = 0;
    for (int i = 0; i < bits; i++)
    {
        if (vec1[i])
            value++;
    }

    return value;
}

vector<vector<int>> GA::select(vector<vector<int>> &vec2, vector<int> &vec_fitness, vector<int> &cal_roulette_p, int chromesome_number, int Roulette_sum)
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

vector<vector<int>> GA::crossover(vector<vector<int>> &vec2, int chromesome_number, int bits)
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

vector<vector<int>> GA::mutate(vector<vector<int>> &vec2, int chromesome_number, int bits)
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

int GA::fitness_2(vector<vector<int>> &vec2, int chromesome_number, int bits, int bestValue)
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