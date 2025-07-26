#ifndef CHUNK_H
#define CHUNK_H

#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "BlockType.h"
#include "Vec2f.h"

#include "EntityManager.h"
#include "FastNoiseLite.h"

#define WORLD_HEIGHT_MIN 256
#define WORLD_HEIGHT_MAX 1024

#define BLOCK_SIZE 32
#define CHUNK_SIZE_X 32 // Chunk Width In Pixels
#define CHUNK_SIZE_Y 48 // Chunk Heigth In Pixels

#define MINIMUM_DIRT_DEPTH 2

extern int chunkWidth; 
extern int chunkHeigth;

struct Chunk {
    int seed;
    float chunkSmoothness = 0.003f;
    bool isLoaded = false;
    bool isGenerated = false;

    bool isVisibleToPlayer(Vec2f& playerPosition);

    void SetSeed(int seed);

    void Generate();
    void Load(EntityManager* entityManager);
    void UnloadEntities(EntityManager* entityManager);

    std::map<int, std::vector<int>> chunkData;
    std::unordered_map<uint64_t, std::shared_ptr<Entity>> renderedBlocks;

    Vec2f Position;
    FastNoiseLite chunkNoise;
    EntityData defaultBlockData;
};

#endif