#include "TextureManager.h"

SDL_Renderer* TextureManager::Renderer = nullptr;
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> TextureManager::textures;

void TextureManager::Init(SDL_Renderer* rendererPtr) {    
    if (rendererPtr == nullptr) {
        std::cerr << "[ERR] TEXTURE INIT : Renderer PTR is NULL!" << std::endl;
        return;
    }

    TextureManager::Renderer = rendererPtr;

    if (!(IMG_Init(IMG_INIT_PNG && IMG_INIT_JPG) & IMG_INIT_PNG)) {
        std::cerr << "[ERR] SDL_image failed to initialize PNG support: " << IMG_GetError() << std::endl;
        return;
    }

    const char* best = new char ('1');

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, best);

    std::cout << "TEXTURE : SDL_image / Texture Manager initialized " << std::endl;
}

std::shared_ptr<SDL_Texture> TextureManager::LoadTexture(const std::string& TexturePath) {
    //std::cout << "TEXTURE : Loading Texture : " << TexturePath << std::endl;
    
    if (TextureManager::Renderer == nullptr) {
        std::cerr << "[ERR] TEXTURE : Renderer PTR is NULL!" << std::endl;
        
        return nullptr;
    }

    auto it = textures.find(TexturePath);

    if (it != textures.end()) {
        //std::cout << "TEXTURE : Culling texture from cache.." << std::endl;
        return it->second;
    }

    SDL_Texture *texture = IMG_LoadTexture(TextureManager::Renderer, TexturePath.c_str());

    if (!texture) {
        std::cerr << "TEXTURE : Texture Loading Failed: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetTextureScaleMode(texture, SDL_ScaleModeBest);

    TextureManager::textures[TexturePath] = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);;

    //std::cout << "TEXTURE : Loaded texture : " << TexturePath << std::endl;

    return TextureManager::textures[TexturePath];
}

void TextureManager::QueryTexture(std::shared_ptr<SDL_Texture> texture, int *w, int *h) {
    SDL_QueryTexture(texture.get(), NULL, NULL, w, h);
}

void TextureManager::Quit() {
    
}