#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "Arena.h"

using namespace std;
#define H 20
#define W 15

Arena arena;

char blocks[7][4][4] = {
    {{' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}}, // I
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}}, // O
    {{' ', ' ', ' ', ' '}, {' ', 'T', ' ', ' '}, {'T', 'T', 'T', ' '}, {' ', ' ', ' ', ' '}}, // T
    {{' ', ' ', ' ', ' '}, {' ', 'S', 'S', ' '}, {'S', 'S', ' ', ' '}, {' ', ' ', ' ', ' '}}, // S
    {{' ', ' ', ' ', ' '}, {'Z', 'Z', ' ', ' '}, {' ', 'Z', 'Z', ' '}, {' ', ' ', ' ', ' '}}, // Z
    {{' ', ' ', ' ', ' '}, {'J', ' ', ' ', ' '}, {'J', 'J', 'J', ' '}, {' ', ' ', ' ', ' '}}, // J
    {{' ', ' ', ' ', ' '}, {' ', ' ', 'L', ' '}, {'L', 'L', 'L', ' '}, {' ', ' ', ' ', ' '}}  // L
};
int x = 4, y = 0, b = 1;
void gotoxy(int x, int y)
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock()
{
    // for (int i = 0 ; i < 4 ; i++)
    //     for (int j = 0 ; j < 4 ; j++)
    //         if (blocks[b][i][j] != ' ' && y+j < H)
    //             board[y+i][x+j] = ' ';
}
void block2Board()
{
    arena.lockPiece(blocks[b], x, y);
}
void initBoard()
{
}
void draw()
{
    gotoxy(0, 0);
    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
        {
            // 1. Lấy dữ liệu nền từ Arena
            char pixel = arena.getCell(i, j);

            // 2. Nếu vị trí này trùng với khối đang rơi, vẽ đè lên
            if (i >= y && i < y + 4 && j >= x && j < x + 4)
            {
                if (blocks[b][i - y][j - x] != ' ')
                {
                    pixel = blocks[b][i - y][j - x];
                }
            }
            cout << pixel;
        }
}

bool canMove(int dx, int dy)
{
    return arena.isValidPosition(blocks[b], x + dx, y + dy);
}

void removeLine()
{
    arena.clearLines();
}

void rotateBlock()
{
    char rotated[4][4];

    // Xoay khối:
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[i][j] = blocks[b][3 - j][i];

    
 // Kiểm tra có xoay được không
    if (arena.isValidPosition(rotated, x, y))
    {
        // Ghi đè lại khối hiện tại
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                blocks[b][i][j] = rotated[i][j];
    }
}


int main()
{
    srand(time(0));
    b = rand() % 7;

    // Ẩn con trỏ chuột
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);

    system("cls");
    initBoard();

    while (1)
    {
        boardDelBlock();
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1, 0))
                x--;
            if (c == 'd' && canMove(1, 0))
                x++;
            if (c == 'x' && canMove(0, 1))
                y++;
            if (c == 'w')
                rotateBlock();
            if (c == 'q')
                break;
        }

        if (canMove(0, 1))
            y++;
        else
        {
            block2Board();
            removeLine();
            x = 4;
            y = 0;
            b = rand() % 7;

            if (!canMove(0, 0))
            {
                system("cls");
                cout << "GAME OVER!";
                break;
            }
        }

        draw();
        Sleep(200);
    }
    return 0;
}
