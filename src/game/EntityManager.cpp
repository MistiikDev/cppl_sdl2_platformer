#include "EntityManager.h"

EntityManager::EntityManager(Game* currentGameInstance) {
    this->currentGameInstance = currentGameInstance;
}

std::unique_ptr<Entity> EntityManager::CreateEntity(EntityData& entityData) {
    std::shared_ptr<SDL_Texture> entity_texture = TextureManager::LoadTexture(entityData.TexturePath);

    std::unique_ptr<Entity> entity_ptr = std::make_unique<Entity>(
        this->currentGameInstance, 
        entityData, 
        entity_texture
    );

    entity_ptr->Awake();
    activeEntities.push_back(std::move(entity_ptr));

    return entity_ptr;
};

std::unique_ptr<Player> EntityManager::CreatePlayer(EntityData& entityData) {
    std::shared_ptr<SDL_Texture> player_texture = TextureManager::LoadTexture(entityData.TexturePath);

    std::unique_ptr<Player> player_ptr = std::make_unique<Player>(
        currentGameInstance, 
        entityData,
        player_texture
    );

    player_ptr->Awake();

    activeEntities.push_back(
        std::unique_ptr<Entity>(std::move(player_ptr))
    );

    return player_ptr;
};

void EntityManager::UpdateEntities(float deltaTime) {    
    for (auto& entity : this->activeEntities) {
        Entity* e = entity.get();

        if (!e->Anchored) {
            Physics::UpdatePositionInWorld(e, deltaTime); // Gravity work..
        }

        e->Update(deltaTime);
    }
    
    Physics::CheckEntityCollisions(this->activeEntities);
}

void EntityManager::ClearEntities() {
    int size = this->activeEntities.size();
    this->activeEntities.clear();

    std::cout << "ENTITY MANAGER : Cleared " << size << " entities" << std::endl;
}

void EntityManager::Quit() {
    
}