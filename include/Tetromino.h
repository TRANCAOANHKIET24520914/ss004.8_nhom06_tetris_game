#ifndef TETROMINO_H
#define TETROMINO_H

#include <cstdlib>

#define T_WIDTH 4
#define T_HEIGHT 4

class Tetromino
{
public:
    int type;
    int rotation;
    static const int shapes[7][16];

    Tetromino();
    void rotateRight();
    int getCell(int x, int y) const;
};

#endif
