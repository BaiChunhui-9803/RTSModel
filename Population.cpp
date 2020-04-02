#include <iostream>
#include "GameMap.h" 
#include "Population.h"
#include "GameRule.h" 

vector<Unit_Arm_Inf> Arm1 = { {100,12,5,150} };//����1�����Ͷ�100/������12/��������5/�������150
vector<Unit_Arm_Inf> Arm2 = { {120,15,2,120} };//����2�����Ͷ�120/������15/��������2/�������120
vector<Unit_Arm_Inf> Arm3 = { {150,10,2,100} };//����3�����Ͷ�150/������10/��������2/�������100

//�Զ����Unit�����еı�����Ϣ
void Unit::Auto_Add_UnitInf(const int arm_gudge) {
    switch (arm_gudge) {
    case 1:case 4:case 7:
        this->m_Endurance = Arm1.at(0).m_Arm_Endurance;
        this->m_Attack_Damage = Arm1.at(0).m_Arm_Attack_Damage;
        this->m_Attack_Distance = Arm1.at(0).m_Arm_Attack_Distance;
        this->m_Interval = Arm1.at(0).m_Arm_Interval;
        break;
    case 2:case 5:case 8:
        this->m_Endurance = Arm2.at(0).m_Arm_Endurance;
        this->m_Attack_Damage = Arm2.at(0).m_Arm_Attack_Damage;
        this->m_Attack_Distance = Arm2.at(0).m_Arm_Attack_Distance;
        this->m_Interval = Arm2.at(0).m_Arm_Interval;
        break;
    case 0:case 3:case 6:case 9:
        this->m_Endurance = Arm3.at(0).m_Arm_Endurance;
        this->m_Attack_Damage = Arm3.at(0).m_Arm_Attack_Damage;
        this->m_Attack_Distance = Arm3.at(0).m_Arm_Attack_Distance;
        this->m_Interval = Arm3.at(0).m_Arm_Interval;
        break;
    }
}


vector<vector<Unit>> unit1_2dmap;//��λ��ά����
vector<Unit> unit1;//�ҷ���λ����
vector<Unit> unit2;//�з���λ����


//Unit���캯��
Unit::Unit(int xpos, int ypos, int state, int arm) {
    this->m_Xpos = xpos;
    this->m_Ypos = ypos;
    this->m_State = state;
    this->m_Arm = arm;

    if (Correct_Unit(this)) {
        Auto_Add_UnitInf(Gudge_ArmType(arm));
    }
    else {
        std::cerr << "�Ա���ȡֵ������Ҫ��" << endl;
        exit(1);//ֹͣ�����һ�����������ķ�ʽ�����Ա�����ֵ(����ֵ)������˵������ֵ���ڹ涨��Χ��
    }
}

//�������Unit��Ԫ����ʱ����unit1
void Auto_Rand_Unit() {
    do {
        int x_rand = rand() % (X_len + 1);
        int y_rand = rand() % (Y_len + 1);
        int state = 1;
        int arm_rand = rand() % 4;
        if (CanAddUnit(x_rand, y_rand)) {
            AddUnit(x_rand, y_rand, 1);
            Unit U1_rand(x_rand, y_rand, state, arm_rand);
            unit1.push_back(U1_rand);
            break;
        }
    } while (1);
}

//�������Unit��Ԫ������unit2
void Auto_Rand_Unit_2() {
    do {
        int x_rand = rand() % (X_len + 1);
        int y_rand = rand() % (Y_len + 1);
        int state = 2;
        int arm_rand = rand() % 4;
        if (CanAddUnit(x_rand, y_rand)) {
            AddUnit(x_rand, y_rand, 2);
            Unit U2_rand(x_rand, y_rand, state, arm_rand);
            unit2.push_back(U2_rand);
            break;
        }
    } while (1);
}

vector<Individual> nowpopulation;//P(t)��Ⱥ
vector<Individual> midpopulation;//�м���Ⱥ���������ѡ�����������
vector<Individual> nextpopulation;//P(t+1)��Ⱥ

//�Ŵ��㷨��׼������
void Initialize()//�����ʼ����Ⱥ���õ���һ����Ⱥ
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < Unit_Size; i++) {
        Auto_Rand_Unit_2();
    }
    std::cout << "Unit2 is generated." << endl;
    for (int j = 0; j < Unit_Size; j++)
    {
        std::cout << '\t' << "Unit2[" << j << "]:" << std::endl;
        std::cout << '\t' << unit2.at(j).m_Xpos;
        std::cout << '\t' << unit2.at(j).m_Ypos;
        std::cout << '\t' << unit2.at(j).m_Arm << std::endl;
    }
    //���ɵз�����

    for (int i = 0; i < Po_Size; i++) {
        for (int j = 0; j < Unit_Size; j++) {

            Auto_Rand_Unit();//�ڶ�ά�������������Po_Size*De_Variable����Ԫ
        }
        unit1_2dmap.push_back(unit1);
        std::cout << "Indivi[" << i << "] is generated." << endl;
        unit1.clear();
        Clear_Map_unit1();
    }
    std::cout << "All random units are generated." << endl;
    //ѭ������ʱ�����������Ԫ�ͱ�����unit1_2dmap��

    //���ɶ���Ⱦɫ�壩�����뵽��ʼ��Ⱥ��
    for (int i = 0; i < Po_Size; i++)
    {
        for (int j = 0; j < Unit_Size; j++)
        {
            unit1.push_back(unit1_2dmap.at(i).at(j));
        }
        Unit* p_unit = &(unit1.at(0));
        Individual Indivi(p_unit);//����һ������Ⱦɫ�壩
        nowpopulation.push_back(Indivi);//���뵽��Ⱥpopulation��
        std::cout << "Indivi[" << i << "] is pushed into nowpopulation." << endl;
    }
    std::cout << "The initial population is generated." << endl;
    //ѭ������ʱ����ʼ��Ⱥ������nowpopulation��

    for (int i = 0; i < Po_Size; i++)
    {
        std::cout << "Indivi[" << i << "]:" << endl;
        for (int j = 0; j < Unit_Size; j++)
        {
            std::cout << '\t' << "Indivi[" << i << "][" << j << "]:" << endl;
            std::cout << '\t' << nowpopulation.at(i).Chrom.at(j).m_Xpos;
            std::cout << '\t' << nowpopulation.at(i).Chrom.at(j).m_Ypos;
            std::cout << '\t' << nowpopulation.at(i).Chrom.at(j).m_Arm<<std::endl;
        }
    }
}

//Individual��ʵ��
Individual::Individual(Unit* p_unit)//���캯��
{
    for (int j = 0; j < Unit_Size; j++)//��forѭ���Ա��������ֵ
    {
        if (Correct_Unit(p_unit))//����Ҫ�����Ա���ȡֵ��Χ�ж� 
        {
            p_unit->Auto_Add_UnitInf(p_unit->m_Arm);
            Chrom.push_back(*p_unit++);
        }
        else//������Ҫ���򷢳������沢����
        {
            cerr << "�Ա���ȡֵ������Ҫ��" << endl;
            exit(1);//ֹͣ�����һ�����������ķ�ʽ�����Ա�����ֵ(����ֵ)������˵������ֵ���ڹ涨��Χ��
        }
    }
    unit1.clear();
    //��ʼ��ʱĬ����Ӧֵ��ֵΪ0
    this->Fitness = 0;
    this->ReFitness = 0;
    this->SumFitness = 0;
}



double Individual::GetFitness()const//��ȡ��Ӧֵ
{
    return Fitness;
}
double Individual::GetReFitness()const //��ȡ��Ӧֵ����
{
    return ReFitness;
}
double Individual::GetSumFitness()const//��ȡ�ۼӸ���
{
    return SumFitness;
}
void Individual::ChaFitness(const double m_fitness)//�޸���Ӧֵ
{
    this->Fitness = m_fitness;
}
void Individual::ChaReFitness(const double m_ReFitness)//�޸���Ӧֵ����
{
    this->ReFitness = m_ReFitness;
}
void Individual::ChaSumFitness(const double m_SumFitness)//�޸��ۼӸ���
{
    this->SumFitness = m_SumFitness;
}



Fitness_Map_Unit Cacula[Unit_Size][Unit_Size] = {};//�����ҷ������ڵ�Ԫ��Ϣ���Ա������Ӧֵ
int Can_ATK_Num[Unit_Size] = {};//�����ҷ�����ɹ����������Ա������Ӧֵ

void Clear_Fitness_Map_Unit() {
    for (int i = 0; i < Unit_Size; i++) {
        for (int j = 0; j < Unit_Size; j++) {
            Cacula[i][j].Attack_Proba = 0;
        }
    }
}

bool No_Unit_In_Distance() {
    int num = 0;
    for (int i = 0; i < Unit_Size; i++) {
        for (int j = 0; j < Unit_Size; j++) {
            if (Cacula[i][j].Attack_Proba == 0) {
                num++;
            }
        }
    }

    if (num == Unit_Size* Unit_Size) {
        cout << "No unit in distance." << endl;
        return 1;
    }
    else
        return 0;
}


//���㵥λ�����
void Cacula_Unit_Distance(const int indivi_pos) {
    for (int i = 0; i < Unit_Size; i++) {
        for (int j = 0; j < Unit_Size; j++) {
            double u1_xpos = nowpopulation.at(indivi_pos).Chrom.at(i).m_Xpos;
            double u1_ypos = nowpopulation.at(indivi_pos).Chrom.at(i).m_Ypos;
            double u2_xpos = unit2.at(j).m_Xpos;
            double u2_ypos = unit2.at(j).m_Ypos;
            Cacula[i][j].Unit_Distance = pow(abs(u1_xpos - u2_xpos), 2);
        }
    }
}

//���㵥λ�������ȼ�
void Cacula_Attack_Proba(const int indivi_pos) {
    
    for (int i = 0; i < Unit_Size; i++) {
        for (int j = 0; j < Unit_Size; j++) {
            if (nowpopulation.at(indivi_pos).Chrom.at(i).m_Attack_Distance >= Cacula[i][j].Unit_Distance) {
                Cacula[i][j].Attack_Proba++;
                Can_ATK_Num[j]++;
            }
        }
    }
}

//����unit1[i]���ȹ����ĸ���λ
int Pick_Which_To_ATK(const int unit_pos) {
    int Max_CanATKNum = 0;
    for (int i = 0; i < Unit_Size; i++) {
        if (Can_ATK_Num[i] > Max_CanATKNum)
            Max_CanATKNum = Can_ATK_Num[i];
    }
    
    for (int i = 0; i < Unit_Size;i++) {
        if (Cacula[unit_pos][i].Attack_Proba > 0 && Can_ATK_Num[i] == Max_CanATKNum)
            return i;
    }

    return -1;
}

//ģ���ҷ�һ����λ�Ĺ�������
void Do_ATK(const int atk_damage, const int unit2_pos) {
    unit2.at(unit2_pos).m_Endurance -= atk_damage;
    if (unit2.at(unit2_pos).m_Endurance <= 0) {
        Can_ATK_Num[unit2_pos] = 0;
        for (int i = 0; i < Unit_Size; i++) {
            Cacula[i][unit2_pos].Attack_Proba = 0;
        }
    }
}



void Unit_Move(){}


//ģ��һ���������Ϸ����
double Start_Game(const int indivi_pos) {
    int k = 0;
    int t1 = 0;
    int t2 = 0;
    int sum_damage_1 = 0;
    int sum_damage_2 = 0;
    double fitness = 0;
    vector<Unit>* p_u1 = &(nowpopulation.at(indivi_pos).Chrom);
    vector<Unit>* p_u2 = &unit2;
    Cacula_Unit_Distance(indivi_pos);
    Cacula_Attack_Proba(indivi_pos);
    while (1) {
        k += 10;
        if (No_Unit_In_Distance() || Unit1_Over(p_u1) || Unit2_Over(p_u2)) {
            cout << "Indivi[" << indivi_pos << "]Game Over" << endl;
            break;
        }

        for (int i = 0; i < Unit_Size; i++) {
            //�ֵ��ҷ���λi�Ĺ���ʱ��
            if (!(k % p_u1->at(i).m_Interval) && (p_u1->at(i).m_Endurance > 0)) {
                int atk_pos = Pick_Which_To_ATK(i);
                if (atk_pos >= 0) {
                    Do_ATK(p_u1->at(i).m_Attack_Damage, atk_pos);
                    sum_damage_1 += p_u1->at(i).m_Attack_Damage;
                    
                }
                else {
                    Unit_Move();
                    t1++;
                }
                    

            }
        }
        
        for (int j = 0; j < Unit_Size; j++) {
            //�ֵ��з���λi�Ĺ���ʱ��
            if (!(k % p_u2->at(j).m_Interval) && (p_u2->at(j).m_Endurance > 0)) {
                while (1) {
                    int atk_pos = rand() % Unit_Size;
                    if (p_u1->at(atk_pos).m_Endurance > 0 && p_u1->at(atk_pos).m_Attack_Distance >= Cacula[atk_pos][j].Unit_Distance) {
                        p_u1->at(atk_pos).m_Endurance -= p_u2->at(j).m_Attack_Damage;
                        sum_damage_2 += p_u2->at(j).m_Attack_Damage;
                        if (p_u1->at(atk_pos).m_Endurance <= 0) {
                            for (int n = 0; n < Unit_Size; n++) {
                                Cacula[atk_pos][n].Attack_Proba = 0;
                            }
                        }
                        break;
                    }

                    else {
                        t2++;
                    }
                    if (t2 > 10) {
                        break;
                    }
                }
            }
        }
    };

    fitness = double(sum_damage_1) - double(sum_damage_2);
    if (fitness > 0) {
        return fitness;
    }
    else
        return 0;
    
}


void Cacula_Fitness()//����������Ӧֵ
{
    double fitness = 0;//��ʱ��Ӧֵ
    for (int i = 0; i < Po_Size; i++) {
        fitness = Start_Game(i);
        nowpopulation.at(i).ChaFitness(fitness);
        Clear_Fitness_Map_Unit();
        for (int j = 0; j < Unit_Size; j++) {
            unit2.at(j).Auto_Add_UnitInf(Gudge_ArmType(unit2.at(j).m_Arm));
        }
    }
}




void CaculaReFitness()//������Ӧֵ����
{
    double sum = 0;//��Ӧֵ�ۼ���
    double temp = 0;
    for (int i = 0; i < Po_Size; i++)//�������Ӧֵ֮��
    {
        sum += nowpopulation.at(i).GetFitness();
    }
    for (int j = 0; j < Po_Size; j++)
    {
        temp = nowpopulation.at(j).GetFitness() / sum;//�������
        nowpopulation.at(j).ChaReFitness(temp);//�޸ĸ������Ӧ�ȸ���
    }
}


void CalculaSumFitness()//�����ۼӸ������
{
    double summation = 0;//�ۼ���
    for (int k = 0; k < Po_Size; k++)
    {
        summation += nowpopulation.at(k).GetReFitness();
        nowpopulation.at(k).ChaSumFitness(summation);//��ǰ�ۼӽ����ֵ
    }
}

void Individual::printout(vector<Individual>::iterator itb, vector<Individual>::iterator ite) {
    int i = 0;
    for (auto it = itb; it != ite; it++, i++) {
        cout << "Indivi[" << i << "]:" << endl;
        cout << '\t' << "fitness=" << it->Fitness;
        cout << '\t' << "refitness=" << it->ReFitness;
        cout << '\t' << "sumfitness=" << it->SumFitness << endl;
    }
}



void seclect() //��Ⱥѡ��
{
    //���������0��1��С��
    double array[Po_Size];//������������
    default_random_engine e(time(0));//���棬�����������
    uniform_real_distribution<double> u(0.0, 1.0); //�ֲ�
    for (int i = 0; i < Po_Size; i++)
        array[i] = u(e);

    //���̽���ѡ��
    for (int j = 0; j < Po_Size; j++)
    {
        for (int i = 1; i < Po_Size; i++)
        {
            if (array[j] < nowpopulation.at(i - 1).GetSumFitness())
            {
                midpopulation.push_back(nowpopulation.at(i - 1));//���뵽�м���Ⱥ
            }
            if (array[j] >= nowpopulation.at(i - 1).GetSumFitness() && array[j] <= nowpopulation.at(i).GetSumFitness())
            {
                midpopulation.push_back(nowpopulation.at(i));//���뵽�м���Ⱥ
            }
        }
    }
    nowpopulation.clear();//���nowpopulation
    
    //for (int i = 0; i < Po_Size; i++)
    //{
    //    nowpopulation.push_back(midpopulation.at(i));
    //}

    //for (auto it = midpopulation.begin(); it != midpopulation.end(); it++) {
    //    nowpopulation.push_back(*it);
    //
    //}
}


double Scand() //�������0��1��С��
{
    int N = rand() % 999;
    return double(N) / 1000.0;;//�������0��1��С��
}





