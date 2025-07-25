#include "Chunk.h"
#include "ChunkManager.h"

std::map<int, Chunk*> ChunkManager::Chunks;

void ChunkManager::UpdateTerrain(EntityManager* entityLoader, const Vec2f& playerInitialPosition) {    
    Vec2f playerPosition = (!(playerInitialPosition == Vec2f::zero) ? playerInitialPosition : entityLoader->localPlayer->GetPosition());

    int playerChunkX = playerPosition.x / chunkWidth; // Chunk 0 starts at (X: 0, Y: 0), Chunk 1 starts at (X: ChunkWidth, Y: 0)....

    for (int radius = -CHUNK_RENDER_DISTANCE; radius < CHUNK_RENDER_DISTANCE; radius++) {
        int chunkID = playerChunkX + radius;

        if (ChunkManager::Chunks.find(chunkID) == ChunkManager::Chunks.end()) {
            Chunk* chunk = new Chunk();

            int chunkPosition = chunkID * chunkWidth;

            std::cout << "CHUNK POSITION : @ " << chunkPosition << std::endl;

            chunk->Position = Vec2f {static_cast<double>(chunkPosition), 0};
            chunk->Generate();

            ChunkManager::Chunks[chunkID] = chunk;
        }

        Chunk* chunk = ChunkManager::Chunks[chunkID];
        
        if (chunk->isVisibleToPlayer(playerPosition)) {
            if (!chunk->isLoaded) {
                std::cout << "CHUNK MANAGER : Loading Chunk : " << chunkID << std::endl;
                chunk->Load(entityLoader);
            }

        } else {
            chunk->UnloadEntities(entityLoader);
        }
    }
}