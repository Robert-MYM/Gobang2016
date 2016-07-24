#include"ChessAI.h"
using namespace std;

const int OriginCB[15][15] = {
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,
	6,7,7,7,7,7,7,7,7,7,7,7,7,7,8 }; //���̳�ʼ��

int CB[15][15];



// SCORE_BLACK[i][j] 
// ��ʾ����j+1������(�����߹�i����λ)������
// i = 0��ʾ���߶�����ס    i = 1��ʾ��һ��û����ס  i = 2 ��ʾ���߶��п�λ
//const   double SCORE_WHITE[][5]   =   {   {0,  0, 0,	0,	1e10}  ,      {1e0,     1e2,	 1e4,	    1e6,   1e10},            {1e1,    1e3,	    1e5	,   1e7,   	1e10}       };
//const   double SCORE_BLACK[][5]   =   {   {0,  0, 0,	0,	-1e9}  ,       {-1e1,   -1e3,	-1e5,   -1e7,	-1e9 },             {-1e2,    -1e4,	-1e6	,	-1e8,	-1e9}       };
const   double SCORE_WHITE[][5] = { { 0,  0, 0,	0,	10000000 },{ 1,     25,	 500,	 2500,   10000000 },{ 5,    100,	 2500,   50000,   	10000000 } };
const   double SCORE_BLACK[][5] = { { 0,  0, 0,	0,	-1000000 },{ -5,   -100,	-1000,   -10000,	-1000000 },{ -25,  -500,	-10000,	-250000,	-1000000 } };

// �������i=0�ķ�����ͣ�i>0ʱ����Խ��Խ�ã�
// �磺[1][3]>[2][2]  ������>����  ����Ϊ����һ�壬���ļ�������  
// ����>���  ����Ϊ��������һ�壬����ʹ����������,���߻���ɻ������ͱ��������>���� ���з�����һ�壬����ʹ���ı������(���߶�����)�����߻����������
// Ϊ�˲�ʹ�����ص���[i+1][j]    >= 4*[i][j] +1  ��[i][j+1]    >= 4*[i+1][j] +1   �����ȡ�����λȡ������9ȡ��Ϊ10,     81ȡ��Ϊ100
// �ڷ��ĸ���Ҫ����������һ���ڷ����������ܷ֣���ʹ����ȥ�º���     �������ĸ���Ϊ�����10��,    ��Ȼ����������ʱ�׷�����Ҫ�󣬲�Ȼ����ȥ�ºڷ����Լ���Ӯ

/*
�׷�����>�ڷ�����
���Ե��׷��л�����ڷ�������ʱ��Ӧ�������λ�ã�
������ʹ�ڷ���������ģ���ôҲֻ��Ҫһ��������ס
*/

void CopyCB(int ChessB[15][15]) {
	int i, j;
	for (i = 0;i <= 14;i++) {
		for (j = 0;j <= 14;j++) {
			CB[i][j] = ChessB[i][j];
		}
	}
}


long double CBPoint(){                 //�������� ����������
	int i, j;
	long double Score;
	Score = 0;
	for (i = 0;i <= 14;i++) {
		Score += CaseRow(i,true);
		Score += CaseRow(i, false);
	}
	for (j = 0;j <= 14;j++) {
		Score += CaseCol(j,true);
		Score += CaseCol(j, false);
	}
	for (i = 0;i <= 14;i++) {
		Score += CaseLeftCross1(i,true);
		Score += CaseLeftCross1(i, false);
	}
	for (j = 1;j <= 14;j++) {
		Score += CaseLeftCross2(j,true);
		Score += CaseLeftCross2(j, false);
	}
	for (i = 0;i <= 14;i++) {
		Score += CaseRightCross1(i, true);
		Score += CaseRightCross1(i, false);
	}
	for (j = 1;j <= 14;j++) {
		Score += CaseRightCross2(j, true);
		Score += CaseRightCross2(j, false);
	}
	return Score;
}

long double CaseRow(int R,bool who) {
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}

	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 1;i <= 14;i++) {
		if (CB[R][i] == me) {
			if (CB[R][i - 1] == me) lianzi++;
			else if (CB[R][i - 1] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[R][i] == you) {
			if (CB[R][i - 1] == me) {
				qi--;
				if(who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
				
			}
		}
		else {
			if (CB[R][i - 1] == me) {
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[R][14] == me) {
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

long double CaseCol(int C,bool who) {
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}
	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 1;i <= 14;i++) {
		if (CB[i][C] == me) {
			if (CB[i-1][C] == me) lianzi++;
			else if (CB[i-1][C] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[i][C] == you) {
			if (CB[i-1][C] == me) {
				qi--;
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];

			}
		}
		else {
			if (CB[i-1][C] == me) {
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[14][C] == me) {
		qi--;
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

long double CaseLeftCross1(int R,bool who)
{
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}
	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 1;i <= (14-R);i++) {
		if (CB[R+i][i] == me) {
			if (CB[R+i-1][i - 1] == me) lianzi++;
			else if (CB[R+i-1][i - 1] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[R+i][i] == you) {
			if (CB[R+i-1][i - 1] == me) {
				qi--;
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];

			}
		}
		else {
			if (CB[R+i-1][i - 1] == me) {
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[14][14-R] == me) {
		qi--;
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

long double CaseLeftCross2(int C,bool who)
{
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}
	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 1;i <= (14 - C);i++) {
		if (CB[i][C+i] == me) {
			if (CB[i - 1][C+i - 1] == me) lianzi++;
			else if (CB[i - 1][C+i - 1] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[i][C+i] == you) {
			if (CB[i - 1][C+i - 1] == me) {
				qi--;
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];

			}
		}
		else {
			if (CB[i - 1][C+i - 1] == me) {
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[14-C][14] == me) {
		qi--;
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

long double CaseRightCross1(int R, bool who)
{
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}
	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 14;i >= R;i--) {
		if (CB[R + 15- i][i] == me) {
			if (CB[R + 15 - i - 1][i + 1] == me) lianzi++;
			else if (CB[R + 15 - i - 1][i + 1] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[R + 15 - i][i] == you) {
			if (CB[R + 15 - i - 1][i + 1] == me) {
				qi--;
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];

			}
		}
		else {
			if (CB[R +15 - i - 1][i + 1] == me) {
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[14][R] == me) {
		qi--;
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

long double CaseRightCross2(int C, bool who)
{
	int me, you;
	if (who) {
		me = 9;
		you = 10;
	}
	else {
		me = 10;
		you = 9;
	}
	int i = 0;;
	int lianzi = 1;
	int qi = 1;
	long double Score;
	Score = 0;
	for (i = 0;i <= C;i++) {
		if (CB[i][C-i] == me) {
			if (CB[i - 1][C - i + 1] == me) lianzi++;
			else if (CB[ i- 1][C - i + 1] == you) {
				qi = 1;
				lianzi = 1;
			}
			else {
				qi = 2;
				lianzi = 1;
			}
		}
		else if (CB[i][C-i] == you) {
			if (CB[i - 1][C - i + 1] == me) {
				qi--;
			
				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];

			}
		}
		else {
			if (CB[i - 1][C - i + 1] == me) {

				if (who) Score += SCORE_WHITE[qi][lianzi - 1];
				else Score += SCORE_BLACK[qi][lianzi - 1];
			}
		}
	}
	if (CB[C][0] == me) {
		qi--;
		if (who) Score += SCORE_WHITE[qi][lianzi - 1];
		else Score += SCORE_BLACK[qi][lianzi - 1];
	}
	return Score;
}

Point *NormalAI(int ChessB[15][15])
{
	CopyCB(ChessB);
	int i, j, getpoint, temppoint;
	getpoint = CBPoint();
	Point temp;
	temp.x = -1;
	temp.y = -1;
	temp.pre = NULL;
	BetaMax(-10000000, 100000000, 2, temp);
	return &temp;
}

bool Check(int x, int y)    //�����Ƿ�Ϊ���ӵ�
{
	if (CB[x][y] != 9 && CB[x][y] != 10) {
		if (x != 0) {
			if (CB[x - 1][y] == 9 || CB[x - 1][y] == 10) return true;
		}
		if (y != 0) {
			if (CB[x][y - 1] == 9 || CB[x][y - 1] == 10) return true;
		}
		if (x != 14) {
			if (CB[x + 1][y] == 9 || CB[x + 1][y] == 10) return true;
		}
		if (y != 14) {
			if (CB[x][y + 1] == 9 || CB[x][y + 1] == 10) return true;
		}
		if (x != 0 && y != 0) {
			if (CB[x - 1][y - 1] == 9 || CB[x - 1][y - 1] == 10) return true;
		}
		if (x != 0 && y != 14) {
			if (CB[x - 1][y + 1] == 9 || CB[x - 1][y + 1] == 10) return true;
		}
		if (x != 14 && y != 0) {
			if (CB[x + 1][y - 1] == 9 || CB[x + 1][y - 1] == 10) return true;
		}
		if (x != 14 && y != 14) {
			if (CB[x + 1][y + 1] == 9 || CB[x + 1][y + 1] == 10) return true;
		}
	}
	return false;
}

Point *HardAI(int ChessB[15][15])
{
	const   double SCORE_WHITE[][5] = { { 0,  0, 0,	0,	100000 },{ 1,     25,	 500,	 2500,   100000 },{ 5,    100,	 2500,   50000,   	100000 } };
	const   double SCORE_BLACK[][5] = { { 0,  0, 0,	0,	-1000000 },{ -5,   -100,	-1000,   -10000,	-1000000 },{ -25,  -500,	-10000,	-250000,	-1000000 } };
    //�ڽ���4������ʱ����Ҫ���İ���5������������
	CopyCB(ChessB);
	int i, j, getpoint, temppoint;
	getpoint = CBPoint();
	Point temp;
	temp.x = -1;
	temp.y = -1;
	temp.pre = NULL;
	BetaMax(-10000000, 100000000, 4, temp);
	return &temp;
}

long double BetaMax(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest) {
	if (depth == 0) {
		return CBPoint();
	}
	Point ptTmp;
	for (int i = 0;i <= 14;i++) {
		for (int j = 0;j <= 14;j++) {
			if (Check(i, j)) {
				CB[i][j] = 9;//��һ����
				long double dbScore = AlphaMin(dbAlphaMin, dbBetaMax, depth - 1, ptTmp);
				CB[i][j] = OriginCB[i][j];//�ָ�
				if (dbScore >= dbBetaMax)
				{
					ptbest.x = i;
					ptbest.y = j;
					return dbBetaMax;       // dbBetaMax-cutoff
											//                    return dbScore;  
				}
				if (dbScore > dbAlphaMin)
				{
					ptbest.x = i;
					ptbest.y = j;
					dbAlphaMin = dbScore;   // dbAlphaMin acts like max in MiniMax
				}
			}
		}
	}
	return dbAlphaMin;
}


long double AlphaMin(long double dbAlphaMin, long double dbBetaMax, int depth, Point &ptbest) {
	if (depth == 0) {
		return CBPoint();
	}
	for (int i = 0;i <= 14;i++) {
		for (int j = 0;j <= 14;j++) {
			if (Check(i, j)) {
				CB[i][j] = 10;//��һ����
				long double dbScore = BetaMax(dbAlphaMin, dbBetaMax, depth - 1, ptbest);
				CB[i][j] = OriginCB[i][j];//�ָ�
				if (dbScore <= dbAlphaMin)
				{
					ptbest.x = i;
					ptbest.y = j;
					//if (dbScore <= -500000) {
						//cout << "what the fuck" << endl;
						//cin.get();
					//}
					return dbAlphaMin;      // dbAlphaMin-cutoff
											//                 return dbScore;          
				}
				if (dbScore < dbBetaMax)
				{
					ptbest.x = i;
					ptbest.y = j;
					dbBetaMax = dbScore;    // dbBetaMax acts like min in MiniMax
				}
			}
		}
	}
	return dbBetaMax; // Min
}