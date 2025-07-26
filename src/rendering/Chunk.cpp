#include "Chunk.h"

int chunkWidth = CHUNK_SIZE_X * BLOCK_SIZE;
int chunkHeigth = CHUNK_SIZE_Y * BLOCK_SIZE;

bool Chunk::isVisibleToPlayer(Vec2f& playerPosition) {
    double halfScreen = 1920 / 2.0;
    double bufferSize = 2 * chunkWidth;

    double visibleStart = playerPosition.x - halfScreen - bufferSize;
    double visibleEnd   = playerPosition.x + halfScreen + bufferSize;

    int chunkStartX = static_cast<int>(this->Position.x);
    int chunkEndX   = chunkStartX + chunkWidth;

    // Check if the chunk overlaps with the visible + buffer zone
    return (chunkEndX >= visibleStart && chunkStartX <= visibleEnd);
}

void Chunk::SetSeed(int seed) {
    this->seed = seed;
}

void Chunk::Generate() {
    // Init noise
    if (isGenerated) return;
    
    float HeigthAmplitude = (WORLD_HEIGHT_MAX - WORLD_HEIGHT_MIN) / 2;

    this->defaultBlockData.Anchored = true;
    this->defaultBlockData.CanCollide = true;
    this->defaultBlockData.Passive = true;
    this->defaultBlockData.fixedToCamera = false;
    
    this->defaultBlockData.Class = "WorldBlock";
    this->defaultBlockData.Name = "Block";

    this->chunkNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    this->chunkNoise.SetFrequency(this->chunkSmoothness);
    this->chunkNoise.SetSeed(this->seed);

    for (int x = 0; x < chunkWidth; x += BLOCK_SIZE) {
        int worldBlockX = static_cast<int>(this->Position.x + x);

        float x_float = static_cast<float>(worldBlockX);
        float localNoise = this->chunkNoise.GetNoise(x_float, 0.0f);

        float localNoiseNormal = (localNoise + 1.0f) / 2.0f;

        int height = static_cast<int>(WORLD_HEIGHT_MIN + (localNoiseNormal * HeigthAmplitude));
        height -= height % BLOCK_SIZE;

        if (height < WORLD_HEIGHT_MIN) height = WORLD_HEIGHT_MIN;
        if (height > WORLD_HEIGHT_MAX) height = WORLD_HEIGHT_MAX;

        std::vector<int> y_depth;

        for (int y = 0; y < height; y += BLOCK_SIZE)
            y_depth.push_back(BlockType::Air);

        int blockDepth = 0;

        for (int y = height; y < chunkHeigth; y += BLOCK_SIZE) {
            BlockType block;

            if (blockDepth == 0)
                block = BlockType::Grass;
            else if (blockDepth <= MINIMUM_DIRT_DEPTH + (rand() % 3))
                block = BlockType::Dirt;
            else
                block = BlockType::Stone;

            y_depth.push_back(block);
            blockDepth++;
        }

        this->chunkData[worldBlockX] = y_depth;
    }

    this->isGenerated = true;
}

typedef unsigned long long uint64_t;

uint64_t pair(int a, int b) {
    // Convert signed to unsigned uniquely
    unsigned long long ua = (a >= 0) ? (a * 2ULL) : (-a * 2ULL - 1);
    unsigned long long ub = (b >= 0) ? (b * 2ULL) : (-b * 2ULL - 1);

    // Szudzik's pairing function
    return (ua >= ub) ? (ua * ua + ua + ub) : (ub * ub + ua);
}

void Chunk::Load(EntityManager* entityManager) {
    if (this->isLoaded) return;
    if (!this->isGenerated) this->Generate();
    
    for (auto& [x, y_depth] : this->chunkData) {
        int y = 0;

        for (int block_type : y_depth) {
            EntityData localBlockData = this->defaultBlockData;

            localBlockData.Anchored = true;
            localBlockData.Passive = true;
            localBlockData.fixedToCamera = false;
            
            localBlockData.Class = "WorldBlock";
            localBlockData.Name = "Block";

            localBlockData.ID = pair(x, y);
            localBlockData.Position = Vec2f{static_cast<double>(x), static_cast<double>(y)};

            switch (block_type) {
                case (BlockType::Air): {
                    localBlockData.CanCollide = false;
                    localBlockData.TexturePath = "src/assets/art/blocs/air.png";
                    break;
                };

                case (BlockType::Dirt): {
                    localBlockData.TexturePath = "src/assets/art/blocs/dirt.png";
                    break;
                };

                case (BlockType::Grass): {
                    localBlockData.TexturePath = "src/assets/art/blocs/grass.png";
                    break;
                };

                case (BlockType::Stone): {
                    localBlockData.TexturePath = "src/assets/art/blocs/stone.png";
                    break;
                }

                default: {
                    localBlockData.TexturePath = "src/assets/art/blocs/debug.png";
                    break;
                }
            }

            this->renderedBlocks[localBlockData.ID] = entityManager->CreateEntity(localBlockData);
            // if (this->renderedBlocks[localBlockData.ID]) {
            //     //std::cout << "CHUNK LOADING: Culling Block" << std::endl;
                
            //     this->renderedBlocks[localBlockData.ID]->isActive = true;
            // } else {
            //     //std::cout << "CHUNK LOADING: Creating Block" << std::endl;
                
            //     this->renderedBlocks[localBlockData.ID] = entityManager->CreateEntity(localBlockData);;
            // }

            y += BLOCK_SIZE;
        }
    }

    this->isLoaded = true;
}

void Chunk::UnloadEntities(EntityManager* entityManager) {
    if (!this->isLoaded) return;

    for (auto& data : this->renderedBlocks) {
        uint64_t blockID = data.first;
        std::shared_ptr<Entity> block = data.second;

        entityManager->ClearEntity(block); 

        //block->isActive = false;
    }

    this->isLoaded = false;
}