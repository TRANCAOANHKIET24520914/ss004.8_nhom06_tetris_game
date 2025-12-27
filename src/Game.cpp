#include "Game.h"
#include <windows.h>
#include <ctime>

Game::Game()
{
    srand(time(NULL));      // Khoi tao khoi ngau nhien de random khoi
    reset();
}

void Game::reset() {
    arena.reset();          // Reset board
    spawnNew();             // Sinh khoi moi
    score = 0;              // Diem
    gameOver = false;       // Cho phep game chay
    paused = false;
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
    // Thoat game
    if (key == 'q' || key == 'Q' || key == 27) { // ESC
        exit(0);
    }

    // Pause / Resume
    if (key == 'p' || key == 'P') {
        paused = !paused;
        return;
    }

    // Restart
    if (key == 'r' || key == 'R') {
        reset();
        return;
    }

    if (paused || gameOver) return;

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
    case 72: // ⬆
        case 'x':
        case 'X': {   // Xoay khoi
            current.rotateRight();
            if (arena.checkCollision(current, posX, posY)) {
                // undo rotate
                current.rotateRight();
                current.rotateRight();
                current.rotateRight();
            }
            break;
        }

        case 32: { // SPACE -> hard drop
            while (!arena.checkCollision(current, posX, posY + 1))
                posY++;

            arena.merge(current, posX, posY);
            score += arena.clearLines() * 100;
            spawnNew();
            break;
        }
        break;
    case 32: // space -> xoay        
        current.rotateRight();
        if (arena.checkCollision(current, posX, posY))
            current.rotateRight(), current.rotateRight(), current.rotateRight();
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
