#ifndef POPULATION_H_
#define POPULATION_H_

using namespace std;
extern int map[X_len][Y_len];

#include<random>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<bitset>
#include<iomanip>

const int Po_Size = 50;//种群规模
const int Ev_Algebra = 500;//进化代数
const double Ov_Probability = 0.850; //交叉概率,交叉概率用于判断两两个体是否需要交叉
const double Va_Probability = 0.050;//变异概率,变异概率用于判断任一个体是否需要变异
const int Unit_Size = 3;//智能体的个数
const int length_4 = 4;//用4位二进制编码
const int length_2 = 2;//用2位二进制编码


struct Unit_Arm_Inf //定义兵种信息
{
    int m_Arm_Endurance;//存放兵种忍耐度
    int m_Arm_Attack_Damage;//存放兵种攻击力
    int m_Arm_Attack_Distance;//存放兵种攻击距离
    int m_Arm_Interval;//存放兵种攻击间隔
};


struct Unit //定义单元类
{
    int m_Xpos;//存放单元x坐标
    int m_Ypos;//存放单元y坐标
    int m_State;//存放单元阵营
    int m_Arm;//存放单元兵种
    int m_Endurance;//存放单位忍耐度
    int m_Attack_Damage;//存放单位攻击力
    int m_Attack_Distance;//存放兵种攻击距离
    int m_Interval;//存放单位攻击间隔

    Unit(int xpos, int ypos, int state, int arm);    
    void Auto_Add_UnitInf(const int arm_gudge);
};

class Individual //定义个体类
{
private:
    double Fitness;//适应值
    double ReFitness;//适应值概率
    double SumFitness;//累加概率，为轮盘转做准备

public:
    vector<Unit> Chrom;//存放当前种群中各个个体，即染色体
    double Probability_Matrix[X_len][Y_len];//概率矩阵，反应单元的质量
    Individual(Unit* p_unit);//构造函数


    void ChaFitness(const double m_fitness);//修改适应值
    void ChaReFitness(const double m_ReFitness);//修改适应值概率
    void ChaSumFitness(const double m_SumFitness);//修改累加概率
    double GetFitness()const;//获取适应值
    double GetReFitness()const;//获取适应值概率
    double GetSumFitness()const;//获取累加概率
    void printout(vector<Individual>::iterator itb, vector<Individual>::iterator ite);
};

void Auto_Rand_Unit();//随机生成Unit单元到临时容器unit1
void Initialize();//随机初始化种群，得到第一代个体 
void Auto_Rand_Unit_2();//随机生成Unit单元到容器unit2


struct Fitness_Map_Unit {
    double Unit_Distance;
    int Attack_Proba;


};

bool No_Unit_In_Distance();
void Clear_Fitness_Map_Unit();
void Cacula_Unit_Distance(const int indivi_pos);//计算unit1[i]到unit2[j]的距离
void Cacula_Attack_Proba(const int indivi_pos);//计算unit1[i]到unit2[j]的攻击优先级
int Pick_Which_To_ATK(const int unit_pos);//计算unit1[i]优先攻击哪个单位
void Do_ATK(const int atk_damage, const int unit2_pos);//模拟一个我方单位的攻击过程
void Unit_Move();
double Start_Game(const int indivi_pos);//模拟游戏过程
void Cacula_Fitness();//计算个体的适应值


void CaculaReFitness();//计算个体的适应值概率
void CalculaSumFitness();//计算累加个体概率
void seclect();//种群选择
double Scand();//随机产生0到49的随机整数




//void crossing();//杂交
//void variating();//变异
//void genetic_algorithm();//遗传算法


#endif