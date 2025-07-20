#pragma once
#ifndef GAME_H
#define GAME_H

#define WIDTH 1280
#define HEIGTH 720
#define GRAVITY 650

#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <thread>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"

class WindowRenderer;
class InputManager;
class PhysicsRenderer;
class LevelManager;

class Game {
    public: 
        Game( const char* GameTitle ): WindowTitle(GameTitle) {};
        ~Game() {};
        
        bool Running = false;
        const char* WindowTitle;

        void Start( const SDL_WindowFlags windowFlag = SDL_WINDOW_ALLOW_HIGHDPI );   
        void Stop();
        void GetWindowSize(int &w, int& h) { 
            w = WIDTH;
            h = HEIGTH;
        }

        SDL_Window* GetWindow() {
            return Window;
        }

        Vec2f MidScreenLoc { WIDTH / 2, HEIGTH / 2 };
        Vec2f GroundScreenLoc = MidScreenLoc - Vec2f {300, -160};

        WindowRenderer* AppRenderer;
        InputManager* _InputManager;
        LevelManager* levelManager;

        float DeltaTime = 0.0f;
    private:
        const int WindowWeigth = WIDTH;
        const int WindowHeigth = HEIGTH;

        void Run();

        SDL_Window* Window;
        SDL_Event AppEventPoll;
};

#endif