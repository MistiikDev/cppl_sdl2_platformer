#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "Vec2f.h"
#include "EntityData.h"

using json = nlohmann::json;

struct LevelData {
    std::vector<EntityData> Entities;
};

struct Level {
    std::string Name;
    int Version;
    LevelData Data;
};

class Game;
class EntityManager;

class LevelManager {
    public:
        LevelManager(EntityManager* currentEntityManager): currentEntityManager(currentEntityManager) {};

        std::string GetLevelPath(const std::string& levelName);

        bool LoadLevel(Game* currentGameInstance, const std::string& LevelName);
        bool UnloadCurrentLevel();
    private:
        EntityManager* currentEntityManager;
        Level CurrentLevel;
};

#endif