#include "Entity.h"
#include "Camera.h"

Camera::Camera(int w, int h) {
    this->ViewportSize = Vec2f {static_cast<double>(w), static_cast<double>(h)};
    this->Position = Vec2f::zero;
}

void Camera::Follow(Vec2f& TargetPosition) {
    Vec2f DesiredPosition = TargetPosition - (this->ViewportSize / 2);

    this->Position = this->Position.Lerp(DesiredPosition, 0.1f); // Hardcoded for now
}

Vec2f Camera::WorldToScreen(Vec2f& WorldPosition) {
    return WorldPosition - this->Position;
}

Vec2f Camera::ScreenToWorldPosition(Vec2f& ScreenPosition) {
    return ScreenPosition + this->Position;
}