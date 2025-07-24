#include <vector>
#include <map>
#include <iostream>

#include "BlockType.h"
#include "Vec2f.h"

#include "EntityManager.h"
#include "FastNoiseLite.h"

#define WORLD_HEIGHT_MIN 500
#define WORLD_HEIGHT_MAX 1000

#define BLOCK_SIZE 32
#define MINIMUM_DIRT_DEPTH 2

struct Chunk {
    float chunkSmoothness = 0.003f;
    bool isLoaded = false;
    bool isVisibleToPlayer(Vec2f& playerPosition);

    unsigned int chunkSizeInBlocks_X = 32; // In terms of blocks, meaning its buffering 32 * 32 = 1024 pixels
    unsigned int chunkSizeInBlocks_Y = 64;

    void Generate();
    void LoadEntities(EntityManager* entityManager);
    void UnloadEntities(EntityManager* entityManager);

    std::map<int, std::vector<int>> chunkData;
    std::vector<std::shared_ptr<Entity>> renderedBlocks;

    Vec2f Position;
    FastNoiseLite chunkNoise;
    EntityData defaultBlockData;
};