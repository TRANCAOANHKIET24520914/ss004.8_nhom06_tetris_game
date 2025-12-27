#include "Renderer.h"
#include <iostream>

using namespace std;

// Ve toan bo man hình game Tetris ra console

void Renderer::draw(const Arena &arena,
                    const Tetromino &t,
                    int posX,
                    int posY,
                    int score)
{
    // an con tro chuot trong console
    cout << "\e[?25l";

    // Đua con tro ve goc tren ben trai man hinh
    cout << "\e[H";

    // ====== Ve vien tren ======
    cout << "\xDA"; // Goc tren trai
    for (int i = 0; i < A_WIDTH * 2; i++)
        cout << "\xC4"; // Đưong ngang
    cout << "\xBF\n"; // Goc tren phai

    // ====== Ve tung dong trong Arena ======
    for (int y = 0; y < A_HEIGHT; y++)
    {
        cout << "\xB3"; // Vien trai

        for (int x = 0; x < A_WIDTH; x++)
        {
            bool falling = false;


            int lx = x - posX;
            int ly = y - posY;

            if (lx >= 0 && lx < 4 && ly >= 0 && ly < 4)
            {
                if (t.getCell(lx, ly) == 1)
                    falling = true;
            }


            if (arena.getCell(x, y) == 1 || falling)
                cout << "\xDB\xDB"; // Ve khoi đac
            else
                cout << ". ";       // O trong
        }

        cout << "\xB3\n"; // Vien phai
    }

    // ====== Ve Vien Duoi ======
    cout << "\xC0"; // Goc duoi trai
    for (int i = 0; i < A_WIDTH * 2; i++)
        cout << "\xC4";
    cout << "\xD9\n"; // Goc dưoi phai

    // ====== Hien thi diem ======
    cout << "Score: " << score << "\n\n";
}
