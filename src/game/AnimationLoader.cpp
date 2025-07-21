#include "AnimationLoader.h"

std::vector<AnimationData> AnimationLoader::LoadAnimDefinitions(const std::string &path, const std::string &className)
{
    std::vector<AnimationData> animationPak;

    std::ifstream file(path);
    nlohmann::json j;
    file >> j;

    auto &animationJson = j[className];

    for (auto &[animationName, animationJsonData] : animationJson.items())
    {
        AnimationData data;

        data.Name = animationJsonData["name"];
        data.duration = animationJsonData["duration"];
        data.looped = animationJsonData["looped"];
        data.framePaths = animationJsonData["frames"].get<std::vector<std::string>>();

        animationPak.push_back(data);
    }

    return animationPak;
}

std::unique_ptr<AnimationTrack> AnimationLoader::LoadTrackFromDefinition(AnimationData &animationData, SDL_Renderer *renderer, Entity *e)
{
    std::unique_ptr<AnimationTrack> track = std::make_unique<AnimationTrack>(animationData, e);

    track->animation = animationData;
    track->targetEntity = e;

    for (const auto &path : animationData.framePaths)
    {
        SDL_Texture *tex = IMG_LoadTexture(renderer, path.c_str());

        std::cout << "ANIMATION : Loading frame : " << path.c_str() << std::endl;

        if (!tex)
        {
            std::cerr << "Failed to load texture: " << path << " | " << IMG_GetError() << std::endl;
            continue;
        }

        track->frames.push_back(std::shared_ptr<SDL_Texture>(tex, SDL_DestroyTexture));
    }

    return track;
}