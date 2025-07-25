#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Game;
class Player : public Entity {
    public:
        Player(Game* currentGameInstance, EntityData& entityData, std::shared_ptr<SDL_Texture> texture) : Entity(currentGameInstance, entityData, texture) {
            ClassName = "Player";
        };
        ~Player() { };
        
        bool isWalking() { return 
            this->isGrounded && this->GetVelocity().Magnitude() > 1 && !this->isJumping && (player_keyStates[SDLK_q] || player_keyStates[SDLK_d]); 
        };
        
        int DashForce = 200;
        double JumpForce = 250;

        float DashDuration = 0.3f;
        float lastDash = 0;
        float dashTimer = 0;

        bool isDashing = false;

        Vec2f RealWorldPosition;
        Vec2f JumpVector { 0, -250 };

        std::string jump_sfx =  "jump_sfx";

        Vec2f GetRealWorldPosition() {
            return this->RealWorldPosition; // Original offset
        };

        void Awake();
        void Update(float deltaTime);
        void Jump();
        void Dash();

        void RegisterPlayerInput(Sint32 keyCode, Uint8 inputState);
    private:        
        float walkSpeed = 175.0f;

        std::unordered_map<Sint32, bool> player_keyStates;
};

#endif
