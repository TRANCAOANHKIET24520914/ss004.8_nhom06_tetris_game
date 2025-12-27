#ifndef RENDERER_H
#define RENDERER_H

#include "Arena.h"
#include "Tetromino.h"
#include <string>

class Renderer {
public:
    void draw(const Arena&, const Tetromino&, int posX, int posY, int score);
};

#endif

