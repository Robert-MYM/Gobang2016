#ifndef FRACTIONAL_H_
#define FRACTIONAL_H_

#include<iostream>
#include<cstdlib>
#include <iomanip>
#include <ctime>  //时间做种 生成随机数函数

using namespace std;
struct Point {
	Point *pre;  //上一个点的位置，用于悔棋 
	int x;   //行
	int y;   //列
};

void CopyCB(int ChessB[15][15]);
//Point *ComputerAI(); //轮到电脑下子
long double CaseRow(int R,bool who);

long double CaseCol(int C,bool who);
long double CaseLeftCross1(int R,bool who);
long double CaseLeftCross2(int C,bool who);
long double CaseRightCross1(int R,bool who);
long double CaseRightCross2(int C,bool who);
long double CBPoint();   //对棋盘进行评分

Point *NormalAI(int ChessB[15][15]);

bool Check(int x, int y); //检查x，y四周是否落子

Point *HardAI(int ChessB[15][15]);

long double AlphaMin(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest);
long double BetaMax(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest);



#endif
