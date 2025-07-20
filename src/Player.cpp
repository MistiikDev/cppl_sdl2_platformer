#include "Player.h"
#include "Game.h"

void Player::Awake() {
    Entity::Awake();

    std::string PLAYER_INPUT_REG_ID = "PLAYER_INPUT_REG";

    InputManager::UserInput.Subscribe(PLAYER_INPUT_REG_ID, [this](Sint32 key, Uint8 state) {
        this->GetUserInput(key, state);
    });

    SDL_Texture* raw_tex1 = IMG_LoadTexture(SDL_GetRenderer(this->CurrentGameInstance->GetWindow()), "src/art/sprites/player_sprite_sized.png");
    SDL_Texture* raw_tex2 = IMG_LoadTexture(SDL_GetRenderer(this->CurrentGameInstance->GetWindow()), "src/art/sprites/player_sprite_sized_walking.png");

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
    Vec2f proc_velocity = unit_direction * this->walkSpeed;
    Vec2f currentVelocity = this->GetVelocity();
    currentVelocity.x = proc_velocity.x;

    SDL_RendererFlip flip = currentVelocity.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    this->SetVelocity(currentVelocity);
    
    if (proc_velocity.x < 0) {
        this->SetRendererFlip(SDL_FLIP_HORIZONTAL);
    } else if (proc_velocity.x > 0) {
        this->SetRendererFlip(SDL_FLIP_NONE);
    }
}

void Player::Jump() {
    if (!isGrounded) return;

    isJumping = true;

    Vec2f jumpImpulse = Vec2f {0, -300};  // Negative Y to go up
    this->SetVelocity(jumpImpulse);
}

void Player::GetUserInput(Sint32 keyCode, Uint8 inputState) {
    bool isPressed = (inputState == SDL_PRESSED);

    this->player_keyStates[keyCode] = isPressed;
}
