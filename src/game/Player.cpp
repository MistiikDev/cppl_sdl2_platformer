#include "Player.h"
#include "Game.h"

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
    Vec2f currentPlayerPosition = this->GetPosition();

    if (this->player_keyStates[SDLK_q]) direction.x -= 1;
    if (this->player_keyStates[SDLK_d]) direction.x += 1;
    if (this->player_keyStates[SDLK_SPACE]) this->Jump();

    Vec2f unit_direction = direction.Unit();
    Vec2f player_velocity = unit_direction * this->walkSpeed;
    Vec2f currentVelocity = this->GetVelocity();
    
    currentVelocity.x = player_velocity.x;

    this->SetVelocity(currentVelocity);

    if (player_velocity.x < 0) {
        this->SetDirectionFacing(SDL_FLIP_HORIZONTAL);
    } else if (player_velocity.x > 0) {
        this->SetDirectionFacing(SDL_FLIP_NONE);
    }
}

void Player::Jump() {
    if (isGrounded) {
        isJumping = true;
        this->SetVelocity(this->JumpForce);
    };
}

void Player::RegisterPlayerInput(Sint32 keyCode, Uint8 inputState) {
    this->player_keyStates[keyCode] = (inputState == SDL_PRESSED);
}
