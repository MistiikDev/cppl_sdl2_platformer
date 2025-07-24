#include "EntityManager.h"
#include "Entity.h"          
#include "Terrain.h"

Terrain::Terrain() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.003f); // Hardcoded for now;
    noise.SetSeed(static_cast<int>(time(NULL)));

    std::cout << "TERRAIN : Generation ready" << std::endl;
}

void Terrain::ClearWorld() {

}

void Terrain::GenerateWorld() {
    std::cout << "TERRAIN : Starting Generation" << std::endl;

    int TotalWidthBlocs = (int)(1920 / BLOCK_SIZE);
    float HeigthAmplitude = (WORLD_HEIGHT_MAX - WORLD_HEIGHT_MIN) / 2;

    std::cout << "TERRAIN : " << TotalWidthBlocs << " total blocks in queue" << std::endl;

    
}