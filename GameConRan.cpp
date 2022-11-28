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

struct Point
{
	int x, y;
};
class Snake
{
public:
	Point a[MAX];
	Snake()
	{
		int w = 16, t = 3;
		for (int i = 0; i < len; i++)
		{
			a[i].x = w;
			a[i].y = t;
			w--;
		}
	}
	void Paint()
	{
		SetColor(1);
		for (int i = 0; i < len; i++)
		{
			gotoXY(a[i].x, a[i].y);
			if (i == 0)
				cout << head;
			else
				cout << tail;
		}
	}
	void Del_data()
	{
		for (int i = 0; i < len; i++)
		{
			gotoXY(a[i].x, a[i].y);
			cout << " ";
		}
	}
	void Move(int w, int t)
	{
		for (int i = len; i > 0; i--)
		{
			a[i].x = a[i - 1].x;
			a[i].y = a[i - 1].y;
		}
		a[0].x = w;
		a[0].y = t;
	}
	void Direction(int h, int &w, int &t)
	{
		if (h == 0)
			w++;
		else if (h == 1)
			w--;
		else if (h == 2)
			t++;
		else if (h == 3)
			t--;
	}
	bool Gameover(int w, int t) // check game
	{
		int th1 = 0, th2 = 0;
		if (w == 10 || w == 89 || t == 0 || t == 19)
			th1 = 1;
		for (int i = 1; i < len; i++)
		{
			if (a[0].x == a[i].x && a[0].y == a[i].y)
				th2 = 1;
		}
		if (th1 == 1 || th2 == 1)
		{
			len = 4;
			return false;
		}
		return true;
	}
};
void Wall() // Vẽ khung trò chơi, tường
{
	int x = 10;
	SetColor(7);
	for (int i = 0; i < height; i++)
	{
		gotoXY(x, i);
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height - 1)
				cout << "=";
			else
			{
				if (j == 0 || j == width - 1)
					cout << "|";
				else
					cout << " ";
			}
		}
		cout << "\n";
	}
}

void play()
{
	bool check = true;
	srand(time(NULL));
	ShowCur(0);
	Snake sn;
	Wall(); // Draw wall
	sn.Paint();
	int x = 17, y = 3, h = 0;
	char kt;
	while (check == true)
	{
		if (_kbhit())
		{
			kt = _getch();
			if (kt == 'd')
				h = 0;
			if (kt == 'a')
				h = 1;
			if (kt == 's')
				h = 2;
			if (kt == 'w')
				h = 3;
		}
		sn.Del_data();
		sn.Move(x, y);
		sn.Direction(h, x, y);
		sn.Paint();
		if (!sn.Gameover(x, y)) check = false; // check gameover
		Sleep(150);
	}
}
int main()
{
	play();
	return 0;
}