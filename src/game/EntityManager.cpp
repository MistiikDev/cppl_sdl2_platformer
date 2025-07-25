#include "EntityManager.h"
#include "Game.h"

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

    // By default, camera subject

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
    // Vec2f playerPrevPos;
    // Vec2f playerNewPos;

    for (auto& entity : this->activeEntities) {
        Entity* e = entity.get();

        if (!e->Anchored) {
            Physics::UpdatePositionInWorld(e, deltaTime);
        }

        e->Update(deltaTime);
    }

    Physics::CheckEntityCollisions(this->activeEntities);

    if (this->localPlayer != nullptr) {
        this->currentGameInstance->SetCameraTarget(this->localPlayer->GetPosition());
    }

    // if (this->localPlayer != nullptr) {
    //     playerNewPos = this->localPlayer->GetPosition();

    //     Vec2f displacement = playerNewPos - playerPrevPos;
    //     this->localPlayer->RealWorldPosition = this->localPlayer->RealWorldPosition + displacement;

    //     playerPrevPos.y = playerNewPos.y; // Let the player update its y position (jumps...)
    //     displacement.y = 0; // Lock player X-Axis
        
    //     this->localPlayer->SetPosition(playerPrevPos, false);

    //     for (auto& entity : this->activeEntities) {
    //         Entity* e = entity.get();
    //         if (e == this->localPlayer.get() || !e->isScrollable) continue;

    //         Vec2f centeredOffsetPosition = e->GetPosition() - (displacement); // Offset every other entity by the opposite of deltaPlayer displacement
            
    //         e->SetPosition(centeredOffsetPosition, false);
    //     }
    // }
}


void EntityManager::ClearEntity(std::shared_ptr<Entity>& entity) {
    auto it = std::find(this->activeEntities.begin(), this->activeEntities.end(), entity);

    if (it == this->activeEntities.end()) {
        std::cout << "[ERR] ENTITY MANAGER : Entity to Delete is not registered! " << std::endl;
        return;
    }

    this->activeEntities.erase(it);
    //std::cout << "ENTITY MANAGER : Successfully deleted Entity @ " << entity << std::endl;
}

void EntityManager::ClearEntities() {
    int size = this->activeEntities.size();
    this->activeEntities.clear();

    std::cout << "ENTITY MANAGER : Cleared " << size << " entities" << std::endl;
}

void EntityManager::Quit() {
    
}