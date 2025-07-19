#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(Game* currentGameInstance, EntityData& entityData, SDL_Texture* texture) : Entity(currentGameInstance, entityData, texture) {};

        Vec2f startPos;

        ~Player() { };

        void Awake();
        void Update(float deltaTime);
        void Jump();

        void GetUserInput(Sint32 keyCode, Uint8 inputState);
    private:
        float walkSpeed = 175.0f;

        std::unordered_map<Sint32, bool> player_keyStates;
};

#endif
