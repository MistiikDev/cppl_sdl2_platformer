#include "Entity.h"
#include "Camera.h"

Camera::Camera(int w, int h) {
    this->ViewportSize = Vec2f {static_cast<double>(w), static_cast<double>(h)};
    this->Position = Vec2f::zero;

    Depth = 1;
}

void Camera::Follow(Vec2f& TargetPosition) {
    if (!this->isFollowing) this->Depth = this->Depth / 1.5f;

    this->isFollowing = true;

    Vec2f ScreenCenter = (this->ViewportSize / 2) * this->Depth;
    Vec2f DesiredPosition = TargetPosition - ScreenCenter;

    this->Position = this->Position.Lerp(DesiredPosition, 0.1f); // Hardcoded for now
}

Vec2f Camera::WorldToScreen(Vec2f& WorldPosition) {
    Vec2f ScreenCenter = this->ViewportSize / 2;

    return (WorldPosition - this->Position) * (1 / this->Depth);
}

Vec2f Camera::ScaleToZoom(Vec2f& size) {
    return size * (1.0 / this->Depth);
}

Vec2f Camera::ScreenToWorldPosition(Vec2f& ScreenPosition) {
    return ScreenPosition + this->Position;
}