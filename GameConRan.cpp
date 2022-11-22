#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "MyLib.h"

#define MAX 100

using namespace std;

int len = 4;
int const width = 80;
int const height = 20;
char head = '0', tail = 'o';

void Mode();
void Skin();
void Menu();
void Wall();

struct Point {
	int x, y;
};
class Snake
{
public:
	Point a[MAX];
	Snake() {
		int w = 16, t = 3;
		for (int i = 0; i < len; i++) {
			a[i].x = w;
			a[i].y = t;
			w--;
		}
	}
	void Paint() {
		SetColor(1);
		for (int i = 0; i < len; i++) {
			gotoXY(a[i].x, a[i].y);
			if (i == 0) cout << head;
			else cout << tail;
		}
	}
	void Del_data() {
		for (int i = 0; i < len; i++) {
			gotoXY(a[i].x, a[i].y);
			cout << " ";
		}
	}
	void Move(int w, int t) {
		for (int i = len; i > 0; i--) {
			a[i].x = a[i - 1].x;
			a[i].y = a[i - 1].y;
		}
		a[0].x = w;
		a[0].y = t;
	}
	void Direction(int h, int& w, int& t) {
		if (h == 0) w++;
		else if (h == 1) w--;
		else if (h == 2) t++;
		else if (h == 3) t--;
	}
	bool Gameover(int w, int t) {
		int th1 = 0, th2 = 0;
		if (w == 10 || w == 89 || t == 0 || t == 19) th1 = 1;
		for (int i = 1; i < len; i++) {
			if (a[0].x == a[i].x && a[0].y == a[i].y) th2 = 1;
		}
		if (th1 == 1 || th2 == 1) {
			len = 4;
			return false;
		}
		return true;
	}
	void Food(int& w, int& t) {
		w = rand() % (88 - 11 + 1) + 11;
		t = rand() % (18 - 1 + 1) + 1;
		SetColor(2);
		gotoXY(w, t);
		cout << "$";
	}
	void Check_food(int& w, int& t) {
		for (int i = 1; i < len; i++) {
			if (a[i].x == w && a[i].y == t) {
				i = 1;
				Food(w, t);
			}
		}
	}
	void Eat(int& l, int& w, int& t) {
		if (a[0].x == w && a[0].y == t) {
			l++;
			Food(w, t);
			Check_food(w, t);
		}
	}
};


void play()
{
	system("cls");
	srand(time(NULL));
	ShowCur(0);
	bool check = true;
	Snake sn;
	Wall();
	sn.Paint();
	int x = 17, y = 3, h = 0, fx = 0, fy = 0;
	char kt;
	sn.Food(fx, fy);
	sn.Check_food(fx, fy);
	while (check == true)
	{
		if (_kbhit()) {
			kt = _getch();
			if (kt == 'd') h = 0;
			if (kt == 'a') h = 1;
			if (kt == 's') h = 2;
			if (kt == 'w') h = 3;
		}
		sn.Del_data();
		sn.Move(x, y);
		sn.Direction(h, x, y);
		sn.Eat(len, fx, fy);
		sn.Paint();
		if (!sn.Gameover(x, y)) check = false;
		Sleep(150);
	}
}
int main()
{
	Menu();
	return 0;
}
void Wall()
{
	int x = 10;
	SetColor(7);
	for (int i = 0; i < height; i++) {
		gotoXY(x, i);
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1) cout << "=";
			else {
				if (j == 0 || j == width - 1) cout << "|";
				else cout << " ";
			}
		}
		cout << "\n";
	}
}
void Mode()
{
	int check = 0;
	char ch;
	while (check == 0)
	{
		system("cls");
		for (int i = 0; i < 40; i++) cout << "=";
		cout << "\n\tChon skin";
		cout << "\n\t1) Easy";
		cout << "\n\t2) Normal";
		cout << "\n\t3) Hard";
		cout << "\n\t4) Back\n";
		for (int i = 0; i < 40; i++) cout << "=";
		ch = _getch();
		if (ch == 49 || ch == 50 || ch == 51) check = 1;
		else if (ch == 52) check = 1;
	}
}
void Skin()
{
	int check = 0;
	char ch;
	while (check == 0) {
		system("cls");
		for (int i = 0; i < 40; i++) cout << "=";
		cout << "\n\tChon skin";
		cout << "\n\t1) oo0";
		cout << "\n\t2) xxX";
		cout << "\n\t3) Back\n";
		for (int i = 0; i < 40; i++) cout << "=";
		ch = _getch();
		if (ch == 49) {
			head = '0'; tail = 'o';
			check = 1;
		}
		else if (ch == 50) {
			head = 'X'; tail = 'x';
			check = 1;
		}
		else if (ch == 51) check = 1;
	}
}
void Menu()
{
	int check = 0;
	char ch;
	while (check == 0) {
		system("cls");
		SetColor(7);
		for (int i = 0; i < 40; i++) cout << "=";
		cout << "\n\t1) Play";
		cout << "\n\t2) Skin";
		cout << "\n\t3) Mode";
		cout << "\n\t4) Huong dan";
		cout << "\n\t5) Exit\n";
		for (int i = 0; i < 40; i++) cout << "=";
		ch = _getch();
		if (ch == 49) play();
		else if (ch == 50) Skin();
		else if (ch == 51) Mode();
		else if (ch == 52) {
			system("cls");
			for (int i = 0; i < 40; i++) cout << "=";
			cout << "\n\tA: Qua trai";
			cout << "\n\tD: Qua phai";
			cout << "\n\tW: Di len";
			cout << "\n\tS: Di xuong\n";
			for (int i = 0; i < 40; i++) cout << "=";
			system("pause");
		}
		else if (ch == 53) check = 1;
	}
}

