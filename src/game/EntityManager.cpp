#include "Physics.h"
#include "Entity.h"
#include "Player.h"

#include "EntityManager.h"

Entity* EntityManager::CreateEntity(Game* currentGameInstance, EntityData& entityData) {
    SDL_Texture *entity_texture = TextureManager::LoadTexture(entityData.TexturePath);
    
    Entity* e = new Entity {
        currentGameInstance, 
        entityData, 
        entity_texture
    };

    e->Awake();
    activeEntities.push_back(e);

    return e;
};

Player* EntityManager::CreatePlayer(Game* currentGameInstance, EntityData& entityData) {
    SDL_Texture *player_texture = TextureManager::LoadTexture(entityData.TexturePath);
    Player* p = new Player {
        currentGameInstance, 
        entityData, 
        player_texture
    };

    p->Awake();
    activeEntities.push_back(p);

    return p;
};

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