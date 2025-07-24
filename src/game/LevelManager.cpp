#include "AudioManager.h"
#include "Entity.h"         
#include "Player.h"     
#include "Terrain.h"
#include "EntityManager.h"   

#include "LevelManager.h"

LevelManager::LevelManager(EntityManager* currentEntityManager): currentEntityManager(currentEntityManager) {
    terrainGenerator = new Terrain();
}

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

void LevelManager::LoadLevelGeometry() {
    std::cout << "LEVEL : Loading Level Geometry" << std::endl;

    this->terrainGenerator->SetEntityLoader(this->currentEntityManager);
    this->terrainGenerator->GenerateWorld();
};

bool LevelManager::LoadLevel(const std::string& levelName) {
    if (!this->UnloadCurrentLevel()) {
        std::cerr << "Could not unload current level!" << std::endl;
        return false;
    }

    std::cout << "LEVEL : Unloaded Active Level (IF ANY)" << std::endl;

    this->LoadLevelGeometry();

    std::string LevelPath = this->GetLevelPath(levelName);
    std::ifstream f(LevelPath);

    std::cout << "LEVEL: Loading level from path: " << LevelPath << std::endl;

    json levelData;

    if (!f.is_open()) {
        std::cerr << "Failed to open level file: " << LevelPath << std::endl;
        return false;
    }

    try {
        f >> levelData;
    } catch (const json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
    
    CurrentLevel.Name = levelData["Name"];
    CurrentLevel.Version = levelData["Version"];
    CurrentLevel.Entities = {};

    auto& entities = levelData["Data"]["Entities"];
    auto& musics = levelData["Data"]["Music"];

    for (auto& e : entities) {
        EntityData entity;

        std::cout << "LEVEL: Loading entity : " << entity.Name << std::endl;

        entity.Name = e["Name"];
        entity.Class = e["Class"];
        entity.Position = Vec2f(e["Position"][0], e["Position"][1]);
        entity.Mass = e["Mass"];
        entity.Anchored = e["Anchored"];
        entity.CanCollide = e["CanCollide"];
        entity.TexturePath = e["TexturePath"];

        entity.RenderingGroup = e["RenderingGroup"];
        entity.RenderingLayer = entity.RenderingLayer = e.value("RenderLayer", 0);

        CurrentLevel.Entities.push_back(entity);

        if (entity.Class == "Player") {
            this->currentEntityManager->CreatePlayer(entity);
        } else if (entity.Class == "Entity") {
            this->currentEntityManager->CreateEntity(entity);
        } else {
            std::cerr << "Unknown entity class: " << entity.Class << std::endl;
        }
    }

    for (auto& music : musics) {
        float musicVolume = music["Volume"];
        std::string musicName = music["Name"];

        AudioManager::PlayAudio(musicName, musicVolume);
    }

    return true;
}