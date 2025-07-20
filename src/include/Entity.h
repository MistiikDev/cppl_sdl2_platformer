#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"
#include "InputManager.h"
#include "EntityData.h"
#include "Animation.h"
#include "Animator.h"

class Game;
class Entity {
    public:
        Entity(Game* game, const EntityData& data, SDL_Texture* texture);
        ~Entity() { }

        // -- Propreties -- 

        bool Anchored;
        bool CanCollide;
        bool isPushing = false;
        bool isJumping = false;
        bool isGrounded = false;

        std::string Name;
        std::string RenderingGroup;

        int RenderingLayer;

        double GetMass() { return Mass; };

        // -- Physics -- 
        
        void SetPosition(Vec2f& position);
        void SetVelocity(const Vec2f& velocity) { this->Velocity = velocity; }; 
        void SetAcceleration(const Vec2f& acceleration) { this->Acceleration = acceleration; };
        void SetRotation(int Rotation) { this->Rotation = Rotation; };

        void Push(Vec2f& push_vector, float speed = 0.1f);

        int GetRotation() { return Rotation; };
        Vec2f& GetPosition() { return Position; };
        Vec2f& GetVelocity() { return Velocity ;};
        Vec2f& GetAcceleration() { return Acceleration; };

        Vec2f GetSize() {
            return Vec2f {
                (double)this->GetEntityRenderingBox().w,
                (double)this->GetEntityRenderingBox().h
            };
        }

        // -- Rendering --

        void SetRendererFlip(SDL_RendererFlip newFlip) { this->Flip = newFlip; };
        void SetAnchorPoint(SDL_Point* anchorPoint) { this->AnchordPoint = anchorPoint; };
        void SetTexture(SDL_Texture* texture) { this->Texture = texture; };
        void SetEntityRenderingBounds(SDL_Rect& boundingBox) { this->BoundingBox = boundingBox; }
        
        void ResetTextureDefault() { this->Texture = this->DefaultTexture; };

        SDL_Texture* GetTexture() { return Texture; };
        SDL_Point* GetAnchorPoint() { return this->AnchordPoint; };

        SDL_RendererFlip GetRendererFlip() { return this->Flip; };
        SDL_Rect& GetEntityRenderingBox() { return BoundingBox; };

        virtual void Awake();
        virtual void Update(float deltaTime);

        // -- Animation -- 

        Animator* animator;

    protected:

        Game* CurrentGameInstance;

    private:
        double Mass;

        Vec2f Position;
        Vec2f Velocity;
        Vec2f Acceleration;

        int Rotation;
        SDL_Rect BoundingBox;
        SDL_RendererFlip Flip;

        SDL_Point* AnchordPoint;
        SDL_Texture* DefaultTexture;
        SDL_Texture* Texture;
        
        std::vector<std::unique_ptr<AnimationTrack>> LoadedAnimations;
};

#endif