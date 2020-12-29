#pragma once
#include <omp.h> 
#include <vector>
#include <map>
#include <string>
#include <variant>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

typedef vector<variant<float, vector<float>>> mass;
typedef vector<variant<float, vector<int>>> spring;

class evolve
{
public:
	evolve(vector<int> kbc_seq_);
	~evolve();
	vector<mass> getMass() { return Mass; }
	vector<spring> getSpring() { return Spring;}
	vector<vector<int>> getMg() { return Mass_group; }
	double getDistance();
	void evolve_update();
	void add_(int pos_ind);
private:
	void initial(vector<vector<float>>, vector<int> mass_ind, vector<vector<int>> spring_ind);
	vector<vector<float>> force_cal();
	void update(vector<vector<float>> force_m_);
private:
	vector<vector<float>> kbc = { {1000,0,0},{20000,0,0},{5000,0.25,0},{5000,0.25,M_PI} };
	vector<int> kbc_seq;
	vector<mass> Mass;
	vector<spring> Spring;
	vector<vector<int>> Mass_group;
	double position_x;
	float k_spring = 10000;
	float k_c = 100000;
	vector<float> g = { 0,0,-9.81 };
	vector<float> L0;
	float miu_k = 1.0;
	float dt = 0.0001;
	float T = 0;
};