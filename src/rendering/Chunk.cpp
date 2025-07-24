#include "Chunk.h"

bool Chunk::isVisibleToPlayer(Vec2f& playerPosition) {
    int topLeftCoords_X = 0;
    int topLeftCoords_Y = chunkData[topLeftCoords_X].front();

    int topRightCoords_X = this->chunkSizeInBlocks_X * BLOCK_SIZE;
    int topRightCoords_Y = chunkData[topRightCoords_X].front();

    Vec2f topLeftCoords { topLeftCoords_X, topLeftCoords_Y };
    Vec2f topRightCoords { topRightCoords_X, topRightCoords_Y };

    return (std::min(std::abs((playerPosition - topLeftCoords).Magnitude()), std::abs((playerPosition - topLeftCoords).Magnitude()))) < 1920; // hardcoded aswell for now
}

void Chunk::Generate() {
    // Init noise

    this->defaultBlockData.Anchored = true;
    this->defaultBlockData.CanCollide = true;
    this->defaultBlockData.Passive = true;
    this->defaultBlockData.Class = "WorldBlock";
    this->defaultBlockData.Name = "Block";

    float HeigthAmplitude = (WORLD_HEIGHT_MAX - WORLD_HEIGHT_MIN) / 2;

    this->chunkNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    this->chunkNoise.SetFrequency(this->chunkSmoothness);
    this->chunkNoise.SetSeed(static_cast<int>(time(NULL)));

    for (int x = 0; x < this->chunkSizeInBlocks_X * BLOCK_SIZE; x += BLOCK_SIZE) { // Passing through pixels
        float x_float = static_cast<float>(x);
        float localNoise = this->chunkNoise.GetNoise(x_float, 0.0f); // Between -1 and 1

        float localNoiseNormal = (localNoise + 1.0f) / 2.0f;

        int height = static_cast<int>(WORLD_HEIGHT_MIN + (localNoiseNormal * HeigthAmplitude));

        // clamp height between
        height -= height % BLOCK_SIZE;

        if (height < WORLD_HEIGHT_MIN)
            height = WORLD_HEIGHT_MIN;
        if (height > WORLD_HEIGHT_MAX)
            height = WORLD_HEIGHT_MAX;

        std::vector<int> y_depth;

        for (int y = height; y < this->chunkSizeInBlocks_Y * BLOCK_SIZE; y += BLOCK_SIZE) {

            std::cout << "TERRAIN : Block position : X (" << x << ") / Y(" << y << ")" << std::endl;

            y_depth.push_back(y);

            // this->entityLoader->CreateEntity(localBlockData);
        }

        
        this->chunkData[x] = y_depth;
    }
}

void Chunk::LoadEntities(EntityManager* entityManager) {
    for (auto coordinateData : this->chunkData) {
        int x = coordinateData.first;
        
        for (int y : coordinateData.second) {
            int x = coordinateData.first;
            int maxHeight = coordinateData.second.front();

            EntityData localBlockData = this->defaultBlockData;
            localBlockData.Position = Vec2f{static_cast<double>(x), static_cast<double>(y)};

            int salt = rand() % 5; // Random depth factor to choose generation from

            if (y == maxHeight) {
                localBlockData.TexturePath = "src/assets/art/blocs/grass.png";

            } else if (y > maxHeight && y < maxHeight + (MINIMUM_DIRT_DEPTH + salt) * BLOCK_SIZE) {
                localBlockData.TexturePath = "src/assets/art/blocs/dirt.png";

            } else {
                localBlockData.TexturePath = "src/assets/art/blocs/stone.png";
            }


            std::cout << "CHUNK : Block Set On : ";
            localBlockData.Position.print();
            
            std::shared_ptr<Entity> block = entityManager->CreateEntity(localBlockData);
            this->renderedBlocks.push_back(block);
        }
    }

    this->isLoaded = true;
}

void Chunk::UnloadEntities(EntityManager* entityManager) {
    for (std::shared_ptr<Entity> block : this->renderedBlocks) {
        entityManager->ClearEntity(block);
    }

    this->isLoaded = false;
}