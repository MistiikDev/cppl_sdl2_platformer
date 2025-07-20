#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <SDL2/SDL.h>
#include "EntityData.h"

class Game;
class Entity;
class Player;

class EntityManager {
    public:
        EntityManager(SDL_Renderer* activeRenderer): activeRenderer(activeRenderer) {};
        
        Entity* CreateEntity(Game* currentGameInstance, EntityData& entityData);
        Player* CreatePlayer(Game* currentGameInstance, EntityData& entityData);

        void UpdateEntities(float deltaTime);
        void ClearEntities();

        std::vector<Entity*>& GetActiveEntities() { return activeEntities; };
    
    private:
        std::vector<Entity*> activeEntities; // Textures to be rendered;
        SDL_Renderer* activeRenderer;

        SDL_Texture* LoadTexture(const char* textureFilePath);
};


#endif