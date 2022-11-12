// code tai day
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
const int width = 20;
const int height = 20;
bool gameOver = false;
struct Point
{
    int x, y;
};
enum controlgame
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
controlgame dir;
class Snake
{
public:
    struct Point Tail[100];
    struct Point snake;
    struct Point bom;
    int nTail;
    int score;
    Snake()
    {
        nTail = 2;
        Tail[0].x = snake.x;
        Tail[0].y = snake.y;
        Tail[1].x = snake.x+1;
        Tail[1].y = snake.y+1;
    };
    void Setup()
    {
        gameOver = false;
        dir = STOP;
        snake.x = width / 2;
        snake.y = height / 2;
        bom.x = rand() % width;
        bom.y = rand() % height;
        score = 0;
        if (gameOver == false)
            cout << "Setup finish" << endl;
    }
    void Draw()
    {
        system("cls");
        for (int i = 0; i < width + 1; i++)
            cout << "# "; // linetop
        cout << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    cout << "#"; // lineleft
                else
                    cout << " ";
                // ben trong tro choi chua con ran
                if (i == snake.y && j == snake.x)
                    cout << "X"; // sanke
                else if (i == bom.y && j == bom.x)
                    cout << "0";
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (Tail[k].x == j && Tail[k].y == i)
                        {
                            cout << "x";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
                if (j == width - 1)
                    cout << "#"; // lineright
            }
            cout << endl;
        }
        for (int i = 0; i < width + 1; i++)
            cout << "# "; // linebot
        cout << endl << endl;
        cout << "Score: " << score;
    }
    void Input()
    {
        int q = 1;
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'q':
                q = 0;
                if (q == 0)
                    gameOver = true;
                break;
            default:
                break;
            }
        }
    }
    void Control()
    {
        switch (dir)
        {
        case LEFT:
            snake.x--;
            break;
        case UP:
            snake.y--;
            break;
        case DOWN:
            snake.y++;
            break;
        case RIGHT:
            snake.x++;
            break;
        default:
            break;
        }
        Tail[0].x = snake.x;
        Tail[0].y = snake.y;
        for (int i = nTail; i > 0; i--)
        {
            Tail[i] = Tail[i-1];
        }
        if (snake.x > width || snake.x < 0 || snake.y > height || snake.y < 0)
        {
            gameOver = true;
        }
        for (int i = 2; i < nTail; i++)
        {
            if (snake.x == Tail[i].x && snake.y == Tail[i].y)
            {
                gameOver = true;
            }
        }
        if (snake.x == bom.x && snake.y == bom.y)
        {
            score++;
            bom.x = rand() % width;
            bom.y = rand() % height;
            nTail++;
        }
    }
    void play()
    {
        Snake();
        Setup();
        while (!gameOver)
        {
            Input();
            Control();
            Draw();
            Sleep(300);
        }
    }
};

int main()
{
    Snake ran;
    ran.play();
    return 0;
}