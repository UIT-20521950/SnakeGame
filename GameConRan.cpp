#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "mylib.h"
#include <iomanip>

#define MAX 100

using namespace std;

int len = 3;
int od = 0;
int const width = 84;
int const height = 24;
int delay = 250;
char head = (char)2;
char tail = (char)2;
void PlayGame();
void Menu();
void Skin();
void Dokho();
void Wall();
void printWelcome();
void printInfo();
void printLoadingBar();

struct Point {
	int x, y;
};
class Snake
{
public:
	Point a[MAX];
	Snake();
	void Paint();
	void Del_data();
	void Move(int w, int t);
	void Direction(int h, int& w, int& t);
	bool GameOver(int w, int t);
	void Food(int& w, int& t);
	void Check_food(int& w, int& t);
	bool Eat(int w, int t);
	void End(int Score);
};
//Ham khoi tao vi tri cho ran
Snake::Snake()
{
	int w = 15, t = 5;
	for (int i = 0; i < len; i++) {
		a[i].x = w;
		a[i].y = t;
		w--;
	}
}
//Ham ve ran
void Snake::Paint()
{
	for (int i = 0; i < len; i++) {
		gotoXY(a[i].x, a[i].y);
		if (i == 0) cout << head;
		else cout << tail;
	}
}
//Xoa vi tri ran
void Snake::Del_data()
{
	for (int i = 0; i < len; i++) {
		gotoXY(a[i].x, a[i].y);
		cout << " ";
	}
}
//Ran di chuyen
void Snake::Move(int w, int t)
{
	for (int i = len; i > 0; i--) {
		a[i].x = a[i - 1].x;
		a[i].y = a[i - 1].y;
	}
	a[0].x = w;
	a[0].y = t;
}
//Ham chon phuon huong cho ran
void Snake::Direction(int h, int& w, int& t) {
	if (h == 0 && od == 1 || h == 1 && od == 0 || h == 2 && od == 3 || h == 3 && od == 2) h = od; //khong cho ran chay nguoc lai
	od = h;
	if (h == 0) w++;
	else if (h == 1) w--;
	else if (h == 2) t++;
	else if (h == 3) t--;
}
//Ket thuc tro choi
bool Snake::GameOver(int w, int t)
{
	int kt1 = 0, kt2 = 0;
	if (w == 10 || w == 89 || t == 4 || t == 23) kt1 = 1;
	for (int i = 1; i < len; i++) {
		if (a[0].x == a[i].x && a[0].y == a[i].y) kt2 = 1;
	}
	if (kt1 == 1 || kt2 == 1) {
		len = 3;
		return false;
	}
	return true;
}
//Ham tao thuc an
void Snake::Food(int& w, int& t)
{
	w = rand() % (88 - 11 + 1) + 11;
	t = rand() % (22 - 5 + 1) + 5;
	SetColor(3);
	gotoXY(w, t);
	cout << (char)3;
}
//Check thuc an co trung voi duoi ran, trung thi tao lai
void Snake::Check_food(int& w, int& t) {
	for (int i = 1; i < len; i++) {
		if (a[i].x == w && a[i].y == t) {
			i = 1;
			Food(w, t);
		}
	}
}
//Ham kiem tra xem ran da an moi chua
bool Snake::Eat(int w, int t)
{
	if (w == a[0].x && t == a[0].y) return true;
	return false;
}
//Ket thuc
void Snake::End(int Score) {
	system("cls");
	SetColor(12);
	for (int i = 0; i < 40; i++) cout << "=";
	SetColor(9);
	cout << "\n\tKet thuc";
	cout << "\n\tYour score: " << Score << "\n";
	SetColor(12);
	for (int i = 0; i < 40; i++) cout << "=";
	cout << "\n";
	system("pause");
}


int main()
{
	ShowCur(0);
	printWelcome();
	printInfo();
	printLoadingBar();
	Menu();
	return 0;
}
void PlayGame()
{
	ShowCur(0);
	srand(time(NULL));
	bool check = true;
	Snake sn;
	Wall();
	sn.Paint();
	char k;
	int x = 16, y = 5, ph = 0, score = 0, fx = 0, fy = 0;
	sn.Food(fx, fy);
	sn.Check_food(fx, fy);
	while (check == true) {
		sn.Del_data();
		if (_kbhit()) {
			k = _getch();
			if (k == 'd') ph = 0;
			if (k == 'a') ph = 1;
			if (k == 's') ph = 2;
			if (k == 'w') ph = 3;
		}
		sn.Move(x, y);
		sn.Direction(ph, x, y);
		if (sn.Eat(fx, fy) == true) {
			len++;
			score += 5;
			gotoXY(40, 25);
			cout << "Score: " << score;
			sn.Food(fx, fy);
			sn.Check_food(fx, fy);
		}
		check = sn.GameOver(x, y);
		sn.Paint();
		Sleep(delay);
	}
	sn.End(score);
}
void Wall()
{
	int x = 10;
	SetColor(13);
	for (int i = 4; i < height; i++) {
		gotoXY(x, i);
		for (int j = 4; j < width; j++) {
			if (i == 4 || i == height - 1) cout << (char)178;
			else {
				if (j == 4 || j == width - 1) cout << (char)178;
				else cout << " ";
			}
		}
		cout << "\n";
	}
}


void Dokho()
{
	int check = 0;
	char ch;
	while (check == 0)
	{
		system("cls");
		SetColor(12);
		for (int i = 0; i < 40; i++) cout << "=";
		SetColor(11);
		gotoXY(14, 1);
		cout << "| Chon mode |";
		SetColor(7);
		gotoXY(16, 2);
		cout << "1) Easy";
		gotoXY(16, 3);
		cout << "2) Normal";
		gotoXY(16, 4);
		cout << "3) Hard";
		gotoXY(16, 5);
		cout << "4) Back\n";
		SetColor(12);
		for (int i = 0; i < 40; i++) cout << "=";
		ch = _getch();
		if (ch == 49 || ch == 50 || ch == 51 || ch == 52) {
			check = 1;
			if (ch == 49) delay = 250;
			else if (ch == 50) delay = 150;
			else if (ch == 51) delay = 50;
		}
	}
}
void Skin()
{
	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	int check = 0;
	char ch;
	/*-----------------------------------------------------------------------------------------*/
	while (check == 0) {
		system("cls");
		SetColor(12);
		for (int i = 0; i < 40; i++) cout << "=";
		SetColor(11);
		gotoXY(14, 1);
		cout << "| Chon skin |";
		SetColor(5);
		gotoXY(17, 2);
		cout << "1) oo" << (char)153;
		gotoXY(17, 3);
		cout << "2) " << (char)2 << (char)2 << (char)2;
		gotoXY(17, 4);
		cout << "3) " << (char)254 << (char)254 << (char)254;
		gotoXY(17, 5);
		cout << "4) Back\n";
		SetColor(12);
		for (int i = 0; i < 40; i++) cout << "=";
		/*-----------------------------------------------------------------------------------------*/
		ch = _getch();
		if (ch == 49 || ch == 50 || ch == 51 || ch == 52) {
			check = 1;
			if (ch == 49) {
				head = (char)153;
				tail = 'o';
			}
			else if (ch == 50) head = tail = (char)2;
			else if (ch == 51) head = tail = (char)254;
		}
	}
}
void Menu()
{
	int check = 0;
	char ch;
	/*-----------------------------------------------------------------------------------------*/
	system("cls");
	SetColor(15);
	while (check == 0) {
		system("cls");
		SetColor(12);
		gotoXY(42, 10);
		for (int i = 0; i < 40; i++) cout << "=";
		SetColor(9);
		gotoXY(50, 11);
		cout << ">>>>GAME RAN SAN MOI<<<<";
		SetColor(13);
		gotoXY(60, 12);
		cout << "1) Play";
		gotoXY(60, 13);
		cout << "2) Skin";
		gotoXY(59, 14);
		cout << "3) Do kho";
		gotoXY(58, 15);
		cout << "4) Huong dan";
		gotoXY(60, 16);
		cout << "5) Exit\n";
		SetColor(4);
		SetColor(12);
		gotoXY(42, 17);
		for (int i = 0; i < 40; i++) cout << "=";
		/*-----------------------------------------------------------------------------------------*/
		ch = _getch();
		if (ch == 49) PlayGame();
		else if (ch == 50) Skin();
		else if (ch == 51) Dokho();
		else if (ch == 52) { /*huong dan*/
			system("cls");
			SetColor(12);
			for (int i = 0; i < 40; i++) cout << "=";
			SetColor(11);
			gotoXY(14, 1);
			cout << "| HUONG DAN |";
			SetColor(3);
			gotoXY(15, 2);
			cout << "A: Qua trai";
			gotoXY(15, 3);
			cout << "D: Qua phai";
			gotoXY(15, 4);
			cout << "W: Di len";
			gotoXY(15, 5);
			cout << "S: Di xuong\n";
			SetColor(12);
			for (int i = 0; i < 40; i++) cout << "=";
			cout << "\n";
			system("pause");
		}
		else if (ch == 53) check = 1; /*KET THUC*/
	}
	system("cls");
	SetColor(14);
	gotoXY(42, 4);
	if (check == 1) cout << ">>> CAM ON BAN DA THAM GIA... !!! <<<\n";
}
void printWelcome()
{
	string str;
	ifstream fi;
	int lines = 1;
	fi.open("ranlogo.txt", ios::in);
	SetColor(14);
	while (!fi.eof())
	{
		gotoXY(58, lines++);
		getline(fi, str);
		cout << str;
	}
	int i;
	while (true)
	{
		i = rand() % 15 + 1 + 1;
		if (i % 16 == 0)
			i = 1;
		SetColor(i);
		gotoXY(8, 1);
		cout << "   _____             _         ";
		gotoXY(8, 2);
		cout << "  / ____|           | |        ";
		gotoXY(8, 3);
		cout << " | (___  _ __   __ _| | _____  ";
		gotoXY(8, 4);
		cout << "  \\___ \\| '_ \\ / _` | |/ / _ \\ ";
		gotoXY(8, 5);
		cout << "  ____) | | | | (_| |   <  __/ ";
		gotoXY(8, 6);
		cout << " |_____/|_| |_|\\__,_|_|\\_\\___| ";

		gotoXY(18, 8);
		cout << "\\ \\ / /             (_)       ";
		gotoXY(18, 9);
		cout << " \\ V / ___ _ __  _____  __ _  ";
		gotoXY(18, 10);
		cout << "  > < / _ \\ '_ \\|_  / |/ _` | ";
		gotoXY(18, 11);
		cout << " / . \\  __/ | | |/ /| | (_| | ";
		gotoXY(18, 12);
		cout << "/_/ \\_\\___|_| |_/___|_|\\__,_| ";
		gotoXY(18, 13);
		Sleep(500);
		if (_kbhit() == true)
		{
			char a = _getch();
			if (a == 13)
				break;
		}

	}
}
// đã hoàn chỉnh ko đụng tới
void printInfo()
{
	int x = 10, y = 22;
	int xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                         ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Member 1: Tran Quoc Thinh";
		y--;
		if (y == 14)
			break;
		Sleep(100);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                               ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Member 2: Nguyen Tan Phuong Nam";
		y--;
		if (y == 15)
			break;
		Sleep(100);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                         ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Member 3: Pham Quoc Nghia";
		y--;
		if (y == 16)
			break;
		Sleep(100);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                           ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Member 4: Nguyen Hoan Thien";
		y--;
		if (y == 17)
			break;
		Sleep(100);
	}
	x = 10, y = 22;
	xcu = -1, ycu = -1;
	while (true)
	{
		// xoa cu
		gotoXY(xcu, ycu);
		cout << "                        ";
		xcu = x;
		ycu = y;
		gotoXY(x, y);
		cout << "Group: ---";
		y--;
		if (y == 18)
			break;
		Sleep(100);
	}

}
// đã hoàn chỉnh ko đụng tới
void printLoadingBar()
{
	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	SetColor(2);
	gotoXY(7, 21);
	cout << "LOADING..";
	char x = 219;
	int r = 0;
	for (int i = 18; i <= 80; i++)
	{
		gotoXY(16, 21);
		cout << ".";
		Sleep(80);
		gotoXY(16, 21);
		cout << " ";
		gotoXY(i, 21);
		if (i <= 44)
		{
			Sleep(2);
		}
		else
		{
			Sleep(2);
		}
		cout << x;
		gotoXY(82, 21);
		if (i == 80)
		{
			cout << 100 << "%";
			gotoXY(16, 21);
			cout << ".";
			break;
		}
		else
		{
			cout << r << "%";
			r++;
		}
	}
	_getch();
}
