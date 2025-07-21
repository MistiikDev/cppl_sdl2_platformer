#include "EntityManager.h"
#include "LevelManager.h"
#include "AudioManager.h"

std::string LevelManager::GetLevelPath(const std::string& levelName) {
    std::string path = "src/assets/data/" + levelName + ".json";

    return path;
}

bool LevelManager::UnloadCurrentLevel() {
    std::cout << "LEVEL: Unloading active level" << std::endl;
    
    this->currentEntityManager->ClearEntities();
    this->CurrentLevel = Level();

    return true;
}

bool LevelManager::LoadLevel(Game* gameInstance, const std::string& levelName) {
    if (!this->UnloadCurrentLevel()) {
        std::cerr << "Could not unload current level!" << std::endl;
        return false;
    }

    std::string LevelPath = this->GetLevelPath(levelName);
    std::ifstream f(LevelPath);

    if (!f.is_open()) {
        std::cerr << "Failed to open level file: " << LevelPath << std::endl;
        return false;
    }

    json levelData;

    try {
        f >> levelData;
    } catch (const json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
    
    CurrentLevel.Name = levelData["Name"];
    CurrentLevel.Version = levelData["Version"];
    CurrentLevel.Data.Entities = {};

    auto& entities = levelData["Data"]["Entities"];
    auto& musics = levelData["Data"]["Music"];

    for (auto& e : entities) {
        EntityData entity;

        entity.Name = e["Name"];
        entity.Class = e["Class"];
        entity.Position = Vec2f(e["Position"][0], e["Position"][1]);
        entity.Mass = e["Mass"];
        entity.Anchored = e["Anchored"];
        entity.CanCollide = e["CanCollide"];
        entity.TexturePath = e["TexturePath"];

        entity.RenderingGroup = e["RenderingGroup"];

        if (e.contains("RenderLayer")) {
            entity.RenderingLayer = e["RenderLayer"];
        } else {
            entity.RenderingLayer = 0;
        }

        std::cout << "LEVEL: Loading entity : " << entity.Name << std::endl;

        CurrentLevel.Data.Entities.push_back(entity);

        if (entity.Class == "Player") {
            this->currentEntityManager->CreatePlayer(gameInstance, entity);
        } else if (entity.Class == "Entity") {
            this->currentEntityManager->CreateEntity(gameInstance, entity);
        }
    }

    for (auto& music : musics) {
        std::string musicName = music["Name"];
        std::cout << musicName;
        float musicVolume = music["Volume"];

        AudioManager::PlayAudio(musicName, musicVolume);
    }

    return true;
}