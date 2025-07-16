#pragma once
#ifndef GAME_H
#define GAME_H

#define WIDTH 1280
#define HEIGTH 720

#define GRAVITY 9.81

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WindowRenderer;
class InputManager;

#include "Vec2f.h"

struct EntityMetaData {
    Vec2f position;
    const char* textureLoc;
};

class Game {
    public: 
        Game( const char* GameTitle ): WindowTitle(GameTitle) {};
        ~Game() {

        }
        
        bool running = false;
        double deltaTime = 0.0f;
        const char* WindowTitle;

        void Start( SDL_WindowFlags windowFlag = SDL_WINDOW_MOUSE_FOCUS );   
        void Stop();
        
        void GetWindowSize(int &w, int& h) { 
            w = WIDTH;
            h = HEIGTH;
        }

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

        InputManager* inputManager;
};

#endif