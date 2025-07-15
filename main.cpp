#include <iostream>
#include "Game.h"

int main(int argc, char* args[]) {
    Game CoreGame {"Platformer"};

    CoreGame.Start( SDL_WINDOW_MOUSE_FOCUS );
    
    return 0;
}