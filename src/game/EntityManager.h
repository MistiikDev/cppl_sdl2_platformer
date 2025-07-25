#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>

#include "Entity.h"
#include "Player.h"
#include "EntityData.h"

#include "Physics.h"

class Game;

class EntityManager {
    public:
        EntityManager(Game* currentGameInstance);
        
        std::shared_ptr<Entity> CreateEntity(EntityData& entityData);
        std::shared_ptr<Player> CreatePlayer(EntityData& entityData);

        void UpdateEntities(float deltaTime);
        void ClearEntity(std::shared_ptr<Entity>& entity);
        
        void LoadEntity(EntityData& entityData);
        void UnloadEntity(EntityData& entityData);

        void ClearEntities();
        void Quit();

        std::shared_ptr<Player> localPlayer;
        std::vector<std::shared_ptr<Entity>>& GetActiveEntities() { return activeEntities; };
    
    private:
        Game* currentGameInstance;
        std::vector<std::shared_ptr<Entity>> activeEntities; // Textures to be rendered;
};


#endif