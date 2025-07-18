#include "Player.h"

void Player::GetUserInput(Sint32 keyCode, Uint8 inputState) {
    bool isPressed = (inputState == SDL_PRESSED);

    this->player_keyStates[keyCode] = isPressed;
}

void Player::Awake() {
    std::string PLAYER_INPUT_REG_ID = "PLAYER_INPUT_REG";

    InputManager::UserInput.Subscribe(PLAYER_INPUT_REG_ID, [this](Sint32 key, Uint8 state) {
        this->GetUserInput(key, state);
    });
}

void Player::Update(float deltaTime) {
    // Vec2f direction(0, 0);
    // Vec2f currentPlayerPosition = this->GetPosition();

    // if (this->player_keyStates[SDLK_q]) direction.x -= 1;
    // if (this->player_keyStates[SDLK_d]) direction.x += 1;

    // Vec2f unit_direction = direction.Unit();
    // Vec2f proc_velocity = unit_direction * this->walkSpeed;

    // Vec2f currentVelocity = this->GetVelocity();
    // currentVelocity.x = proc_velocity.x;

    // this->SetVelocity(currentVelocity);
}