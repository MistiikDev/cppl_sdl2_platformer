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

#define MINIMUM_DIRT_DEPTH 2

class EntityManager;
class Terrain {
    public:
        Terrain();

        void SetEntityLoader(EntityManager* _entityLoader) {
            std::cout << "Loading Entity Loader" << std::endl;
            this->entityLoader = _entityLoader;

            std::cout << "Loaded Entity Loader" << std::endl;
        }

        void SetSeed(uint64_t seed);
        void ClearWorld();
        void GenerateWorld();
    private:
        EntityData defaultBlockData;
        EntityManager* entityLoader;
        FastNoiseLite noise;
};

#endif