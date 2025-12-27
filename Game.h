#ifndef GAME_H
#define GAME_H

#include "Arena.h"
#include "Tetromino.h"
#include "Renderer.h"

class Game
{
private:
    Arena arena;
    Tetromino current;
    Renderer renderer;

    int posX, posY;
    int score;
    bool gameOver;
    bool paused;

public:
    Game();
    void start();
    void handleInput(int key);
    void spawnNew();
    void update();
    void reset();
};

#endif
