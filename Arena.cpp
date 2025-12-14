#include "Arena.h"

// Constructor: Khởi tạo board với tường bao quanh
Arena::Arena()
{
    for (int i = 0; i < A_HEIGHT; i++)
    {
        for (int j = 0; j < A_WIDTH; j++)
        {
            if (i == A_HEIGHT - 1 || j == 0 || j == A_WIDTH - 1)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
}

// Kiểm tra va chạm
bool Arena::isValidPosition(const char tetromino[4][4], int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino[i][j] != ' ')
            {
                int px = x + j;
                int py = y + i;

                if (px < 0 || px >= A_WIDTH || py >= A_HEIGHT)
                {
                    return false;
                }

                if (py >= 0 && board[py][px] != ' ')
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Arena::lockPiece(const char tetromino[4][4], int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetromino[i][j] != 0)
            {
                if (y + i >= 0 && y + i < A_HEIGHT - 1 && x + j > 0 && x + j < A_WIDTH - 1)
                {
                    board[y + i][x + j] = tetromino[i][j];
                }
            }
        }
    }
}

int Arena::clearLines()
{
    int linesCleared = 0;

    for (int i = A_HEIGHT - 2; i > 0; i--)
    {
        bool isFull = true;

        for (int j = 1; j < A_WIDTH - 1; j++)
        {
            if (board[i][j] == ' ')
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            linesCleared++;

            for (int k = i; k > 0; k--)
            {
                for (int col = 1; col < A_WIDTH - 1; col++)
                {
                    board[k][col] = board[k - 1][col];
                }
            }

            for (int col = 1; col < A_WIDTH - 1; col++)
            {
                board[0][col] = ' ';
            }

            i++;
        }
    }
    return linesCleared;
}

char Arena::getCell(int y, int x) const
{
    if (x < 0 || x >= A_WIDTH || y < 0 || y >= A_HEIGHT)
        return '#';
    return board[y][x];
}
