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

Entity* EntityManager::CreateEntity(Game* currentGameInstance, EntityData& entityData) {
    SDL_Texture *texture = this->LoadTexture(entityData.TexturePath.c_str());

    Entity* e = new Entity { 
        currentGameInstance, 
        entityData, 
        texture
    };

    activeEntities.push_back(e);

    return e;
};

Player* EntityManager::CreatePlayer(Game* currentGameInstance, EntityData& entityData) {
    SDL_Texture *texture = this->LoadTexture(entityData.TexturePath.c_str());
    
    Player* p = new Player { 
        currentGameInstance, 
        entityData, 
        texture
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
            Physics::UpdatePositionInWorld(e, deltaTime); // Gravity work..
        }

        e->Update(deltaTime);
    }
    
    Physics::CheckEntityCollisions(this->activeEntities);
}

void EntityManager::ClearEntities() {
    for (Entity* e: this->activeEntities) {
        delete e;
    }

    this->activeEntities.clear();
}