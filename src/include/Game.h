#pragma once
#ifndef GAME_H
#define GAME_H

#define WIDTH 1280
#define HEIGTH 720
#define GRAVITY 450

#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WindowRenderer;
class InputManager;
class PhysicsRenderer;

#include "Vec2f.h"

class Player;
class Entity;

struct EntityMetaData {
    const Vec2f position;
    const char* textureLoc;
    const bool b_isPlayer;

    double mass;
};

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

        Vec2f MidScreenLoc { WIDTH / 2, HEIGTH / 2 };
        Vec2f GroundScreenLoc = MidScreenLoc - Vec2f {300, -160};

        float DeltaTime = 0.0f;
    private:
        const int WindowWeigth = WIDTH;
        const int WindowHeigth = HEIGTH;

        void Run();

        SDL_Window* Window;
        SDL_Event AppEventPoll;

        WindowRenderer* AppRenderer;
        InputManager* _InputManager;
};

#endif