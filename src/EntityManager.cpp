#include "Entity.h"
#include "Player.h"
#include "Physics.h"

#include "EntityManager.h"

SDL_Texture* EntityManager::LoadTexture(const char* textureFilePath) {
    SDL_Texture *texture = IMG_LoadTexture(this->activeRenderer, textureFilePath);
    
    if (!texture) {
        std::cerr << "Texture load failed: " << IMG_GetError() << std::endl;
    }

    return texture;
}

Entity* EntityManager::CreateEntity(Game* currentGameInstance, const Vec2f &start_position, const char* textureFilePath, double Mass) {
    SDL_Texture *texture = this->LoadTexture(textureFilePath);
    Entity* e = new Entity { 
        currentGameInstance, 
        start_position, 
        texture, 
        Mass
    };

    activeEntities.push_back(e);

    return e;
};

Player* EntityManager::CreatePlayer(Game* currentGameInstance, const Vec2f &start_position, const char* textureFilePath, double Mass) {
    SDL_Texture *texture = this->LoadTexture(textureFilePath);
    Player* p = new Player { 
        currentGameInstance, 
        start_position, 
        texture, 
        Mass
    };

    activeEntities.push_back(p);

    return p;
};

void EntityManager::AwakeEntities() {
    for (Entity* e : this->activeEntities) {
        e->Awake();
    }
}

void EntityManager::UpdateEntities(float deltaTime) {
    for (Entity* e : this->activeEntities) {

        if (!e->Anchored) {
            Physics::UpdatePositionInWorld(e, deltaTime);
        }

        Physics::CheckEntityCollisions(this->activeEntities);
        e->Update(deltaTime);
    }
}

void EntityManager::ClearEntities() {
    for (Entity* e: this->activeEntities) {
        delete e;
    }

    this->activeEntities.clear();
}