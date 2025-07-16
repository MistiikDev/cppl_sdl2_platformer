#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"
#include "InputManager.h"

class Game;
class Entity {
    public:
        Entity(Game* CurrentGameInstance, Vec2f& startPosition, SDL_Texture* texture): CurrentGameInstance(CurrentGameInstance), position(startPosition), entityTexture(texture) {
            SDL_QueryTexture(texture, NULL, NULL, &entityBox.w, &entityBox.h);

            entityBox.x = 0;
            entityBox.y = 0;
        };

        ~Entity() {
            
        }

        virtual void Awake() {};
        virtual void Update(float deltaTime) {};

        void SetPosition(Vec2f& position);
        void AddVelocity(Vec2f& velocity);

        double GetDeltaTime();


        Vec2f& GetPosition() { return position; };
        Vec2f& GetVelocity() { return Velocity ;};

        SDL_Rect& GetEntityRenderingBox() { return entityBox; };
        SDL_Texture* GetTexture() { return entityTexture; };

    private:
        Vec2f position;
        Vec2f Velocity;


        SDL_Rect entityBox;
        SDL_Texture* entityTexture;

        Game* CurrentGameInstance;
};

#endif