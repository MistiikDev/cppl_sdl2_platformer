#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"
#include "InputManager.h"
#include "EntityData.h"

class Game;
class Entity {
    public:
        Entity(Game* CurrentGameInstance, EntityData& entityData, SDL_Texture* EntityTexture) : CurrentGameInstance(CurrentGameInstance) {
            this->Name = entityData.Name;

            this->Anchored = entityData.Anchored;
            this->CanCollide = entityData.CanCollide;
            
            this->Position = entityData.Position; // Start Position;
            this->Velocity = Vec2f {0, 0};
            this->Acceleration = Vec2f {0, 0};

            this->Mass = entityData.Mass;

            entityBox.x = 0;
            entityBox.y = 0;

            this->entityTexture = EntityTexture;

            this->RenderingGroup = entityData.RenderingGroup;
            this->RenderingLayer = entityData.RenderingLayer;

            SDL_QueryTexture(this->entityTexture, NULL, NULL, &entityBox.w, &entityBox.h);
        };

        ~Entity() { }

        bool Anchored;
        bool CanCollide;
        
        bool isPushing = false;
        bool isJumping = false;
        bool isGrounded = false;

        std::string Name;
        std::string RenderingGroup;

        int RenderingLayer;

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