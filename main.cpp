#include<iostream>

#include "GameMap.h" 
#include "Population.h"
#include "GameRule.h" 

extern vector<Individual> nowpopulation;
extern vector<Individual> midpopulation;
//extern vector<vector<Unit>> unit1_2dmap;//单位二维容器
//extern vector<Unit> unit1;//我方单位容器
//extern vector<Unit> unit2;//敌方单位容器

int main()
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	Initialize();
	Cacula_Fitness();
	CaculaReFitness();
	CalculaSumFitness();
	nowpopulation.at(0).printout(nowpopulation.begin(), nowpopulation.end());
	
	/*for (i = 0; i < 100; i++) {
		seclect();
		CaculaReFitness();
		CalculaSumFitness();
		cout << i << endl;
	}
	
	nowpopulation.at(0).printout(nowpopulation.begin(), nowpopulation.end());*/

}

