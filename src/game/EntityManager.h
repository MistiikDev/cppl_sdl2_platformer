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
        
        std::unique_ptr<Entity> CreateEntity(EntityData& entityData);
        std::unique_ptr<Player> CreatePlayer(EntityData& entityData);

        void UpdateEntities(float deltaTime);
        void ClearEntities();

        void Quit();

        std::vector<std::unique_ptr<Entity>>& GetActiveEntities() { return activeEntities; };
    
    private:
        Game* currentGameInstance;
        std::vector<std::unique_ptr<Entity>> activeEntities; // Textures to be rendered;
};


#endif