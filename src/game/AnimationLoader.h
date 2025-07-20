#ifndef ANIMATION_LOADER_H
#define ANIMATION_LOADER_H

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "AnimationData.h"
#include "AnimationTrack.h"

class AnimationLoader {
    public:
        static std::vector<AnimationData> LoadAnimDefinitions(const std::string& path, const std::string& className);
        static std::unique_ptr<AnimationTrack> LoadTrackFromDefinition(AnimationData& animationData, SDL_Renderer* renderer, Entity* e);
};

#endif