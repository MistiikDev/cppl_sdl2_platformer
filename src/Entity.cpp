#include "Game.h"
#include "Entity.h"

void Entity::SetPosition(Vec2f& newposition) {
    int w = this->entityBox.w;
    int h = this->entityBox.h;
    int screen_w, screen_h;

    this->CurrentGameInstance->GetWindowSize(screen_w, screen_h);

    // new position.coord = clamp(0, screen_width - player_width, coord); -> screen_width - player_width = account for texture thickness!
    newposition.x = std::max(0.0, std::min((double)(screen_w - w), newposition.x));
    newposition.y = std::max(0.0, std::min((double)(screen_h - h), newposition.y));

    this->Position = newposition;
}

void Entity::Update(float deltaTime) {

} 

void Entity::Push(Vec2f& push_vector, float speed) {
    if (this->isPushing) { return; }
    this->isPushing = true;

    Vec2f startPosition = this->GetPosition();
    Vec2f targetPosition = startPosition + push_vector;

    for (int i = 0; i <= 100; i++) {
        float t = static_cast<float>(i) / 100.0f;
        Vec2f lerpedPosition = startPosition.Lerp(targetPosition, t);

        this->SetPosition(lerpedPosition);
    }

    this->isPushing = false;
}