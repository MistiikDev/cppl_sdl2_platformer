#include "Entity.h"
#include "WindowRenderer.h"

WindowRenderer::WindowRenderer(SDL_Window* window, SDL_RendererFlags renderFlag) {
    this->activeRenderer = SDL_CreateRenderer(window, -1, renderFlag |  SDL_RENDERER_PRESENTVSYNC);
    this->entityManager = new EntityManager(this->activeRenderer);
}

void WindowRenderer::Display() {
    SDL_RenderPresent(this->activeRenderer);
}

void WindowRenderer::Render() {
    std::vector<Entity*> activeEntities = this->entityManager->GetActiveEntities();

    // Sort list based off of render layers.
    std::sort(activeEntities.begin(), activeEntities.end(), 
        [](Entity* a, Entity* b) { 
            return a->RenderingLayer < b->RenderingLayer; 
        }
    );

    for (Entity* e : activeEntities) {
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