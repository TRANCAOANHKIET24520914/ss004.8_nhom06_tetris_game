#include "Game.h"
#include "InputHandler.h"
#include <windows.h>

int main() {
    system("cls");
    SetConsoleOutputCP(437);

    Game game;
    InputHandler input;

    while (true) {
        input.process(game);
        game.update();
        Sleep(10);
    }

    return 0;
}
#include "Game.h"
#include "InputHandler.h"
#include <windows.h>
#include <cstdlib>

int main() {
    system("cls");     // xoa man hinh (Windows)
    SetConsoleOutputCP(437); // set ma ASCII

    Game game;
    InputHandler input;

    while (true) {
        input.process(game);
        game.update();
        Sleep(10);    // Delay 10ms
    }

    return 0;
}

