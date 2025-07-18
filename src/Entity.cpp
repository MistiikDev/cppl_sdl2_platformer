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