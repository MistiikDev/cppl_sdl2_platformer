#include "Player.h"
#include "Game.h"

void Player::Awake() {
    Entity::Awake();

    std::string PLAYER_INPUT_REG_ID = "PLAYER_INPUT_REG";
    InputManager::UserInput.Subscribe(PLAYER_INPUT_REG_ID, [this](Sint32 key, Uint8 state) {
        this->RegisterPlayerInput(key, state);
    });

    SDL_Texture* raw_tex1 = IMG_LoadTexture(SDL_GetRenderer(this->CurrentGameInstance->GetWindow()), "src/assets/art/sprites/player_sprite_sized.png");
    SDL_Texture* raw_tex2 = IMG_LoadTexture(SDL_GetRenderer(this->CurrentGameInstance->GetWindow()), "src/assets/art/sprites/player_sprite_sized_walking.png");

    if (!raw_tex1 || !raw_tex2) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
    }

    auto tex1 = std::shared_ptr<SDL_Texture>(raw_tex1, SDL_DestroyTexture);
    auto tex2 = std::shared_ptr<SDL_Texture>(raw_tex2, SDL_DestroyTexture);

    this->walkAnimation.frames = { tex2, tex1 };
    this->walkAnimation.Name = "WalkAnimation";
    this->walkAnimation.duration = 0.4f;
    this->walkAnimation.looped = true;

    this->animator->LoadAnimation(walkAnimation);
}

void Player::Update(float deltaTime) {
    Entity::Update(deltaTime);

    if (this->isWalking()) {
        this->animator->Play(this->walkAnimation.Name, 1);
    } else {
        this->animator->Stop(this->walkAnimation.Name);
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
