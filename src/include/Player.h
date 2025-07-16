#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(Game* CurrentGameInstance, Vec2f& startPosition, SDL_Texture* texture) : Entity(CurrentGameInstance, startPosition, texture) {};

        ~Player() {
            
        }

        virtual void Awake();
        virtual void Update(float deltaTime);

        void GetUserInput(Sint32 keyCode, Uint8 inputState);
    private:
        bool isJumping;
        float walkSpeed = 100.0f;

        std::unordered_map<Sint32, bool> player_keyStates;
};

#endif
