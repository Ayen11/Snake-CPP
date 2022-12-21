#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; 
eDirection dir;

bool isBoundless = true; //change boundless here


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); //clears terminal
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            if ( j == 0)
                cout << "#";
            
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";

            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {   
                    
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }

                }
                if (!print)
                    cout << " ";
            }
            if (j == width -1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input(){
    if (_kbhit()){
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;    
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

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
    case LEFT:
        if (dir != RIGHT)
        {
            x--;            
        }
        break;

    case RIGHT:
        if (dir != LEFT)
        {
            x++;
        }
        break;

    case UP:
        if (dir != DOWN)
        {
            y--;
        }
        break;

    case DOWN:
        if (dir != UP)
        {
            y++;
        }
        break;  

    default:
        break;
    }


    for (int i = 0; i < nTail; i++) //checks for self collision
    {
        if(tailX[i] == x && tailY[i] == y)
        gameOver = true;
    }



    switch (isBoundless)
    {
    case true: //teleports player to other side of bounds on collision
        if (x >= width) x = 0; else if (x < 0) x = width - 1; 
        if (y >= height) y = 0; else if (y < 0) y = height - 1;
        break;
    
    case false: //checks for collision with boundries
        if (x > width || x < 0 || y > height|| y < 0) 
        {
        gameOver = true;
        }        

    default:
        break;
    }



    if (x == fruitX && y == fruitY) //checks for collision with fruit
    {
    score += 10;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(70);
    }
    
    return 0;
} 