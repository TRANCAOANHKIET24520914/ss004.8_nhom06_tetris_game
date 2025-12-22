#include "Tetromino.h"

const int Tetromino::shapes[7][16] = {
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // I
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // O
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0}, // S
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // Z
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, // T
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, // L
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0}  // J
};

Tetromino::Tetromino()
{
    type = rand() % 7;
    rotation = 0;
}

void Tetromino::rotateRight()
{
    rotation = (rotation + 1) % 4;
}

int Tetromino::getCell(int x, int y) const
{
    int idx = 0;
    switch (rotation)
    {
    case 0:
        idx = y * 4 + x;
        break;
    case 1:
        idx = 12 + y - (x * 4);
        break;
    case 2:
        idx = 15 - (y * 4) - x;
        break;
    case 3:
        idx = 3 - y + (x * 4);
        break;
    }
    return shapes[type][idx];
}
