#include "EntityManager.h"

void EntityManager::CreateEntity(Vec2f &position, const char* textureFilePath) {
    SDL_Texture *texture = IMG_LoadTexture(this->activeRenderer, textureFilePath);
    
    if (!texture) {
        std::cerr << "Texture load failed: " << IMG_GetError() << std::endl;
    }
    
    Entity* e = new Entity{position, texture};

    activeEntities.push_back(e);
};