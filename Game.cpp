#include "Game.h"
#include <windows.h>
#include <ctime>

Game::Game()
{
    srand(time(NULL));      // Khoi tao khoi ngau nhien de random khoi
    arena.reset();          // Reset board
    spawnNew();             // Sinh khoi moi
    score = 0;              // Diem
    gameOver = false;       // Cho phep game chay
}

void Game::spawnNew()
{
    current = Tetromino();          // Tao khoi teromino
    posX = A_WIDTH / 2 - 2;         // Dat khoi o giua
    posY = 0;                       // Dat khoi tren cung

    if (arena.checkCollision(current, posX, posY))      
    {
        gameOver = true;            // Ket thuc tro choi neu khoi da day
    }
}

void Game::handleInput(int key)     // Khong va cham thi moi cho di chuyen
{
    switch (key)
    {
    case 75: // Trai
        if (!arena.checkCollision(current, posX - 1, posY))
            posX--;
        break;
    case 77: // Phai
        if (!arena.checkCollision(current, posX + 1, posY))
            posX++;
        break;
    case 80: // Xuong
        if (!arena.checkCollision(current, posX, posY + 1))
            posY++;
        break;
    case 32: // space -> xoay
        if (!arena.checkCollision(current, posX, posY))
            current.rotateRight();
        break;
    }
}

void Game::update()
{
    static DWORD lastTick = GetTickCount();     // Thoi diem truoc
    DWORD now = GetTickCount();                 // Thoi diem hien tai

    if (now - lastTick >= 500)                  // Cu 500ms thi roi xuonh 1 o
    {
        if (arena.checkCollision(current, posX, posY + 1))      // Neu ko xuong dc nx
        {
            arena.merge(current, posX, posY);                   // Gan khoi vao board
            score += arena.clearLines() * 100;                  // Dong day thi xoa va tang diem
            spawnNew();                                         // Sinh khoi moi
        }
        else
            posY++;                                             // tiep tuc roi xuong

        lastTick = now;                                         // Cap nhat lastTick
    }

    renderer.draw(arena, current, posX, posY, score);           // Ve lai board
}

void Game::start()
{
    while (!gameOver)
    {
        update();
        Sleep(10);
    }

    system("cls");
    printf("GAME OVER\nScore: %d\n", score);
}
