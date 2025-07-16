#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "EntityManager.h"

class WindowRenderer{
    public:
        WindowRenderer(SDL_Window* window, SDL_RendererFlags renderFlag);

        EntityManager* entityManager;

        void Display();
        void Render();
        void ClearViewport();

        void Quit();
    private:
        SDL_Renderer* activeRenderer;
};

#endif