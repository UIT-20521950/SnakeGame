#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "myLib.h"

#define MAX 100

using namespace std;

int len = 4;
void Wall();

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
	void Move(int t, int w);
	bool GameOver(int x, int y);
};

Snake::Snake()
{
	int y = 17, z = 3;
	for (int i = 0; i < len; i++) {
		a[i].x = y;
		a[i].y = z;
		y--;
	}
}
void Snake::Paint()
{
	for (int i = 0; i < len; i++) {
		gotoXY(a[i].x, a[i].y);
		if (i == 0) cout << "0";
		else cout << "o";
	}
}
void Snake::Del_data()
{
	for (int i = 0; i < len; i++) {
		gotoXY(a[i].x, a[i].y);
		cout << " ";
	}
}
void Snake::Move(int t, int w)
{
	for (int i = len; i > 0; i--) {
		a[i].x = a[i - 1].x;
		a[i].y = a[i - 1].y;
	}
	a[0].x = t;
	a[0].y = w;
}
bool Snake::GameOver(int x, int y)
{
	if (x == 10 || x == 95 || y == 1 || y == 25) return false;
}


int main()
{
	bool check = true;
	Snake sn;
	ShowCur(0);
	Wall();
	sn.Paint();
	char k;
	int x = 18, y = 3, ph = 0;
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
		if (ph == 0) x++;
		else if (ph == 1) x--;
		else if (ph == 2) y++;
		else if (ph == 3) y--;
		check = sn.GameOver(x, y);
		sn.Paint();
		Sleep(300);
	}
	return 0;
}

void Wall() {
	for (int x = 1; x <= 25; x++)
	{
		gotoXY(10, x);
		cout << "|";
		gotoXY(95, x);
		cout << "|";
	}
	for (int y = 10; y <= 95; y++) {
		gotoXY(y, 1);
		cout << "-";
		gotoXY(y, 25);
		cout << "-";
	}
}