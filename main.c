#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 25
#define HEIGHT 25

int x, y, fruitX, fruitY, score, gameover;
int tailX[100], tailY[100];
int nTail;
typedef enum
{
    Top,
    Down,
    Left,
    Right,
    Stop = 0
} MDir;
MDir dir;

void Draw();
void Input();
void Logic();

int main(void)
{
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    score = 0;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    dir = Stop;

    while(!gameover)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }

    return 0;
}

void Draw()
{
    system("cls");

    for(int i = 0; i < WIDTH + 2; i++) 
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else 
            {
                int printTail = 0;
                for (int k = 0; k < nTail; k++) 
                {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        printTail = 1;
                    }
                }

                if (!printTail)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }

        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("score: %d\n", score);
}

void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                dir = Left;
                break;
            case 'w':
                dir = Top;
                break;
            case 'd':
                dir = Right;
                break;
            case 's':
                dir = Down;
                break;
            case 27:
                gameover = 1;
            default:
                break;
        }
    }
}

void Logic()
{
    int prev2X, prev2Y;
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) 
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) 
    {
        case Left:
            x--;
            break;
        case Right:
            x++;
            break;
        case Top:
            y--;
            break;
        case Down:
            y++;
            break;
        default:
            break;
    }

    if (x >= WIDTH)
        x = 0;
    else if (x < 0)
        x = WIDTH - 1;

    if (y >= HEIGHT)
        y = 0;
    else if (y < 0)
        y = HEIGHT - 1;

    if (x == fruitX && y == fruitY) 
    {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}