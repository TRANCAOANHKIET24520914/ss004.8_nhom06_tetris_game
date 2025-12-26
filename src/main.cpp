#include "Game.h"
#include "InputHandler.h"

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
