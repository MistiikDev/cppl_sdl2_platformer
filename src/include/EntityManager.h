#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

class EntityManager {
    public:
        EntityManager(SDL_Renderer* activeRenderer): activeRenderer(activeRenderer) {};
        
        void CreateEntity(Vec2f& position, const char* textureFilePath);

        std::vector<Entity*> GetActiveEntities() { return activeEntities; };
    
        private:
        std::vector<Entity*> activeEntities; // Textures to be rendered;
        SDL_Renderer* activeRenderer;
};


#endif