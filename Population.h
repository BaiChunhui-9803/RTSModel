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

const int Po_Size = 50;//��Ⱥ��ģ
const int Ev_Algebra = 500;//��������
const double Ov_Probability = 0.850; //�������,������������ж����������Ƿ���Ҫ����
const double Va_Probability = 0.050;//�������,������������ж���һ�����Ƿ���Ҫ����
const int Unit_Size = 3;//������ĸ���
const int length_4 = 4;//��4λ�����Ʊ���
const int length_2 = 2;//��2λ�����Ʊ���


struct Unit_Arm_Inf //���������Ϣ
{
    int m_Arm_Endurance;//��ű������Ͷ�
    int m_Arm_Attack_Damage;//��ű��ֹ�����
    int m_Arm_Attack_Distance;//��ű��ֹ�������
    int m_Arm_Interval;//��ű��ֹ������
};


struct Unit //���嵥Ԫ��
{
    int m_Xpos;//��ŵ�Ԫx����
    int m_Ypos;//��ŵ�Ԫy����
    int m_State;//��ŵ�Ԫ��Ӫ
    int m_Arm;//��ŵ�Ԫ����
    int m_Endurance;//��ŵ�λ���Ͷ�
    int m_Attack_Damage;//��ŵ�λ������
    int m_Attack_Distance;//��ű��ֹ�������
    int m_Interval;//��ŵ�λ�������

    Unit(int xpos, int ypos, int state, int arm);    
    void Auto_Add_UnitInf(const int arm_gudge);
};

class Individual //���������
{
private:
    double Fitness;//��Ӧֵ
    double ReFitness;//��Ӧֵ����
    double SumFitness;//�ۼӸ��ʣ�Ϊ����ת��׼��

public:
    vector<Unit> Chrom;//��ŵ�ǰ��Ⱥ�и������壬��Ⱦɫ��
    double Probability_Matrix[X_len][Y_len];//���ʾ��󣬷�Ӧ��Ԫ������
    Individual(Unit* p_unit);//���캯��


    void ChaFitness(const double m_fitness);//�޸���Ӧֵ
    void ChaReFitness(const double m_ReFitness);//�޸���Ӧֵ����
    void ChaSumFitness(const double m_SumFitness);//�޸��ۼӸ���
    double GetFitness()const;//��ȡ��Ӧֵ
    double GetReFitness()const;//��ȡ��Ӧֵ����
    double GetSumFitness()const;//��ȡ�ۼӸ���
    void printout(vector<Individual>::iterator itb, vector<Individual>::iterator ite);
};

void Auto_Rand_Unit();//�������Unit��Ԫ����ʱ����unit1
void Initialize();//�����ʼ����Ⱥ���õ���һ������ 
void Auto_Rand_Unit_2();//�������Unit��Ԫ������unit2


struct Fitness_Map_Unit {
    double Unit_Distance;
    int Attack_Proba;


};

bool No_Unit_In_Distance();
void Clear_Fitness_Map_Unit();
void Cacula_Unit_Distance(const int indivi_pos);//����unit1[i]��unit2[j]�ľ���
void Cacula_Attack_Proba(const int indivi_pos);//����unit1[i]��unit2[j]�Ĺ������ȼ�
int Pick_Which_To_ATK(const int unit_pos);//����unit1[i]���ȹ����ĸ���λ
void Do_ATK(const int atk_damage, const int unit2_pos);//ģ��һ���ҷ���λ�Ĺ�������
void Unit_Move();
double Start_Game(const int indivi_pos);//ģ����Ϸ����
void Cacula_Fitness();//����������Ӧֵ


void CaculaReFitness();//����������Ӧֵ����
void CalculaSumFitness();//�����ۼӸ������
void seclect();//��Ⱥѡ��
double Scand();//�������0��49���������




//void crossing();//�ӽ�
//void variating();//����
//void genetic_algorithm();//�Ŵ��㷨


#endif