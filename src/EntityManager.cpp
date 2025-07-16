#include "Entity.h"
#include "Player.h"

#include "EntityManager.h"

SDL_Texture* EntityManager::LoadTexture(const char* textureFilePath) {
    SDL_Texture *texture = IMG_LoadTexture(this->activeRenderer, textureFilePath);
    
    if (!texture) {
        std::cerr << "Texture load failed: " << IMG_GetError() << std::endl;
    }

    return texture;
}

void EntityManager::CreateEntity(Game* currentGameInstance, Vec2f &position, const char* textureFilePath) {
    SDL_Texture *texture = this->LoadTexture(textureFilePath);
    Entity* e = new Entity {currentGameInstance, position, texture};

    activeEntities.push_back(e);
};

void EntityManager::CreatePlayer(Game* currentGameInstance, Vec2f &position, const char* textureFilePath) {
    SDL_Texture *texture = this->LoadTexture(textureFilePath);
    Player* p = new Player {currentGameInstance, position, texture};

    activeEntities.push_back(p);
};

void EntityManager::AwakeEntities() {
    for (Entity* e : this->activeEntities) {
        e->Awake();
    }
}

void EntityManager::UpdateEntities(float deltaTime) {
    for (Entity* e : this->activeEntities) {
        e->Update(deltaTime);
    }
}

void EntityManager::ClearEntities() {
    for (Entity* e: this->activeEntities) {
        delete e;
    }

    this->activeEntities.clear();
}