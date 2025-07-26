#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <iostream>
#include <map>

#define CHUNK_RENDER_DISTANCE 3

class Chunk;
class ChunkManager {
    public:
        static void UpdateTerrain(EntityManager* entityLoader, const Vec2f& playerInitialPosition);
    private:
        static std::map<int, Chunk*> Chunks;
};

#endif