#include "Entity.h"
#include "Camera.h"

#include "WindowRenderer.h"

WindowRenderer::WindowRenderer(SDL_Window* window, SDL_RendererFlags renderFlag, int Width, int Height) {
    this->activeRenderer = SDL_CreateRenderer(window, -1, renderFlag |  SDL_RENDERER_PRESENTVSYNC);
    
    SDL_SetWindowResizable( window, SDL_TRUE );
    SDL_RenderSetLogicalSize(this->activeRenderer, Width, Height);

    this->logicalWidth = Width;
    this->logicalHeigth = Height;

    std::cout << "RENDERER : Loading Window Renderer" << std::endl;
}

SDL_Renderer* WindowRenderer::GetRenderer() {
    return this->activeRenderer;
}

void WindowRenderer::SetViewportSize(int newWidth, int newHeight) {
    SDL_RenderSetViewport(this->activeRenderer, nullptr);
}

void WindowRenderer::Display() {
    SDL_RenderPresent(this->activeRenderer);
}

void WindowRenderer::Render(std::vector<std::shared_ptr<Entity>>& activeEntities, Camera* camera) {

    // Sort list based off of render layers.
    std::sort(activeEntities.begin(), activeEntities.end(), 
        [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
            return a->RenderingLayer < b->RenderingLayer;
        }
    );

     for (const auto& e : activeEntities) {

        SDL_Rect sourceRect, destRect;
        // Source, what pixels are we drawing?
        sourceRect.x = e->GetEntityRenderingBox().x;
        sourceRect.y = e->GetEntityRenderingBox().y;
        sourceRect.w = e->GetEntityRenderingBox().w;
        sourceRect.h = e->GetEntityRenderingBox().h;

        // Destination, where are we drawing on the screen?

        // The textures are not repositioned accordingly, they overlap after the resize.
        Vec2f renderPos;
        Vec2f renderSize;

        if (e->fixedToCamera) {
            renderPos = e->GetPosition();
            renderSize = Vec2f{
                static_cast<double>(e->GetEntityRenderingBox().w),
                static_cast<double>(e->GetEntityRenderingBox().h)
            };
        } else {
            Vec2f textureSize = Vec2f {
                static_cast<double>(e->GetEntityRenderingBox().w),
                static_cast<double>(e->GetEntityRenderingBox().h)
            };

            renderPos = camera->WorldToScreen(e->GetPosition());
            renderSize = camera->ScaleToZoom(textureSize);
        }

        destRect.x = renderPos.x;
        destRect.y = renderPos.y;
        
        destRect.w = renderSize.x;
        destRect.h = renderSize.y;

        SDL_Texture* entityTexture = e->GetTexture().get();
        
        SDL_RenderCopyEx(
                this->activeRenderer,
                entityTexture,
                &sourceRect,
                &destRect,
                e->GetRotation(),
                e->GetAnchorPoint(),
                e->GetFacingDirection()
            );
    }
}

void WindowRenderer::ClearViewport() {
    SDL_RenderClear(this->activeRenderer);
}

void WindowRenderer::Quit() {
    std::cout << "RENDERER :  Destructed" << '\n';

    SDL_DestroyRenderer(this->activeRenderer);
}