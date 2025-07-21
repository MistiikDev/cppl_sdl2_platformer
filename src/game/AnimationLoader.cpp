#include "AnimationLoader.h"

std::map<std::string, std::vector<AnimationData>> AnimationLoader::AnimationPackage;

void AnimationLoader::Init() {
    std::cout << "ANIMATION : Animation Loader Initialized" << std::endl;
}

void AnimationLoader::LoadAnimDefinitions(const std::string &path) {
    std::cout << "ANIMATION : Loading animation data from : " << path << std::endl;

    std::ifstream file(path);
    nlohmann::json j;
    file >> j;

    for (auto &[className, animationJson] : j.items()) {

        AnimationLoader::AnimationPackage[std::string(className)] = std::vector<AnimationData>();

        for (auto &[animationName, animationJsonData] : animationJson.items())
        {
            AnimationData data;

            data.Name = animationJsonData["name"];
            data.duration = animationJsonData["duration"];
            data.looped = animationJsonData["looped"];
            data.framePaths = animationJsonData["frames"].get<std::vector<std::string>>();

            AnimationLoader::AnimationPackage[std::string(className)].push_back(data);
        } 
    }
}

std::unique_ptr<AnimationTrack> AnimationLoader::LoadTrackFromDefinition(const AnimationData &animationData, SDL_Renderer *renderer, Entity *e)
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

    std::cout << "ANIMATION : Done loading animation track : " << track->animation.Name << std::endl;

    return track;
}