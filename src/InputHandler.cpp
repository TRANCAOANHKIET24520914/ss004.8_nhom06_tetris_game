#include "InputHandler.h"
#include <conio.h>

void InputHandler::process(Game &game)
{
    if (!_kbhit())
        return;

    int key = _getch();
    game.handleInput(key);
}
