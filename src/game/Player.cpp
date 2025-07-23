#include "Game.h"
#include "Player.h"

void Player::RegisterPlayerInput(Sint32 keyCode, Uint8 inputState) {
    this->player_keyStates[keyCode] = (inputState == SDL_PRESSED);
}

void Player::Awake() {
    Entity::Awake();

    std::string PLAYER_INPUT_REG_ID = "PLAYER_INPUT_REG";
    InputManager::UserInput.Subscribe(PLAYER_INPUT_REG_ID, [this](Sint32 key, Uint8 state) {
        this->RegisterPlayerInput(key, state);
    });
}

void Player::Update(float deltaTime) {
    Entity::Update(deltaTime);

    if (this->isWalking()) {
        this->animator->Play("WalkAnimation", 1);
    } else {
        this->animator->Stop("WalkAnimation");
    }

    Vec2f direction(0, 0);

    if (this->player_keyStates[SDLK_q]) direction.x -= 1;
    if (this->player_keyStates[SDLK_d]) direction.x += 1;
    if (this->player_keyStates[SDLK_SPACE]) this->Jump();
    
    Vec2f player_velocity = direction.Unit() * this->walkSpeed;
    Vec2f currentVelocity = this->GetVelocity();
    
    currentVelocity.x = player_velocity.x;

    if (player_velocity.x < 0) {
        this->SetDirectionFacing(SDL_FLIP_HORIZONTAL);
    } else if (player_velocity.x > 0) {
        this->SetDirectionFacing(SDL_FLIP_NONE);
    }

    this->SetVelocity(currentVelocity);
}

void Player::Jump() {
    if (isGrounded) {
        isJumping = true;
        this->SetVelocity(this->JumpVector);
        AudioManager::PlayAudio(this->jump_sfx, 30);
    };
}