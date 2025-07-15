#ifndef GAME_H
#define GAME_H

#define WIDTH 1920
#define HEIGTH 1080

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "WindowRenderer.h"
#include "Entity.h"

struct EntityMetaData {
    Vec2f position;
    const char* textureLoc;
};

class Game {
    public: 
        Game( const char* GameTitle ): WindowTitle(GameTitle) {};

        bool running = false;
        const char* WindowTitle;

        void Start( SDL_WindowFlags windowFlag = SDL_WINDOW_MOUSE_FOCUS );   
        void Stop();
        
        std::vector<EntityMetaData> demoMap =
        {
            EntityMetaData {Vec2f(0, 0), "src/art/background/day_background.png"},
        };

    private:
        int windowWidth = WIDTH;
        int windowHeigth = HEIGTH;

        void Run();

        SDL_Window* window;
        SDL_Event AppEventPoll;

        WindowRenderer* AppRenderer;
};

#endif