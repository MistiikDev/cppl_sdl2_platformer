#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(SDL_Texture* playerTexture) : Entity(Vec2f(100, 400), playerTexture), Score(0) {
            
        }

    private:
        int Score;
};

#endif
