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

};


void play()
{
	srand(time(NULL));
	ShowCur(0);
	Snake sn;
	sn.Paint();
	int x = 17, y = 3, h = 0;
	char kt;
	while (true)
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
		sn.Paint();
		Sleep(150);
	}
}
int main()
{
	play();
	return 0;
}