#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(Game* CurrentGameInstance, const Vec2f& startPosition, SDL_Texture* texture, double Mass) : Entity(CurrentGameInstance, startPosition, texture, Mass) {
            this->Name = "Player";
            this->Anchored = false; // Set by default for now
            this->CanCollide = true;
        };

        ~Player() { };

        virtual void Awake();
        virtual void Update(float deltaTime);

        void GetUserInput(Sint32 keyCode, Uint8 inputState);
    private:
        bool isJumping;
        float walkSpeed = 100.0f;

        std::unordered_map<Sint32, bool> player_keyStates;
};

#endif
