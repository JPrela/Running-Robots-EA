#include "evolve.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <time.h>
using namespace std;

evolve::~evolve() 
{

}

evolve::evolve(vector<int> kbc_seq_)
{
	Mass.clear();
	Spring.clear();
	Mass_group.clear();
	kbc_seq = kbc_seq_;
	add_(1);
	add_(3);
	add_(7);
	add_(9);
	add_(11);
	add_(13);
	add_(17);
	add_(19);
	add_(14);
	add_(15);
	add_(16);
}

void evolve::evolve_update() 
{
	for (int i = 0; i <10; ++i) {
		vector<vector<float>> force_m;
		force_m = force_cal();
		update(force_m);
		T += dt;
	}
}

void evolve::add_(int pos_ind, float y)
{
	vector<vector<float>> pos;
	vector<int> rep_mass;
	vector<int> mass_ind;
	vector<vector<int>> rep_spr;
	vector<vector<int>> spr_ind;
	vector<int> temp;
	switch(pos_ind) {
	case 1: pos = { { 0,0,0 }, { 0.1,0,0 } ,{ 0,0.1,0 },{ 0,0,0.1 },{ 0.1,0.1,0 },{ 0.1,0,0.1 },{ 0,0.1,0.1 },{ 0.1,0.1,0.1 } }; break;
	case 2: pos = { { 0.1,0,0 }, { 0.2,0,0 } ,{ 0.1,0.1,0 },{ 0.1,0,0.1 },{ 0.2,0.1,0 },{ 0.2,0,0.1 },{ 0.1,0.1,0.1 },{ 0.2,0.1,0.1 } }; break;
	case 3: pos = { { 0.2,0,0 }, { 0.3,0,0 } ,{ 0.2,0.1,0 },{ 0.2,0,0.1 },{ 0.3,0.1,0 },{ 0.3,0,0.1 },{ 0.2,0.1,0.1 },{ 0.3,0.1,0.1 } }; break;
	case 4: pos = { { 0,0.1,0 }, { 0.1,0.1,0 } ,{ 0,0.2,0 },{ 0,0.1,0.1 },{ 0.1,0.2,0 },{ 0.1,0.1,0.1 },{ 0,0.2,0.1 },{ 0.1,0.2,0.1 } }; break;
	case 5: pos = { { 0.1,0.1,0 }, { 0.2,0.1,0 } ,{ 0.1,0.2,0 },{ 0.1,0.1,0.1 },{ 0.2,0.2,0 },{ 0.2,0.1,0.1 },{ 0.1,0.2,0.1 },{ 0.2,0.2,0.1 } }; break;
	case 6: pos = { { 0.2,0.1,0 }, { 0.3,0.1,0 } ,{ 0.2,0.2,0 },{ 0.2,0.1,0.1 },{ 0.3,0.2,0 },{ 0.3,0.1,0.1 },{ 0.2,0.2,0.1 },{ 0.3,0.2,0.1 } }; break;
	case 7:pos = { { 0,0.2,0 }, { 0.1,0.2,0 } ,{ 0,0.3,0 },{ 0,0.2,0.1 },{ 0.1,0.3,0 },{ 0.1,0.2,0.1 },{ 0,0.3,0.1 },{ 0.1,0.3,0.1 } }; break;
	case 8:pos = { { 0.1,0.2,0 }, { 0.2,0.2,0 } ,{ 0.1,0.3,0 },{ 0.1,0.2,0.1 },{ 0.2,0.3,0 },{ 0.2,0.2,0.1 },{ 0.1,0.3,0.1 },{ 0.2,0.3,0.1 } }; break;
	case 9:pos = { { 0.2,0.2,0 }, { 0.3,0.2,0 } ,{ 0.2,0.3,0 },{ 0.2,0.2,0.1 },{ 0.3,0.3,0 },{ 0.3,0.2,0.1 },{ 0.2,0.3,0.1 },{ 0.3,0.3,0.1 } }; break;
	case 11: pos = { { 0,0,0.1 }, { 0.1,0,0.1 } ,{ 0,0.1,0.1 },{ 0,0,0.2 },{ 0.1,0.1,0.1 },{ 0.1,0,0.2 },{ 0,0.1,0.2 },{ 0.1,0.1,0.2 } }; break;
	case 12: pos = { { 0.1,0,0.1 }, { 0.2,0,0.1 } ,{ 0.1,0.1,0.1 },{ 0.1,0,0.2 },{ 0.2,0.1,0.1 },{ 0.2,0,0.2 },{ 0.1,0.1,0.2 },{ 0.2,0.1,0.2 } }; break;
	case 13: pos = { { 0.2,0,0.1 }, { 0.3,0,0.1 } ,{ 0.2,0.1,0.1 },{ 0.2,0,0.2 },{ 0.3,0.1,0.1 },{ 0.3,0,0.2 },{ 0.2,0.1,0.2 },{ 0.3,0.1,0.2 } }; break;
	case 17:pos = { { 0,0.2,0.1 }, { 0.1,0.2,0.1 } ,{ 0,0.3,0.1 },{ 0,0.2,0.2 },{ 0.1,0.3,0.1 },{ 0.1,0.2,0.2 },{ 0,0.3,0.2 },{ 0.1,0.3,0.2 } }; break;
	case 18:pos = { { 0.1,0.2,0.1 }, { 0.2,0.2,0.1 } ,{ 0.1,0.3,0.1 },{ 0.1,0.2,0.2 },{ 0.2,0.3,0.1 },{ 0.2,0.2,0.2 },{ 0.1,0.3,0.2 },{ 0.2,0.3,0.2 } }; break;
	case 19:pos = { { 0.2,0.2,0.1 }, { 0.3,0.2,0.1 } ,{ 0.2,0.3,0.1 },{ 0.2,0.2,0.2 },{ 0.3,0.3,0.1 },{ 0.3,0.2,0.2 },{ 0.2,0.3,0.2 },{ 0.3,0.3,0.2 } }; break;
	case 14: pos = { { 0,0.1,0.1 }, { 0.1,0.1,0.1 } ,{ 0,0.2,0.1 },{ 0,0.1,0.2 },{ 0.1,0.2,0.1 },{ 0.1,0.1,0.2 },{ 0,0.2,0.2 },{ 0.1,0.2,0.2 } }; break;
	case 15: pos = { { 0.1,0.1,0.1 }, { 0.2,0.1,0.1 } ,{ 0.1,0.2,0.1 },{ 0.1,0.1,0.2 },{ 0.2,0.2,0.1 },{ 0.2,0.1,0.2 },{ 0.1,0.2,0.2 },{ 0.2,0.2,0.2 } }; break;
	case 16: pos = { { 0.2,0.1,0.1 }, { 0.3,0.1,0.1 } ,{ 0.2,0.2,0.1 },{ 0.2,0.1,0.2 },{ 0.3,0.2,0.1 },{ 0.3,0.1,0.2 },{ 0.2,0.2,0.2 },{ 0.3,0.2,0.2 } }; break;
	case 25: pos = { { 0.1,0.1,0.2 }, { 0.2,0.1,0.2 } ,{ 0.1,0.2,0.2 },{ 0.1,0.1,0.3 },{ 0.2,0.2,0.2 },{ 0.2,0.1,0.3 },{ 0.1,0.2,0.3 },{ 0.2,0.2,0.3 } }; break;

	}
	for (int i = 0; i < pos.size(); ++i) pos[i][2] += 0;
	for (int i = 0; i < pos.size(); ++i) pos[i][1] += y;
 	for (int i = 0; i < pos.size(); ++i) {
		int indicate = 0;
		for (int j = 0; j < Mass.size(); ++j) {
			if (pos[i] == get<1>(Mass[j][1])) {
				rep_mass.push_back(i);
				mass_ind.push_back(j);
				indicate = 1;
				break;
			}
		}
		if (indicate == 0) mass_ind.push_back(i + Mass.size() - rep_mass.size());
	}
	for (int i = 0; i < pos.size(); ++i)
		for (int j = i+1; j < pos.size(); ++j) {
			int indicate = 0;
			if (mass_ind[i] < Mass.size() && mass_ind[j] < Mass.size())
				if (mass_ind[i] < mass_ind[j]) {
					temp = { mass_ind[i] ,mass_ind[j] };
					for (int k = 0; k < Spring.size(); ++k)
						if (temp == get<1>(Spring[k][2])) {
							rep_spr.push_back(temp);
							indicate = 1;
							break;
						}
				}
				else {
					temp = { mass_ind[j] ,mass_ind[i] };
					for (int k = 0; k < Spring.size(); ++k)
						if (temp == get<1>(Spring[k][2])) {
							rep_spr.push_back(temp);
							indicate = 1;
							break;
						}
				}
			if (indicate == 0) {
				if (mass_ind[i] < mass_ind[j]) spr_ind.push_back({ mass_ind[i] ,mass_ind[j] });
				else spr_ind.push_back({ mass_ind[j] ,mass_ind[i] });
			}
		}
	Mass_group.push_back(mass_ind);
	initial(pos, mass_ind, spr_ind);
}

void evolve::initial(vector<vector<float>> pos, vector<int> mass_ind, vector<vector<int>> spring_ind) {
	mass node;
	spring edge;
	vector<vector<float>> initial_pos;
	vector<float> v = { 0,0,0 };
	vector<float> a = { 0,0,0 };
	initial_pos = pos;
	int l_pos=initial_pos.size();
	int l_m = Mass.size();
	for (int i = 0; i < mass_ind.size(); i++)
	{
		if (mass_ind[i] >= l_m) {
			node.push_back(0.1);
			node.push_back(initial_pos[i]);
			node.push_back(a);
			node.push_back(v);
			Mass.push_back(node);
			node.clear();
		}
	}
	vector<int> m_ind(2);
	for (int i = 0; i < spring_ind.size();++i) {
			edge.push_back(kbc[kbc_seq[i]][0]);
			float dist=0;
			int i_1 = spring_ind[i][0];
			int i_2 = spring_ind[i][1];
			for (int k = 0; k < 3; ++k) dist += pow(get<1>(Mass[i_1][1])[k] - get<1>(Mass[i_2][1])[k],2);
			edge.push_back(sqrt(dist));
			L0.push_back(sqrt(dist));
			m_ind[0] = i_1; m_ind[1] = i_2;
			edge.push_back(m_ind);
			Spring.push_back(edge);
			edge.clear();
		}
}

vector<vector<float>> evolve::force_cal()
{
	vector<vector<float>> force_m;
	vector<vector<float>> force_e;
	int len_m = Mass.size();
	int len_s = Spring.size();
	float breath_force;
	vector<vector<float>> mass_force(len_m);
	vector<int> ind_m(2);
	vector<float> pos1(3);
	vector<float> pos2(3);
	vector<float> force_vector_12(3);
	vector<float> force_vector_21(3);
	float spring_force;
	float m= 0.1;
	for (int i = 0; i < len_m; ++i) force_m.push_back({ 0,0,0 });
//#pragma omp parallel for
		for (int i = 0; i < len_s; ++i) {
			/*vector<int> ind_m(2);
			vector<float> pos1(3);
			vector<float> pos2(3);
			vector<float> force_vector_12(3);
			vector<float> force_vector_21(3);
			float spring_force;*/
			ind_m = get<1>(Spring[i][2]);
			pos1 = get<1>(Mass[ind_m[0]][1]);
			pos2 = get<1>(Mass[ind_m[1]][1]);
			float L = 0;
			for (int j = 0; j < 3; ++j) {
				force_vector_12[j] = pos2[j] - pos1[j];
				force_vector_21[j] = pos1[j] - pos2[j];
				L += pow(pos1[j] - pos2[j], 2);
			}
			L = sqrt(L);
			spring_force = get<0>(Spring[i][0]) * (L - get<0>(Spring[i][1]));
			for (int k = 0; k < 3; ++k) {
				force_vector_12[k] = force_vector_12[k] / float(L) * spring_force;
				force_vector_21[k] = force_vector_21[k] / float(L) * spring_force;
				force_m[ind_m[0]][k] += force_vector_12[k];
				force_m[ind_m[1]][k] += force_vector_21[k];
			}
		}

//#pragma omp parallel for
	for (int i = 0; i < len_m; ++i) {
		force_m[i][2] += g[2] * get<0>(Mass[i][0]);
		if (get<1>(Mass[i][1])[2] <= 0) {
			force_m[i][2] += -get<1>(Mass[i][1])[2] * k_c;
			float h_f = sqrt(pow(force_m[i][0], 2) + pow(force_m[i][1], 2));
			if (h_f <= abs(get<1>(Mass[i][1])[2] * k_c * miu_k)) {
				force_m[i][0] = 0;
				force_m[i][1] = 0;

			}
			else {
				force_m[i][0] = (float(force_m[i][0]) / h_f) * (h_f - abs(get<1>(Mass[i][1])[2] * k_c * miu_k));
				force_m[i][1] = (float(force_m[i][1]) / h_f) * (h_f - abs(get<1>(Mass[i][1])[2] * k_c * miu_k));
			}
		}

	}
	//if (T<0.1)
	//force_m[Mass.size() - 1][0] += -80;
	return force_m;
}

void evolve::update(vector<vector<float>> force_m_)
{
	int len_m = Mass.size();
	int len_s = Spring.size();
	float temp = 0.15;
	vector<float> a(3);
	vector<float> v(3);
	vector<float> p(3);
	float m;
//#pragma omp parallel for
	for (int i = 0; i < len_m; ++i) {
		//vector<float> a(3);
		//vector<float> v(3);
		//vector<float> p(3);
		//float m;
		v = get<1>(Mass[i][2]);
		p = get<1>(Mass[i][1]);
		m = get<0>(Mass[i][0]);
		for (int k = 0; k < 3; ++k) {
			a[k] = float(force_m_[i][k]) / m;
			v[k] = v[k] + a[k] * dt; 
			v[k] *= 0.9994;
			p[k] = p[k] + v[k] * dt;
		}
		Mass[i][1] = p;
		Mass[i][2] = v;
		Mass[i][3] = a;
	}
//#pragma omp parallel for
	for (int i = 0; i < len_s; ++i) {
		float l0 = L0[i];
		l0 *= kbc[kbc_seq[i]][1] * sin(20 * T + kbc[kbc_seq[i]][2]) + 1;
		Spring[i][1] = l0;
	}
	
}

