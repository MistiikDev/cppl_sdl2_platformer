#include "Chunk.h"
#include "ChunkManager.h"

std::map<int, Chunk*> ChunkManager::Chunks;

int Seed = time(NULL);

void ChunkManager::UpdateTerrain(EntityManager* entityLoader, const Vec2f& playerInitialPosition) {    
    Vec2f playerPosition = (!(playerInitialPosition == Vec2f::zero) ? playerInitialPosition : entityLoader->localPlayer->GetPosition());
    
    int playerChunkX = static_cast<int>(std::floor(playerPosition.x / static_cast<double>(chunkWidth))); // Chunk 0 starts at (X: 0, Y: 0), Chunk 1 starts at (X: ChunkWidth, Y: 0)....

    for (int radius = -CHUNK_RENDER_DISTANCE; radius <= CHUNK_RENDER_DISTANCE; radius++) {
        int chunkID = playerChunkX + radius;

        if (ChunkManager::Chunks.find(chunkID) == ChunkManager::Chunks.end()) {
            Chunk* chunk = new Chunk();

            std::cout << "Creating chunk " << chunkID << " at world X = " << chunkID * chunkWidth << std::endl;

            int chunkPosition = chunkID * chunkWidth;
            
            chunk->Position = Vec2f {static_cast<double>(chunkPosition), 0};

            chunk->SetSeed(Seed);
            chunk->Generate();

            chunk->Position.print();

            ChunkManager::Chunks[chunkID] = chunk;
        }
    }    
    
    std::vector<int> chunksToUnload;
    std::vector<int> chunksToLoad;

    for (auto& [chunkID, chunk] : Chunks) {
        bool visible = playerChunkX - CHUNK_RENDER_DISTANCE <= chunkID &&  playerChunkX + CHUNK_RENDER_DISTANCE >= chunkID;
        
        if (visible && !chunk->isLoaded) {
            chunksToLoad.push_back(chunkID);

        } else if (!visible && chunk->isLoaded) {
            chunksToUnload.push_back(chunkID);

        }
    }

    for (int chunkID : chunksToUnload) {
        Chunks[chunkID]->UnloadEntities(entityLoader);
        
        std::cout << "UNLOADED chunk " << chunkID << "\n";
    }

    for (int chunkID : chunksToLoad) {
        Chunks[chunkID]->Load(entityLoader);
        
        std::cout << "LOADED chunk " << chunkID << "\n";
    }
}