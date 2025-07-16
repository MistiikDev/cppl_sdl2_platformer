#include <iostream>
#include "WindowRenderer.h"
#include "Entity.h"

WindowRenderer::WindowRenderer(SDL_Window* window, SDL_RendererFlags renderFlag) {
    this->activeRenderer = SDL_CreateRenderer(window, -1, renderFlag |  SDL_RENDERER_PRESENTVSYNC);
    this->entityManager = new EntityManager(this->activeRenderer);
}

void WindowRenderer::Display() {
    SDL_RenderPresent(this->activeRenderer);
}

void WindowRenderer::Render() {
    for (Entity* e : (this->entityManager->GetActiveEntities())) {
        SDL_Rect sourceRect, destRect;
        // Source, what pixels are we drawing?
        sourceRect.x = e->GetEntityRenderingBox().x;
        sourceRect.y = e->GetEntityRenderingBox().y;
        sourceRect.w = e->GetEntityRenderingBox().w;
        sourceRect.h = e->GetEntityRenderingBox().h;

        // Destination, where are we drawing on the screen?
        destRect.x = static_cast<int>(e->GetPosition().x);
        destRect.y = static_cast<int>(e->GetPosition().y);
        destRect.w = e->GetEntityRenderingBox().w;
        destRect.h = e->GetEntityRenderingBox().h;

        SDL_RenderCopy(this->activeRenderer, e->GetTexture(), &sourceRect, &destRect);
    }
}

void WindowRenderer::ClearViewport() {
    SDL_RenderClear(this->activeRenderer);
}

void WindowRenderer::Quit() {
    std::cout << "Destroying RENDERER." << '\n';

    SDL_DestroyRenderer(this->activeRenderer);
}