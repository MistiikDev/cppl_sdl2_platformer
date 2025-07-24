#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
    public:
        static void Init(SDL_Renderer* Renderer);

        static std::shared_ptr<SDL_Texture> LoadTexture(const std::string& TexturePath);
        static std::shared_ptr<SDL_Texture> GetTexture(std::string& TexturePath);
        static void QueryTexture(std::shared_ptr<SDL_Texture> texture, int *w, int *h);

        static void Quit();
    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures;
        static SDL_Renderer* Renderer;

        static void Clear();
};