#ifndef TERRAIN_GEN_H
#define TERRAIN_GEN_H

#include <iostream>
#include <vector>
#include <map>

#include "Vec2f.h"
#include "BlockType.h"
#include "FastNoiseLite.h"

#define WORLD_HEIGHT_MIN 500
#define WORLD_HEIGHT_MAX 1000

#define WORLD_WIDTH 1920
#define BLOCK_SIZE 32

class Game;
class EntityManager;
class Terrain {
    public:
        Terrain();

        void SetEntityLoader(Game* _gameInstance, EntityManager* _entityLoader) {
            this->gameInstance = _gameInstance;
            this->entityLoader = _entityLoader;
        }

        void SetSeed(uint64_t seed);
        void ClearWorld();
        void GenerateWorld();
    private:
        Game* gameInstance;
        EntityManager* entityLoader;
        FastNoiseLite noise;
};

#endif