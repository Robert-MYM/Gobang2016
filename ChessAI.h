#ifndef FRACTIONAL_H_
#define FRACTIONAL_H_

#include<iostream>
#include<cstdlib>
#include <iomanip>
#include <ctime>  //ʱ������ �������������

using namespace std;
struct Point {
	Point *pre;  //��һ�����λ�ã����ڻ��� 
	int x;   //��
	int y;   //��
};

void CopyCB(int ChessB[15][15]);
//Point *ComputerAI(); //�ֵ���������
long double CaseRow(int R,bool who);

long double CaseCol(int C,bool who);
long double CaseLeftCross1(int R,bool who);
long double CaseLeftCross2(int C,bool who);
long double CaseRightCross1(int R,bool who);
long double CaseRightCross2(int C,bool who);
long double CBPoint();   //�����̽�������

Point *NormalAI(int ChessB[15][15]);

bool Check(int x, int y); //���x��y�����Ƿ�����

Point *HardAI(int ChessB[15][15]);

long double AlphaMin(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest);
long double BetaMax(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest);



#endif
