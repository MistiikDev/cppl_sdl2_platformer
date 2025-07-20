#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Game;
class Player : public Entity {
    public:
        Player(Game* currentGameInstance, EntityData& entityData, SDL_Texture* texture) : Entity(currentGameInstance, entityData, texture) {
            ClassName = "Player";
        };
        ~Player() { };
        
        bool isWalking() { return 
            this->isGrounded && this->GetVelocity().Magnitude() > 1 && !this->isJumping && (player_keyStates[SDLK_q] || player_keyStates[SDLK_d]); 
        };

        Vec2f JumpForce {0, -250};

        void Awake();
        void Update(float deltaTime);
        void Jump();

        void RegisterPlayerInput(Sint32 keyCode, Uint8 inputState);
    private:

        float walkSpeed = 175.0f;
        std::unordered_map<Sint32, bool> player_keyStates;
};

#endif
