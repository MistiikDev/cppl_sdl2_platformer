#include "EntityManager.h"
#include "Entity.h"          
#include "Terrain.h"

#include "ChunkManager.h"

Terrain::Terrain() {
    std::cout << "TERRAIN : Generation ready" << std::endl;
}

void Terrain::GenerateWorld() {
    std::cout << "TERRAIN : Starting Generation" << std::endl;
    this->isGenerating = true;
}

void Terrain::Update(const Vec2f& playerInitialPosition) {
    if (!(playerInitialPosition == Vec2f::zero)) {
        ChunkManager::UpdateTerrain(this->entityLoader, playerInitialPosition);
    } else {
        if (!this->isGenerating) return;
        if (!this->entityLoader || !this->entityLoader->localPlayer) return;

        ChunkManager::UpdateTerrain(this->entityLoader, Vec2f::zero);
    }
}