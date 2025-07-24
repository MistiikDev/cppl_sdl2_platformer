#include "EntityManager.h"
#include "Entity.h"          
#include "Terrain.h"

Terrain::Terrain() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.003f); // Hardcoded for now;
    noise.SetSeed(static_cast<int>(time(NULL)));

    defaultBlockData.Anchored = true;
    defaultBlockData.CanCollide = true;
    defaultBlockData.Passive = true;
    defaultBlockData.Class = "WorldBlock";
    defaultBlockData.Name = "Block";

    std::cout << "TERRAIN : Generation ready" << std::endl;
}

void Terrain::ClearWorld() {

}

void Terrain::GenerateWorld() {
    std::cout << "TERRAIN : Starting Generation" << std::endl;

    int TotalWidthBlocs = (int)(1920 / BLOCK_SIZE);
    float HeigthAmplitude = (WORLD_HEIGHT_MAX - WORLD_HEIGHT_MIN) / 2;

    std::cout << "TERRAIN : " << TotalWidthBlocs << " total blocks in queue" << std::endl;

    for (int x = 0; x < 1920; x+= BLOCK_SIZE) {
        // Going through width (x coordinates);

        float x_float = static_cast<float>(x);
        float localNoise = noise.GetNoise(x_float, 0.0f); // Between -1 and 1

        float localNoiseNormal = (localNoise + 1.0f) / 2.0f;

        int height = static_cast<int>(WORLD_HEIGHT_MIN + (localNoiseNormal * HeigthAmplitude));

        // clamp height between
        height -= height % BLOCK_SIZE;

        if (height < WORLD_HEIGHT_MIN) height = WORLD_HEIGHT_MIN;
        if (height > WORLD_HEIGHT_MAX) height = WORLD_HEIGHT_MAX;

        for (int y = height; y < 1080; y += BLOCK_SIZE) {
            
            EntityData localBlockData = this->defaultBlockData; // Make a copy of the existing default template.

            localBlockData.Position = Vec2f {static_cast<double>(x), static_cast<double>(y)};

            int salt = rand() % 5; // Random depth factor to choose generation from

            if (y == height) {
                localBlockData.TexturePath = "src/assets/art/blocs/grass.png";
            
            } else if (y > height && y < height + (MINIMUM_DIRT_DEPTH + salt) * BLOCK_SIZE)  { 
                localBlockData.TexturePath = "src/assets/art/blocs/dirt.png";
            
            } else {
                localBlockData.TexturePath = "src/assets/art/blocs/stone.png";
            }

            std::cout << "TERRAIN : Block position : X (" << x << ") / Y(" << y << ")" << std::endl;

            this->entityLoader->CreateEntity(localBlockData);
        }
    }
}