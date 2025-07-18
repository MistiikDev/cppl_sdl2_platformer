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
        Entity(Game* CurrentGameInstance, const Vec2f& startPosition, SDL_Texture* texture, double Mass) : 
            CurrentGameInstance(CurrentGameInstance), Position(startPosition), entityTexture(texture), Mass(Mass) 
        {
            SDL_QueryTexture(texture, NULL, NULL, &entityBox.w, &entityBox.h);

            this->Name = "Generic Entity";
            
            this->Anchored = true; // Set by default for now
            this->CanCollide = true;
            
            this->Velocity = Vec2f {0, 0};
            this->Acceleration = Vec2f {0, 0};

            entityBox.x = 0;
            entityBox.y = 0;
        };

        ~Entity() { }

        bool Anchored;
        bool CanCollide;
        
        bool isPushing = false;
        bool isJumping = false;
        bool isGrounded = false;

        std::string Name;

        virtual void Awake() {};
        virtual void Update(float deltaTime);

        void Push(Vec2f& push_vector, float speed = 0.1f);

        void SetPosition(Vec2f& position);
        void SetVelocity(const Vec2f& velocity) { this->Velocity = velocity; }; 
        void SetAcceleration(const Vec2f& acceleration) {this->Acceleration = acceleration; };

        double GetMass() { return Mass; };

        Vec2f& GetPosition() { return Position; };
        Vec2f& GetVelocity() { return Velocity ;};
        Vec2f& GetAcceleration() { return Acceleration; };

        Vec2f GetSize() {
            return Vec2f {
                (double)this->GetEntityRenderingBox().w,
                (double)this->GetEntityRenderingBox().h
            };
        }

        SDL_Rect& GetEntityRenderingBox() { return entityBox; };
        SDL_Texture* GetTexture() { return entityTexture; };
    private:

        double Mass;

        Vec2f Position;
        Vec2f Velocity;
        Vec2f Acceleration;

        SDL_Rect entityBox;
        SDL_Texture* entityTexture;

        Game* CurrentGameInstance;
};

#endif