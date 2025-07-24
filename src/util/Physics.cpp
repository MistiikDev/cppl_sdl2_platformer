#include "Entity.h"
#include "Physics.h"

const float epsilon = 0.01f;
const float Physics::GRAVITY = 650.0f;
const Vec2f Physics::GRAVITY_VECTOR = Vec2f {0, GRAVITY};
std::vector<Entity*> Physics::ProcessedEntities;

void Physics::UpdatePositionInWorld(Entity* e, float deltaTime) {    
    double EntityMass = e->GetMass();

    Vec2f lastPosition = e->GetPosition();
    Vec2f lastVelocity = e->GetVelocity();
    Vec2f lastAcceleration = e->GetAcceleration();

    Vec2f Acceleration = lastAcceleration + (GRAVITY_VECTOR * EntityMass);
    Vec2f Velocity = lastVelocity + Acceleration / EntityMass * deltaTime;
    Vec2f newPosition = lastPosition + Velocity * deltaTime;

    if (e->isGrounded && Velocity.y > 0) {
        Velocity.y = 0;
        e->isJumping = false; // Now it's safe to cancel jumping
    }

    e->SetAcceleration(Acceleration);
    e->SetVelocity(Velocity);

    if (e->ClassName == "Player") {
        newPosition.x = e->GetPosition().x; // Hardcoded for now, TODO: Add possibility of locking an axis for physics computations;
    }

    e->SetPosition(newPosition, true);
    e->SetAcceleration(Vec2f::zero);
}

void Physics::CheckEntityCollisions(std::vector<std::shared_ptr<Entity>>& e_list) {
    Physics::ProcessedEntities.clear();

    for (auto& entity : e_list) {
        Entity* e = entity.get();

        e->isGrounded = false;

        if (std::find(Physics::ProcessedEntities.begin(), Physics::ProcessedEntities.end(), e) != Physics::ProcessedEntities.end()) {
            continue;
        }

        if (e->Anchored) { 
            continue; 
        }; // Dont check collisions for anchored entities FOR NOW; as we only check it for moving hitboxes

        for (auto& entity_other : e_list) {
            Entity* e_other = entity_other.get();

            if (e_other == e) {
                continue;
            }

            Physics::CheckForCollisions(e, e_other);
        }
    }
}

void Physics::CheckForCollisions(Entity* e_a, Entity* e_b) {
    if ((e_a->CanCollide && e_b->CanCollide)) {

        Hitbox a_Hitbox {
            e_a->GetPosition().x,
            e_a->GetPosition().y,
            
            e_a->GetEntityRenderingBox().w,
            e_a->GetEntityRenderingBox().h
        };

        Hitbox b_Hitbox = {
            e_b->GetPosition().x,
            e_b->GetPosition().y,

            e_b->GetEntityRenderingBox().w,
            e_b->GetEntityRenderingBox().h
        };


        // Project on x-axis
        if (
            (a_Hitbox.x + a_Hitbox.width >= b_Hitbox.x + epsilon) &&
            (a_Hitbox.x + epsilon <= b_Hitbox.x + b_Hitbox.width) &&
            (a_Hitbox.y + a_Hitbox.heigth >= b_Hitbox.y + epsilon) &&
            (a_Hitbox.y + epsilon <= b_Hitbox.y + b_Hitbox.heigth)
        ) {
            Vec2f MTW = Physics::GetMinimumTranslationVector(a_Hitbox, b_Hitbox);

            if (!e_a->Anchored) {

                if (std::abs(MTW.y) > 0 && MTW.y < 0) { 
                    e_a->isGrounded = true; 
                }

                Physics::ProcessedEntities.push_back(e_a);
                e_a->Push(MTW);

            } else if (!e_b->Anchored) {

                if (std::abs(MTW.y) > 0 && MTW.y < 0) { 
                    e_b->isGrounded = true; 
                }

                Physics::ProcessedEntities.push_back(e_b);
                e_b->Push(MTW);

            } else {
                std::cout << "WARNING: Unsolved Collisions : " << e_a->Name << " / " << e_b->Name << ", unable to move entities." << std::endl;
            }
        } 
    }
}

Vec2f Physics::GetMinimumTranslationVector(Hitbox& a_Hitbox, Hitbox& b_Hitbox) {
    double x_overlap_a = a_Hitbox.x + a_Hitbox.width - b_Hitbox.x;
    double x_overlap_b = b_Hitbox.x + b_Hitbox.width - a_Hitbox.x;

    double y_overlap_a = a_Hitbox.y + a_Hitbox.heigth - b_Hitbox.y;
    double y_overlap_b = b_Hitbox.y + b_Hitbox.heigth - a_Hitbox.y;

    double x_overlap = (x_overlap_a < x_overlap_b) ? -x_overlap_a : x_overlap_b;
    double y_overlap = (y_overlap_a < y_overlap_b) ? -y_overlap_a : y_overlap_b;

    if (std::abs(x_overlap) < 0.01) x_overlap = 0.0;
    if (std::abs(y_overlap) < 0.01) y_overlap = 0.0;
    
    if (abs(x_overlap) < abs(y_overlap)) {
        return Vec2f {static_cast<double>(x_overlap), 0};
    } else {
        return Vec2f {0, static_cast<double>(y_overlap)};
    } // Get the "least" colliding axis
}