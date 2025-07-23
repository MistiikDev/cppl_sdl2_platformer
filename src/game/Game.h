#pragma once
#ifndef GAME_H
#define GAME_H

#define WIDTH 1280
#define HEIGTH 720

#define LOGICAL_WIDTH 1920
#define LOGICAL_HEIGTH 1080

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
class EntityManager;

class Game {
    public: 
        Game( const char* GameTitle ): WindowTitle(GameTitle) {};
        ~Game() {};
        
        bool Running = false;
        const char* WindowTitle;
        float DeltaTime = 0.0f;
        
        void Start( const SDL_WindowFlags windowFlag = SDL_WINDOW_ALLOW_HIGHDPI );   
        void Stop();
        void GetLogicalWindowSize(int &w, int& h);

        SDL_Window* GetWindow() {
            return Window;
        }

        Vec2f MidScreenLoc { WIDTH / 2, HEIGTH / 2 };
        Vec2f GroundScreenLoc = MidScreenLoc - Vec2f {300, -160};

        WindowRenderer* AppRenderer;
        InputManager* _InputManager;
        LevelManager* levelManager;
        EntityManager* entityManager;
    private:
        void Run();

        SDL_Window* Window;
        SDL_Event AppEventPoll;
};

#endif