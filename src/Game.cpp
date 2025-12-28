#include "Game.h"
#include <windows.h>
#include <ctime>
#include <iostream>

using namespace std;

Game::Game() : gameOverDrawn(false) // KHỞI TẠO
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
    gameOverDrawn = false;  // RESET BIẾN NÀY

    // XÓA MÀN HÌNH KHI RESET
    system("cls");
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
    case 80: // Xuong - THAY ĐỔI: Rơi nhanh hơn (3 ô mỗi lần)
        for (int i = 0; i < 3; i++) {  // Thay vì chỉ 1 ô, rơi 3 ô mỗi lần nhấn
            if (!arena.checkCollision(current, posX, posY + 1))
                posY++;
            else
                break;
        }
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

        // THAY ĐỔI: Kiểm tra nếu arena đầy sau khi merge
        bool arenaFull = false;
        for (int x = 0; x < A_WIDTH; x++) {
            if (arena.getCell(x, 0) == 1) {  // Kiểm tra hàng trên cùng
                arenaFull = true;
                gameOver = true;
                break;
            }
        }

        if (!arenaFull) {
            spawnNew();
        }
        break;
    }
    }
}

void Game::update()
{
    // XỬ LÝ PAUSE TRƯỚC TIÊN
    static bool pauseDrawn = false;
    static bool wasPaused = false;

    if (paused) {
        if (!pauseDrawn) {
            // Chỉ xóa và vẽ thông báo pause một lần
            system("cls");
            cout << "================================\n";
            cout << "           GAME PAUSED!\n";
            cout << "================================\n";
            cout << "Press 'P' to resume\n";
            pauseDrawn = true;
        }
        return;
    }

    // Reset biến pauseDrawn khi không còn pause
    if (wasPaused) {
        // KHÔNG gọi system("cls") ở đây nữa
        // Renderer sẽ tự xóa và vẽ lại từ đầu
        wasPaused = false;
        pauseDrawn = false;
    }

    wasPaused = paused;

    // PHẦN CÒN LẠI GIỮ NGUYÊN (game over logic và update bình thường)...
    if (gameOver) {
        if (!gameOverDrawn) {
            system("cls");
            cout << "==================================\n";
            cout << "           GAME OVER!\n";
            cout << "        Final Score: " << score << "\n";
            cout << "==================================\n";
            cout << "Press 'R' to restart or 'Q' to quit\n";
            gameOverDrawn = true;
        }
        return;
    }

    static DWORD lastTick = GetTickCount();
    DWORD now = GetTickCount();

    if (now - lastTick >= 500)
    {
        if (arena.checkCollision(current, posX, posY + 1))
        {
            arena.merge(current, posX, posY);
            score += arena.clearLines() * 100;

            bool arenaFull = false;
            for (int x = 0; x < A_WIDTH; x++) {
                if (arena.getCell(x, 0) == 1) {
                    arenaFull = true;
                    gameOver = true;
                    break;
                }
            }

            if (!arenaFull) {
                spawnNew();
            }
        }
        else
            posY++;

        lastTick = now;
    }

    // Vẽ arena bình thường
    renderer.draw(arena, current, posX, posY, score);
}

void Game::start()
{
    while (!gameOver)
    {
        update();
        Sleep(10);
    }

    // Đoạn này chỉ chạy khi game over từ hàm start() cũ
    // Nhưng chúng ta đã xử lý trong update() rồi
    system("cls");
    printf("GAME OVER\nScore: %d\n", score);
}
