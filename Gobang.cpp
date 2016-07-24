#include"ChessAI.h"
using namespace std;
const char ChessBoard[11][4] = { "┌","┬","┐","├","┼","┤","└","┴","┘","○","●" };
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
	6,7,7,7,7,7,7,7,7,7,7,7,7,7,8 }; 
int PP = 0;
int CP = 0; //记录比分的全局变量

bool CheckWinner(int CB[15][15], int x, int y)
{
	int who,luozi;
	who = CB[x][y];
	int i, j;
	luozi = 0;
	for (i = 0;i <= 14;i++) {
		if (CB[i][y] == who) {
			luozi++;
			if (luozi == 5) return true;
		}
		else luozi = 0;
	}
	luozi = 0;
	for (j = 0;j <= 14;j++) {
		if (CB[x][j] == who) {
			luozi++;
			if (luozi == 5) return true;
		}
		else luozi = 0;
	}
	luozi = 0;
	for (i = 0;i <= 14;i++) {
		if (((i - x + y) >= 0) && ((i - x + y) <= 14)) {
			if (CB[i][i-x+y] == who) {
				luozi++;
				if (luozi == 5) return true;
			}
			else luozi = 0;
		}
	}
	luozi = 0;
	for (i = 0;i <= 14;i++) {
		if (((x + y-i) >= 0) && ((x + y-i) <= 14)) {
			if (CB[i][x+y-i] == who) {
				luozi++;
				if (luozi == 5) return true;
			}
			else luozi = 0;
		}
	}
	return false;
}

void AIwin()
{
	CP++;
	cout << "五子连珠！你被电脑击败了" << endl;
	cin.get();
	return;
}

void Playerwin() {
	PP++;
	cout << "五子连珠！你获得了胜利" << endl;
	cin.get();
	return;
}

void ShowCB(int CB[15][15],Point *Temp,int Back)
{
	int Row, Col;
	cout <<endl <<endl << "       0   1   2   3   4   5   6   7   8   9   10  11  12  13  14" << endl;
	for (Row = 0;Row <= 14;Row++) {
		cout << setw(6) << Row;
		for (Col = 0;Col <= 13;Col++) {
			cout << ChessBoard[CB[Row][Col]] << "─";
		}
		if (Row == 0) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "提示：                 " << endl;
		}
		else if (Row == 1) {
			if (Temp==NULL)
			cout << ChessBoard[CB[Row][14]] << setw(40) << "开始对局               " << endl;
			else
			cout << ChessBoard[CB[Row][14]] << setw(34) << "电脑的子落在了第 " <<Temp->x<<" 行 "<<Temp->y<<" 列"<< endl;
		}
		else if (Row == 2) {
			if (Back == 1)
				cout << ChessBoard[CB[Row][14]] << setw(40) << "悔棋成功               " << endl;
			else if (Back == 2)
				cout << ChessBoard[CB[Row][14]] << setw(40) << "悔棋失败，当前还未落子 " << endl;
			else cout << ChessBoard[CB[Row][14]] << endl;
		}
		else if (Row == 4) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "规则：                 "<<endl;
		}
		else if (Row == 5) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "输入 -1 -1 代表投子认输" << endl;
		}
		else if (Row == 6) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "输入 -2 -2 代表悔棋    " << endl;
		}
		else if (Row == 8) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "当前比分：             " << endl;
		}
		else if (Row == 9) {
			cout << ChessBoard[CB[Row][14]] << setw(30) <<"玩家得分     "<<setw(10)<<PP<< endl;
		}
		else if (Row == 10) {
			cout << ChessBoard[CB[Row][14]] << setw(30) << "电脑得分     " << setw(10) << CP << endl;
		}
		else cout << ChessBoard[CB[Row][14]] << endl;
		if(Row!=14) cout << "      │  │  │  │  │  │  │  │  │  │  │  │  │  │  │" << endl;
	}
	cout << endl;
	return;
}


void main() {
	int Mode;
	system("color 3f");
	system("mode con cols=120 lines=40");
	system("title 大作业五子棋");
	cout << endl << endl << endl << "\t\t\t\t\t\t***********************" << endl;
	cout << "\t\t\t\t\t\t      五子棋v2.0" << endl;
	cout << "\t\t\t\t\t\t***********************" << endl << endl << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\t\t\t\t\t\tOPP大作业 " << endl << endl;
	cout << "\t\t\t\t\t\t介绍： " << endl;
	cout << "\t\t\t\t\t\t实现了一个简单的五子棋对战" << endl;
	cout << endl<<endl<<endl;
	cout << "\t\t\t\t\t\t组长:毛一鸣 学号：3130001004" << endl << endl;
	cout << "\t\t\t\t\t\t组员:鲁泽地 学号：3140101224" << endl<<endl;
	cout << "\t\t\t\t\t\t     王  昊 学号：3140100999"<<endl<<endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t通过输入数字来选择您的对手" << endl << endl;
	cout << "\t\t\t\t\t\t      1、普通电脑" << endl << endl;
	cout << "\t\t\t\t\t\t      2、高级电脑（测试）" << endl << endl;  //目前尚不清楚高级电脑棋力到底如何
	cout << "------------------------------------------------------------------------------------------------------------------------";
	
	cin >> Mode;

	while (Mode != 1 && Mode != 2) {
		cout << "您的输入有误，请重新输入" << endl;
		cin >> Mode;
	}
	bool Again,Gameover,NR;
	char Againhandle;
	int Row, Col;//玩家输入的行列
	Point *P,*Temp;  //记录当前落子点
	P = new Point;
	Again = true;
	while (Again) {
		int Back = 0;//控制棋盘打印时的悔棋提示
		P->pre = NULL;
		int CB[15][15] = {
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
			6,7,7,7,7,7,7,7,7,7,7,7,7,7,8 }; //棋盘初始化
		Gameover = false;
		while (!Gameover) {
			system("color 3f");
			system("cls");
			ShowCB(CB,P->pre,Back);
			Back = 0;
			cout << "请玩家落子 , 以行│列的方式 , 中间用空格分开：";
			NR = false;//控制玩家正确落子
			while (!NR) {
				cin >> Row >> Col;
				cin.get();
				if (Row == -1 && Col == -1) {
					AIwin();
					NR = true;
					Gameover = true;
				}
				else if (Row >= 0 && Row <= 14 && Col >= 0 && Col <= 14) {
					if (CB[Row][Col] == 9 || CB[Row][Col] == 10) {
						cout << "该位置已被落子，请玩家重新选择：";
					}
					else {
						CB[Row][Col] = 10;          //玩家落子
						if (CheckWinner(CB,Row,Col)) {
							system("color 2f");
							system("cls");
							ShowCB(CB,P->pre,Back);
							Playerwin();
							Gameover = true;
						}
						
						P->x = Row;
						P->y = Col;
						Temp = P;
						P= new Point;
						P->pre = Temp;
						NR = true;
					}
				}
				else if (Row == -2 && Col == -2) {
					if (P->pre != NULL) {
						P = P->pre;
						CB[P->x][P->y] = OriginCB[P->x][P->y];
						P = P->pre;
						CB[P->x][P->y] = OriginCB[P->x][P->y];
						Back = 1;
						
					}
					else {
						Back = 2;
					}
					NR = true;
				}
				else {
					cout << "位置错误，请玩家重新选择：";
				}
				}
			if (Row != -1 && Row != -2) {
				if(Mode==1) Temp = NormalAI(CB);
				else Temp = HardAI(CB);
				P->x = Temp->x;
				P->y = Temp->y;
				CB[P->x][P->y] = 9;//电脑落子
				if (CheckWinner(CB, P->x, P->y)) {
					system("color 4f");
					system("cls");
					ShowCB(CB,P->pre, Back);
					AIwin();
					Gameover = true;
				}
				
				Temp = P;
				P = new Point;
				P->pre = Temp;
			}
			}
		
		while (P->pre != NULL) {
			Temp = P;
			P = P->pre;
			free(Temp);
			Temp = NULL;
		}
		cout << "您是否想要继续对局？(Y/N)" ;
		cin >> Againhandle;
		cin.get();
		if (Againhandle != 'y' && Againhandle != 'Y') Again = false;
		}
		cout << endl << endl << endl << endl << endl << endl << "\t\t\t\t\t\t***********************" << endl;
		cout << "\t\t\t\t\t\t        谢谢使用" << endl;
		cout << "\t\t\t\t\t\t***********************" << endl << endl << endl;
		cin.get();
	
	}
	
