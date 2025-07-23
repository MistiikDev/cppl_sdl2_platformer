#ifndef ANIMATION_LOADER_H
#define ANIMATION_LOADER_H

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"

#include "AnimationData.h"
#include "AnimationTrack.h"

class AnimationLoader {
    public:
        static void Init(SDL_Renderer* Renderer);
        static std::map<std::string, std::vector<AnimationData>> AnimationPackage;

        static void LoadAnimDefinitions(const std::string& path);
        static std::unique_ptr<AnimationTrack> LoadTrackFromDefinition(const AnimationData &animationData, Entity *e);

    private:
        static SDL_Renderer* Renderer;

        static void Clear();
};

#endif