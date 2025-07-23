#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <SDL2/SDL.h>
#include <unordered_map>
#include "EntityData.h"
#include "TextureManager.h"

class Game;
class Entity;
class Player;

class EntityManager {
    public:
        EntityManager();
        
        Entity* CreateEntity(Game* currentGameInstance, EntityData& entityData);
        Player* CreatePlayer(Game* currentGameInstance, EntityData& entityData);

        void UpdateEntities(float deltaTime);
        void ClearEntities();

        void Quit();

        std::vector<Entity*>& GetActiveEntities() { return activeEntities; };
    
    private:
        std::vector<Entity*> activeEntities; // Textures to be rendered;
};


#endif