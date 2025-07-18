#include <vector>

class Entity;
class Physics {
    public:
        static const float GRAVITY;
        static const Vec2f GRAVITY_VECTOR;

        static void UpdatePositionInWorld(Entity* e, float deltaTime);
        
        static void CheckForCollisions(Entity* e_a, Entity* e_b);
        static void CheckEntityCollisions(std::vector<Entity*>& entity_list);

        static Vec2f GetMinimumTranslationVector(SDL_Rect& a_Hitbox, SDL_Rect& b_Hitbox);

    private:

};