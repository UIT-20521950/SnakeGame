#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
const int width = 20;
const int height = 20;
bool gameOver = false, game = false;
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
    string head = "X";
    string body = "x";
    string bom_game = "@";
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    Snake()
    {
        nTail = 2;
        Tail[0].x = snake.x;
        Tail[0].y = snake.y;
        Tail[1].x = snake.x + 1;
        Tail[1].y = snake.y + 1;
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
    void Draw(string head, string body, string bom_game)
    {
        system("cls");
        for (int i = 0; i < width + 1; i++)
        {
            cout << "# "; // linetop
        }

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
                    cout << head; // sanke
                else if (i == bom.y && j == bom.x)
                {
                        cout << bom_game;
                }

                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (Tail[k].x == j && Tail[k].y == i)
                        {
                            cout << body;
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
        cout << endl
             << endl;
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
            Tail[i] = Tail[i - 1];
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
            bom.x = rand() % (width - 1) + 1;
            bom.y = rand() % (height - 1) + 1;
            nTail++;
        }
    }
    void skin()
    {
        int c;
        cout << "\n========================\n";
        cout << "\t\t1. Snake: xxX  - 0";
        cout << "\n\t\t2. Snake: oo0  - $";
        cout << "\n\t\t3. Snake default";
        cout << "\n========================\n";
        cout << "\n Selcet your choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
        {
            head = "\x1B[31mX\033[0m";
            body = "\x1B[33mx\033[0m";
            bom_game = "\x1B[93m0\033[0m";
        }
        break;
        case 2:
        {
            head = "\x1B[31m0\033[0m";
            body = "\x1B[33mo\033[0m";
            bom_game = "\x1B[93m$\033[0m";
        }
        break;
        default:
            break;
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
            Draw(head, body, bom_game);
            Sleep(300);
        }
        system("cls");
        cout << "\n========================\n";
        cout << "\n     \x1B[36mHight score: \033[0m" << score << "\n";
        cout << "\n========================\n";
    }
};
void menu(Snake a)
{
    int c;
    for (int i = 0; i < 25; i++)
    {
        cout << "- ";
    }
    cout << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "\t";
    }
    cout << "Menu Game Snake \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "\t";
    }
    cout << "1. Select 1 to Start Game\n";
    for (int i = 0; i < 2; i++)
    {
        cout << "\t";
    }
    cout << "2. Put any key to Quit Game\n";
    for (int i = 0; i < 25; i++)
    {
        cout << "- ";
    }
    cout << "\n Selcet your choice: ";
    cin >> c;
    switch (c)
    {
    case 1:
        a.skin();
        a.play();
        break;
    default:
        c = 2;
        if (c == 2)
            game = true;
        ;
        break;
    }
}
int main()
{
    Snake ran;
    while (!game)
    {
        menu(ran);
    }
    return 0;
}