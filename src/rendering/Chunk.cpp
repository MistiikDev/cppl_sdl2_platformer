#include "Chunk.h"

#define PRELOAD_BUFFER 1 // Number of chunks between loads, preload chunks BEFORE entering it.

int chunkWidth = CHUNK_SIZE_X * BLOCK_SIZE;
int chunkHeigth = CHUNK_SIZE_Y * BLOCK_SIZE;

bool Chunk::isVisibleToPlayer(Vec2f& playerPosition) {
    int chunkStartX = this->Position.x;
    int chunkEndX = chunkStartX + chunkWidth;

    return ((playerPosition.x >= (chunkStartX - (PRELOAD_BUFFER * chunkWidth))) && (playerPosition.x <= (chunkEndX + (PRELOAD_BUFFER * chunkWidth))));
}

void Chunk::Generate() {
    // Init noise

    if (isGenerated) return;

    this->defaultBlockData.Anchored = true;
    this->defaultBlockData.CanCollide = true;
    this->defaultBlockData.Passive = true;
    this->defaultBlockData.isScrollable = true;
    
    this->defaultBlockData.Class = "WorldBlock";
    this->defaultBlockData.Name = "Block";

    float HeigthAmplitude = (WORLD_HEIGHT_MAX - WORLD_HEIGHT_MIN) / 2;

    this->chunkNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    this->chunkNoise.SetFrequency(this->chunkSmoothness);
    this->chunkNoise.SetSeed(static_cast<int>(time(NULL)));

    for (int x = this->Position.x; x < chunkWidth; x += BLOCK_SIZE) {
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

        for (int y = 0; y < height; y+=BLOCK_SIZE) {
            y_depth.push_back(BlockType::Air);
        }

        int blockDepth = 0;

        for (int y = height; y < chunkHeigth; y += BLOCK_SIZE) { // make y start at 0 ? account for air blocks, makes full chunks
            std::cout << "CHUNK GENERATION : Block position : X (" << x << ") / Y(" << y << ")" << std::endl;

            int salt = rand() % 5; // Random depth factor to choose generation from
            BlockType block;

            if (blockDepth == 0) {
                block = BlockType::Grass;

            } else if (blockDepth <= MINIMUM_DIRT_DEPTH + (rand() % 3)) {
                block = BlockType::Dirt;

            } else {
                block = BlockType::Stone;
            }

            y_depth.push_back(block);

            blockDepth ++;
        }

        this->chunkData[x] = y_depth;
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

    for (auto coordinateData : this->chunkData) {
        int x = coordinateData.first;
        int y = 0;

        for (int block_type : coordinateData.second) {
            EntityData localBlockData = this->defaultBlockData;

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
            }

            std::cout << "CHUNK LOADING: Rendering Block (ID : " << localBlockData.ID << ") @ :";
            localBlockData.Position.print();
            
            if (this->renderedBlocks[localBlockData.ID]) {
                std::cout << "CHUNK LOADING: Culling Block" << std::endl;
                this->renderedBlocks[localBlockData.ID]->isActive = true;
            } else {
                std::cout << "CHUNK LOADING: Creating Block" << std::endl;
                std::shared_ptr<Entity> block = entityManager->CreateEntity(localBlockData);
                this->renderedBlocks[localBlockData.ID] = block;
            }

            // auto it = std::find_if(this->renderedBlocks.begin(), this->renderedBlocks.end(), 
            //     [&localBlockData](const std::shared_ptr<Entity>& entityA) {
            //         return localBlockData.ID == entityA->ID;
            // });

            // if (it != this->renderedBlocks.end()) {
            //     std::cout << "CHUNK LOADING : Reactivating Entity" << std::endl;
            //     it->get()->isActive = true; // Set already existing entity to load;
            // } else {
            //     std::shared_ptr<Entity> block = entityManager->CreateEntity(localBlockData);
            //     block->isActive = true;

            //     this->renderedBlocks.push_back(block);
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

        block->isActive = false;
    }

    this->isLoaded = false;
}