#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include <iostream>
#include "Arena.h" // Cần truy cập Arena để lấy dữ liệu bản đồ

class Renderer {
private:
    HANDLE hConsole;

    // Hàm di chuyển con trỏ console (thay thế cho việc xóa toàn màn hình)
    void gotoxy(int x, int y);

    // Hàm thiết lập màu sắc (tùy chọn, để mặc định trắng đen cho đơn giản)
    void setColor(int color);

public:
    Renderer();
    
    // Thiết lập ban đầu (ẩn con trỏ chuột)
    void init();

    // Hàm vẽ chính: Kết hợp Arena và Khối đang rơi
    void render(const Arena& arena, const char currentBlock[4][4], int x, int y, int score);

    // Màn hình Game Over
    void renderGameOver(int finalScore);
};

#endif