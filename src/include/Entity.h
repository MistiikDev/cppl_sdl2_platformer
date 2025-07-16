#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"

class Entity {
    public:
        Entity(Vec2f& startPosition, SDL_Texture* texture): position(startPosition), entityTexture(texture) {
            SDL_QueryTexture(texture, NULL, NULL, &entityBox.w, &entityBox.h);

            entityBox.x = 0;
            entityBox.y = 0;
        };

        void SetPosition(Vec2f& position) { this->position = position; }

        Vec2f& GetPosition() { return position; };
        SDL_Rect& GetEntityRenderingBox() { return entityBox; };
        SDL_Texture* GetTexture() { return entityTexture; };
    private:
        Vec2f position;
        SDL_Rect entityBox;
        SDL_Texture* entityTexture;
};

#endif