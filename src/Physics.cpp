#include "Entity.h"
#include "Physics.h"

const float Physics::GRAVITY = 450.0f;
const Vec2f Physics::GRAVITY_VECTOR = Vec2f {0, GRAVITY};

void Physics::UpdatePositionInWorld(Entity* e, float deltaTime) {
    double EntityMass = e->GetMass();

    Vec2f lastPosition = e->GetPosition();
    Vec2f lastVelocity = e->GetVelocity();
    Vec2f lastAcceleration = e->GetAcceleration();

    Vec2f Acceleration = lastAcceleration + (GRAVITY_VECTOR * EntityMass);
    Vec2f Velocity = lastVelocity + Acceleration / EntityMass * deltaTime;
    Vec2f newPosition = lastPosition + Velocity * deltaTime;

    e->SetAcceleration(Acceleration);
    e->SetVelocity(Velocity);
    e->SetPosition(newPosition);

    e->SetAcceleration(Vec2f::zero);
}

void Physics::CheckEntityCollisions(std::vector<Entity*>& e_list) {
    for (Entity* e : e_list) {
        for (Entity* e_other : e_list) {
            if (e_other == e) {
                continue;
            }

            Physics::CheckForCollisions(e, e_other);
        }
    }
}


void Physics::CheckForCollisions(Entity* e_a, Entity* e_b) {
    if ((e_a->CanCollide && e_b->CanCollide)) {
        SDL_Rect& a_Hitbox = e_a->GetEntityRenderingBox();
        SDL_Rect& b_Hitbox = e_b->GetEntityRenderingBox();

        // Project on x-axis
        if (
            (a_Hitbox.x + a_Hitbox.w >= b_Hitbox.x) &&
            (a_Hitbox.x <= b_Hitbox.x + b_Hitbox.w) &&
            (a_Hitbox.y + a_Hitbox.h >= b_Hitbox.y) &&
            (a_Hitbox.y <= b_Hitbox.y + b_Hitbox.h)
        ) {
            Vec2f MTW = Physics::GetMinimumTranslationVector(a_Hitbox, b_Hitbox);
            MTW.print();
        } 
    }
}

Vec2f Physics::GetMinimumTranslationVector(SDL_Rect& a_Hitbox, SDL_Rect& b_Hitbox) {
    int x_overlap_a = a_Hitbox.x + a_Hitbox.w - b_Hitbox.x;
    int x_overlap_b = b_Hitbox.x + b_Hitbox.w - a_Hitbox.x;

    int y_overlap_a = a_Hitbox.y + a_Hitbox.h - b_Hitbox.y;
    int y_overlap_b = b_Hitbox.y + b_Hitbox.h - a_Hitbox.y;

    int x_overlap = (x_overlap_a < x_overlap_b) ? x_overlap_a : -x_overlap_b;
    int y_overlap = (y_overlap_a < y_overlap_b) ? y_overlap_a : -y_overlap_b;

    if (abs(x_overlap) < abs(y_overlap)) {
        return Vec2f {static_cast<double>(x_overlap), 0};
    } else {
        return Vec2f {0, static_cast<double>(y_overlap)};
    } // Get the "least" colliding axis
}