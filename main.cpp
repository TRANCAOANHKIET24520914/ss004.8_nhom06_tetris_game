#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "../include/Arena.h"
#include "../include/Renderer.h" // Thêm thư viện 
#include "../include/Game.h"

using namespace std;
#define H 20
#define W 15

Arena arena;
Renderer renderer; // 1. Khởi tạo đối tượng Renderer 

char blocks[7][4][4] = {
    {{' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}}, // I
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}}, // O
    {{' ', ' ', ' ', ' '}, {' ', 'T', ' ', ' '}, {'T', 'T', 'T', ' '}, {' ', ' ', ' ', ' '}}, // T
    {{' ', ' ', ' ', ' '}, {' ', 'S', 'S', ' '}, {'S', 'S', ' ', ' '}, {' ', ' ', ' ', ' '}}, // S
    {{' ', ' ', ' ', ' '}, {'Z', 'Z', ' ', ' '}, {' ', 'Z', 'Z', ' '}, {' ', ' ', ' ', ' '}}, // Z
    {{' ', ' ', ' ', ' '}, {'J', ' ', ' ', ' '}, {'J', 'J', 'J', ' '}, {' ', ' ', ' ', ' '}}, // J
    {{' ', ' ', ' ', ' '}, {' ', ' ', 'L', ' '}, {'L', 'L', 'L', ' '}, {' ', ' ', ' ', ' '}}  // L
};

int x = 4, y = 0, b = 1;
int score = 0; // Thêm biến điểm số để Renderer hiển thị

// --- ĐÃ XÓA HÀM GOTOXY VÀ DRAW CŨ VÌ ĐÃ CÓ TRONG RENDERER ---

void block2Board() {
    arena.lockPiece(blocks[b], x, y);
}

bool canMove(int dx, int dy) {
    return arena.isValidPosition(blocks[b], x + dx, y + dy);
}

void removeLine() {
    // Giả sử mỗi hàng biến mất được 100 điểm
    int linesCleared = arena.clearLines(); 
    score += linesCleared * 100;
}

void rotateBlock() {
    char rotated[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[i][j] = blocks[b][3 - j][i];

    if (arena.isValidPosition(rotated, x, y)) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                blocks[b][i][j] = rotated[i][j];
    }
}

int main() {
    srand(time(0));
    b = rand() % 7;

    // 2. Sử dụng hàm init để ẩn con trỏ chuột
    renderer.init();

    system("cls");

    while (1) {
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x' && canMove(0, 1)) y++;
            if (c == 'w' || c == ' ') rotateBlock(); // Space để xoay như trong Renderer mô tả
            if (c == 'q') break;
        }

        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();
            x = 4; y = 0;
            b = rand() % 7;

            if (!canMove(0, 0)) {
                // 3. Sử dụng màn hình Game Over 
                renderer.renderGameOver(score);
                break;
            }
        }

        // 4. Sử dụng hàm render chính thay cho hàm draw() cũ
        renderer.render(arena, blocks[b], x, y, score);
        
        Sleep(200);
    }
    return 0;
}
