#include<iostream>

#include "GameMap.h" 
#include "Population.h"
#include "GameRule.h" 

extern vector<Individual> nowpopulation;
extern vector<Individual> midpopulation;
//extern vector<vector<Unit>> unit1_2dmap;//��λ��ά����
//extern vector<Unit> unit1;//�ҷ���λ����
//extern vector<Unit> unit2;//�з���λ����

int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	Initialize();
	Cacula_Fitness();
	Cacula_FitnessProba();
	nowpopulation.at(0).printout(nowpopulation.begin(), nowpopulation.end());
	
	for (i = 0; i < 500; i++) {
		seclect();
		Cacula_Fitness();
		Cacula_FitnessProba();
		double best = GetBestFitness();
		double sum = GetSumFitness();
		cout << i << " sum:" << left << setw(5) <<sum << " best:" << left << setw(5) << best << endl;
	}
	pp();
	nowpopulation.at(0).printout(nowpopulation.begin(), nowpopulation.end());
}

