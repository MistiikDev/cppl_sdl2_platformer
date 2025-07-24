#include <vector>
#include "Vec2f.h"

class Entity;

struct Hitbox {
    double x;
    double y;
    int width;
    int heigth;
};

class Physics {
    public:
        static const float GRAVITY;
        static const Vec2f GRAVITY_VECTOR;

        static void UpdatePositionInWorld(Entity* e, float deltaTime);
        static void CheckForCollisions(Entity* e_a, Entity* e_b);

        static void CheckEntityCollisions(std::vector<std::unique_ptr<Entity>>& entity_list);

        static Vec2f GetMinimumTranslationVector(Hitbox& a_Hitbox, Hitbox& b_Hitbox);
    private:
        static std::vector<Entity*> ProcessedEntities;
};