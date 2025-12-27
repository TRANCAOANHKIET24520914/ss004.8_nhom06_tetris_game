#ifndef ARENA_H
#define ARENA_H

#include "Tetromino.h"

#define A_WIDTH 15
#define A_HEIGHT 20

class Arena
{
private:
    int grid[A_HEIGHT][A_WIDTH];

public:
    Arena();
    void reset();
    bool checkCollision(const Tetromino &, int posX, int posY) const;
    void merge(const Tetromino &, int posX, int posY);
    int clearLines();
    int getCell(int x, int y) const { return grid[y][x]; }
};

#endif