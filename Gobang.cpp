#include"ChessAI.h"
using namespace std;
const char ChessBoard[11][4] = { "��","��","��","��","��","��","��","��","��","��","��" };
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
int CP = 0; //��¼�ȷֵ�ȫ�ֱ���

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
	cout << "�������飡�㱻���Ի�����" << endl;
	cin.get();
	return;
}

void Playerwin() {
	PP++;
	cout << "�������飡������ʤ��" << endl;
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
			cout << ChessBoard[CB[Row][Col]] << "��";
		}
		if (Row == 0) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "��ʾ��                 " << endl;
		}
		else if (Row == 1) {
			if (Temp==NULL)
			cout << ChessBoard[CB[Row][14]] << setw(40) << "��ʼ�Ծ�               " << endl;
			else
			cout << ChessBoard[CB[Row][14]] << setw(34) << "���Ե��������˵� " <<Temp->x<<" �� "<<Temp->y<<" ��"<< endl;
		}
		else if (Row == 2) {
			if (Back == 1)
				cout << ChessBoard[CB[Row][14]] << setw(40) << "����ɹ�               " << endl;
			else if (Back == 2)
				cout << ChessBoard[CB[Row][14]] << setw(40) << "����ʧ�ܣ���ǰ��δ���� " << endl;
			else cout << ChessBoard[CB[Row][14]] << endl;
		}
		else if (Row == 4) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "����                 "<<endl;
		}
		else if (Row == 5) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "���� -1 -1 ����Ͷ������" << endl;
		}
		else if (Row == 6) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "���� -2 -2 �������    " << endl;
		}
		else if (Row == 8) {
			cout << ChessBoard[CB[Row][14]] << setw(40) << "��ǰ�ȷ֣�             " << endl;
		}
		else if (Row == 9) {
			cout << ChessBoard[CB[Row][14]] << setw(30) <<"��ҵ÷�     "<<setw(10)<<PP<< endl;
		}
		else if (Row == 10) {
			cout << ChessBoard[CB[Row][14]] << setw(30) << "���Ե÷�     " << setw(10) << CP << endl;
		}
		else cout << ChessBoard[CB[Row][14]] << endl;
		if(Row!=14) cout << "      ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��" << endl;
	}
	cout << endl;
	return;
}


void main() {
	int Mode;
	system("color 3f");
	system("mode con cols=120 lines=40");
	system("title ����ҵ������");
	cout << endl << endl << endl << "\t\t\t\t\t\t***********************" << endl;
	cout << "\t\t\t\t\t\t      ������v2.0" << endl;
	cout << "\t\t\t\t\t\t***********************" << endl << endl << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\t\t\t\t\t\tOPP����ҵ " << endl << endl;
	cout << "\t\t\t\t\t\t���ܣ� " << endl;
	cout << "\t\t\t\t\t\tʵ����һ���򵥵��������ս" << endl;
	cout << endl<<endl<<endl;
	cout << "\t\t\t\t\t\t�鳤:ëһ�� ѧ�ţ�3130001004" << endl << endl;
	cout << "\t\t\t\t\t\t��Ա:³��� ѧ�ţ�3140101224" << endl<<endl;
	cout << "\t\t\t\t\t\t     ��  � ѧ�ţ�3140100999"<<endl<<endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\tͨ������������ѡ�����Ķ���" << endl << endl;
	cout << "\t\t\t\t\t\t      1����ͨ����" << endl << endl;
	cout << "\t\t\t\t\t\t      2���߼����ԣ����ԣ�" << endl << endl;  //Ŀǰ�в�����߼����������������
	cout << "------------------------------------------------------------------------------------------------------------------------";
	
	cin >> Mode;

	while (Mode != 1 && Mode != 2) {
		cout << "����������������������" << endl;
		cin >> Mode;
	}
	bool Again,Gameover,NR;
	char Againhandle;
	int Row, Col;//������������
	Point *P,*Temp;  //��¼��ǰ���ӵ�
	P = new Point;
	Again = true;
	while (Again) {
		int Back = 0;//�������̴�ӡʱ�Ļ�����ʾ
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
			6,7,7,7,7,7,7,7,7,7,7,7,7,7,8 }; //���̳�ʼ��
		Gameover = false;
		while (!Gameover) {
			system("color 3f");
			system("cls");
			ShowCB(CB,P->pre,Back);
			Back = 0;
			cout << "��������� , ���Щ��еķ�ʽ , �м��ÿո�ֿ���";
			NR = false;//���������ȷ����
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
						cout << "��λ���ѱ����ӣ����������ѡ��";
					}
					else {
						CB[Row][Col] = 10;          //�������
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
					cout << "λ�ô������������ѡ��";
				}
				}
			if (Row != -1 && Row != -2) {
				if(Mode==1) Temp = NormalAI(CB);
				else Temp = HardAI(CB);
				P->x = Temp->x;
				P->y = Temp->y;
				CB[P->x][P->y] = 9;//��������
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
		cout << "���Ƿ���Ҫ�����Ծ֣�(Y/N)" ;
		cin >> Againhandle;
		cin.get();
		if (Againhandle != 'y' && Againhandle != 'Y') Again = false;
		}
		cout << endl << endl << endl << endl << endl << endl << "\t\t\t\t\t\t***********************" << endl;
		cout << "\t\t\t\t\t\t        ллʹ��" << endl;
		cout << "\t\t\t\t\t\t***********************" << endl << endl << endl;
		cin.get();
	
	}
	
