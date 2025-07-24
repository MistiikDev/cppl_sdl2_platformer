#include "EntityManager.h"

EntityManager::EntityManager(Game* currentGameInstance) {
    this->currentGameInstance = currentGameInstance;
}

std::shared_ptr<Entity> EntityManager::CreateEntity(EntityData& entityData) {
    std::shared_ptr<SDL_Texture> entity_texture = TextureManager::LoadTexture(entityData.TexturePath);

    std::shared_ptr<Entity> entity_ptr = std::make_shared<Entity>(
        this->currentGameInstance, 
        entityData, 
        entity_texture
    );

    entity_ptr->Awake();
    activeEntities.push_back(entity_ptr);

    return entity_ptr;
};

std::shared_ptr<Player> EntityManager::CreatePlayer(EntityData& entityData) {
    if (this->localPlayer != nullptr) {
        std::cerr << "[ERR] ENTITY MANAGER : Attempted to create more that 1 Local Player" << std::endl;
        return nullptr;
    }

    std::shared_ptr<SDL_Texture> player_texture = TextureManager::LoadTexture(entityData.TexturePath);
    std::shared_ptr<Player> player_ptr = std::make_shared<Player>(
        currentGameInstance, 
        entityData,
        player_texture
    );

    player_ptr->Awake();
    activeEntities.push_back(player_ptr);

    this->localPlayer = player_ptr;

    return player_ptr;
};

void EntityManager::UpdateEntities(float deltaTime) {
    for (auto& entity : this->activeEntities) {
        Entity* e = entity.get();

        if (!e->Anchored) {
            Physics::UpdatePositionInWorld(e, deltaTime); // Gravity work..
        }

        e->Update(deltaTime);

        // Set position according to player moving
        if (this->localPlayer != nullptr && e != this->localPlayer.get()) {
            Vec2f currentPosition = e->GetPosition();
            Vec2f playerVelocity = this->localPlayer->GetVelocity();
            Vec2f entityPosition = currentPosition + ((Vec2f::zero - playerVelocity) * deltaTime);
            entityPosition.y = currentPosition.y;

            e->SetPosition(entityPosition, false);
        }
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