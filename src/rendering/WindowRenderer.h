#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "EntityManager.h"

class Entity;
class WindowRenderer {
    public:
        WindowRenderer(SDL_Window* window, SDL_RendererFlags renderFlag, int Width, int Height);

        int logicalWidth;
        int logicalHeigth;

        SDL_Renderer* GetRenderer();

        void Display();
        void Render(std::vector<std::shared_ptr<Entity>>& renderObjects);
        void ClearViewport();

        void SetViewportSize(int newWidth, int newHeight);

        void Quit();
    private:
        SDL_Renderer* activeRenderer;
};

#endif