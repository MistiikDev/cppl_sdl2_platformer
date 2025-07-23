#include "TextureManager.h"

SDL_Renderer* TextureManager::Renderer;

void TextureManager::Init(SDL_Renderer* Renderer) {
    if (Renderer == nullptr) {
        std::cerr << "[ERR] TEXTURE : Renderer PTR is NULL!" << std::endl;
        return;
    }

    TextureManager::Renderer = Renderer;

    std::cout << "TEXTURE : Texture Manager initialized " << std::endl;
}

SDL_Texture* TextureManager::LoadTexture(const std::string& TexturePath) {
    if (TextureManager::Renderer == nullptr) {
        std::cerr << "[ERR] TEXTURE : Renderer PTR is NULL!" << std::endl;
        return;
    }

    auto it = textures.find(TexturePath);

    if (it != textures.end()) {
        return it->second;
    }

    SDL_Texture *texture = IMG_LoadTexture(TextureManager::Renderer, TexturePath.c_str());

    if (!texture) {
        std::cerr << "TEXTURE : Texture Loading Failed: " << IMG_GetError() << std::endl;
    }

    textures[TexturePath] = texture;

    return texture;
}

void TextureManager::QueryTexture(SDL_Texture* texture, int *w, int *h) {
    SDL_QueryTexture(texture, NULL, NULL, w, h);
}