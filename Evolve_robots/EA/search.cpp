#include "search.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;




search::search()
{
	for (int i = 0; i < 1; ++i) {
		population.clear();
		fitness.clear();
		search_ea(100);        // evaluation times, at least 3
	}
}

search::~search()
{
}

void search::search_ea(int n)
{
	ofstream ofile;
	ofstream ofile1;
	ofstream ofile2;
	double valread = DBL_MIN;
	vector<PAIR> fit_val;
	vector<int> parents_index;
	double child_fit;
	vector<int> best_indi;
	initial_pop();
	float div;
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		PAIR temp(fitness[i], i);
		fit_val.push_back(temp);
	}
	ofile.open("D:\\data_a3\\PB\\fit.txt", ios::app);               // record fitness value
	//ofile2.open("D:\\data_a3\\PB\\div.txt", ios::app);             // record diversity of population
	for (int i = 0; i < n; ++i) {
		parents_index = select_parents(fit_val);
		cross_over(parents_index);
		if (i < 16000) mutate();
		else if (rand() % 10 == 0) mutate();
		//if (i % 10 == 0) {
		//	div=cal_div();
		//	ofile2 << div << endl;
		//}
		child_fit = fitness_cal(child);
		if (child_fit > fit_val[parents_index[0]].first) {
			population[parents_index[0]] = child;
			PAIR temp(child_fit, parents_index[0]);
			fit_val[parents_index[0]] = temp;
		}
		else if (child_fit > fit_val[parents_index[1]].first) {
			population[parents_index[1]] = child;
			PAIR temp(child_fit, parents_index[1]);
			fit_val[parents_index[1]] = temp;
		}
		valread = bestfitval(fit_val);
		ofile << valread << endl;
	}
	ofile.close();
	best_indi=population[bestfitval_ind(fit_val)];
	ofile1.open("D:\\data_a3\\PB\\best.txt", ios::app);
	for (int i = 0; i < best_indi.size(); ++i) ofile1 << best_indi[i] << endl;       // record the results
	ofile1.close();
	//ofile2.close();

}

void search::initial_pop()
{
	vector <int> temp(springs_number);
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		for (int i = 0; i < springs_number; i++) { temp[i] = rand() % 4; }
		population.push_back(temp);
		evolve e1(temp);
		for (int j = 0; j < 32000; ++j) e1.evolve_update();
		fitness.push_back(e1.getDistance());
		e1.~evolve();
	}
}

vector<int> search::select_parents(vector<PAIR> fit_val_)
{
	vector<int> parents_index(2);
	parents_index[0] = Tournament(fit_val_, 2);
	parents_index[1] = Tournament(fit_val_, 2);
	while (parents_index[1] == parents_index[0]) parents_index[1] = Tournament(fit_val_, 2);
	return parents_index;
}

int search::Tournament(vector<PAIR> fit_val_, int k)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(fit_val_.begin(), fit_val_.end(), std::default_random_engine(seed));
	vector<PAIR> temp_f;
	int parents_index;
	PAIR temp_ind;
	for (int i = 0; i < k; ++i) {
		temp_ind = fit_val_.back();
		temp_f.push_back(temp_ind);
		fit_val_.pop_back();
	}
	sort(temp_f.begin(), temp_f.end());
	parents_index = temp_f[0].second;
	return parents_index;
}

void search::cross_over(vector<int> parents_index)
{
	child=population[parents_index[0]];
	int ind_begin = rand() % (springs_number / 2);
	for (int i = ind_begin+1; i <= springs_number / 2+ind_begin; ++i) {
		child[i] = population[parents_index[1]][i];
	}
}

void search::mutate(int n)
{
	for (int i = 0; i < n; ++i) {
		int mutate_ind = rand() % springs_number;
		int new_ind = rand() % 4;
		while (new_ind==child[mutate_ind]) new_ind = rand() % 4;
		child[mutate_ind] = new_ind;
	}
}

double search::fitness_cal(vector<int> individual)
{
	double fitness_value;
	evolve e1(individual);
	for (int j = 0; j < 32000; ++j) e1.evolve_update();
	fitness_value=e1.getDistance();
	e1.~evolve();
	return fitness_value;
}

double search::bestfitval(vector<PAIR> fit_val_)
{
	sort(fit_val_.begin(), fit_val_.end()/*, cmp_by_value*/);
	double bestfitval = fit_val_.back().first;
	return bestfitval;
}

int search::bestfitval_ind(vector<PAIR> fit_val_)
{
	sort(fit_val_.begin(), fit_val_.end()/*, cmp_by_value*/);
	int bestfitval_ind = fit_val_.back().second;
	return bestfitval_ind;
}

float search::cal_div()
{
	int count = 0;
	for (int i = 0; i < (POPULATION_SIZE / 2); ++i) {
		for (int j = 0; j < springs_number; ++j) {
			if (population[i][j] != population[POPULATION_SIZE - i - 1][j])
				count += 1;
		}
	}
	float div =  count / float(50);
	return div;
}



