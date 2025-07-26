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
    this->currentEntityManager->ClearEntities();
    this->CurrentLevel = Level();

    std::cout << "LEVEL : Unloaded Active Level (IF ANY)" << std::endl;

    return true;
}

void LevelManager::LoadLevelGeometry(const Vec2f& playerInitialPosition) {
    std::cout << "LEVEL : Loading Level Geometry" << std::endl;

    this->terrainGenerator->SetEntityLoader(this->currentEntityManager);
    this->terrainGenerator->GenerateWorld();
    this->terrainGenerator->Update(playerInitialPosition);
};

void LevelManager::UpdateTerrain() {
    this->terrainGenerator->Update(Vec2f::zero);
}

bool LevelManager::LoadLevel(const std::string& levelName) {
    if (!this->UnloadCurrentLevel()) {
        std::cerr << "Could not unload current level!" << std::endl;
        return false;
    }

    std::string LevelPath = this->GetLevelPath(levelName);
    std::ifstream f(LevelPath);

    EntityData playerData;
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
        entity.fixedToCamera = e["fixedToCamera"];

        entity.RenderingGroup = e["RenderingGroup"];
        entity.RenderingLayer = e.value("RenderLayer", 0);

        CurrentLevel.Entities.push_back(entity);

        if (entity.Class == "Player") {
            playerData = entity; // Dont spawn player YET;
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
    
    this->LoadLevelGeometry(playerData.Position);
    this->currentEntityManager->CreatePlayer(playerData);

    std::cout << "LEVEL: Loaded level metadata from path: " << LevelPath << std::endl;

    return true;
}