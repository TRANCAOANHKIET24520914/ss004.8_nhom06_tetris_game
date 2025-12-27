#include "Arena.h"
#include <cstring>

Arena::Arena()
{
    reset();
}

void Arena::reset()
{
    memset(grid, 0, sizeof(grid));
}

bool Arena::checkCollision(const Tetromino &t, int posX, int posY) const
{
    for (int y = 0; y < T_HEIGHT; y++)
    {
        for (int x = 0; x < T_WIDTH; x++)
        {
            if (t.getCell(x, y) != 1)
                continue;

            int ax = posX + x;
            int ay = posY + y;

            if (ax < 0 || ax >= A_WIDTH || ay >= A_HEIGHT)
                return true;

            if (ay >= 0 && grid[ay][ax] == 1)
                return true;
        }
    }
    return false;
}

void Arena::merge(const Tetromino &t, int posX, int posY)
{
    for (int y = 0; y < T_HEIGHT; y++)
    {
        for (int x = 0; x < T_WIDTH; x++)
        {
            if (t.getCell(x, y) != 1)
                continue;
            int ax = posX + x;
            int ay = posY + y;

            if (ay >= 0 && ay < A_HEIGHT && ax >= 0 && ax < A_WIDTH)
                grid[ay][ax] = 1;
        }
    }
}

int Arena::clearLines()
{
    int cleared = 0;

    for (int y = A_HEIGHT - 1; y >= 0; y--)
    {
        bool full = true;

        for (int x = 0; x < A_WIDTH; x++)
        {
            if (grid[y][x] == 0)
            {
                full = false;
                break;
            }
        }

        if (!full)
            continue;

        cleared++;

        for (int yy = y; yy > 0; yy--)
            memcpy(grid[yy], grid[yy - 1], A_WIDTH * sizeof(int));

        memset(grid[0], 0, A_WIDTH * sizeof(int));
        y++;
    }

    return cleared;
}