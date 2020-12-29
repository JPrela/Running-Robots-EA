#pragma once
#include "evolve.h"
#include <vector>
#include <time.h>
using namespace std;


typedef pair<double, int> PAIR;
const int POPULATION_SIZE = 10;
const int springs_number = 248;

class search
{
public:
    search();
    ~search();

private:
    void search_ea(int n);
    void initial_pop();
    vector<int> select_parents(vector<PAIR> fit_val_);
    int Tournament(vector<PAIR> fit_val_, int k);
    void cross_over(vector<int> parents_index);
    void mutate(int n=1);
    double fitness_cal(vector<int> individual);
    double bestfitval(vector<PAIR> fit_val_);
    int bestfitval_ind(vector<PAIR> fit_val_);
    float cal_div();
private:
    vector<vector<int>> population;
    vector<double> fitness;
    vector<int> child;
};
