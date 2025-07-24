#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "Vec2f.h"
#include "EntityData.h"

using json = nlohmann::json;

struct Level {
    std::string Name;
    int Version;

    std::vector<EntityData> Entities;
};

class EntityManager;
class Terrain;

class LevelManager {
    public:
        LevelManager(EntityManager* currentEntityManager);

        std::string GetLevelPath(const std::string& levelName);

        void LoadLevelGeometry();
        bool LoadLevel(const std::string& LevelName);
        
        bool UnloadCurrentLevel();
    private:
        EntityManager* currentEntityManager;
        Terrain* terrainGenerator;
        Level CurrentLevel;
};

#endif