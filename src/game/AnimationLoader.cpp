#include "AnimationLoader.h"

std::map<std::string, std::vector<AnimationData>> AnimationLoader::AnimationPackage;
SDL_Renderer* AnimationLoader::Renderer;

void AnimationLoader::Init(SDL_Renderer* Renderer) {
    if (Renderer == nullptr) {
        std::cerr << "[ERR] ANIMATION : Renderer PTR is NULL!" << std::endl;
        return;
    }

    AnimationLoader::Renderer = Renderer;

    std::cout << "ANIMATION : Animation Loader Initialized" << std::endl;
}

void AnimationLoader::LoadAnimDefinitions(const std::string &path) {
    //std::cout << "ANIMATION : Loading animation data from : " << path << std::endl;

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

std::unique_ptr<AnimationTrack> AnimationLoader::LoadTrackFromDefinition(const AnimationData &animationData, Entity *e)
{
    std::unique_ptr<AnimationTrack> track = std::make_unique<AnimationTrack>(animationData, e);

    track->animation = animationData;
    track->targetEntity = e;

    for (const std::string path : animationData.framePaths)
    {
        std::shared_ptr<SDL_Texture> frame_texture = TextureManager::LoadTexture(path.c_str());

        //std::cout << "ANIMATION : Loading frame : " << path.c_str() << std::endl;

        if (!frame_texture)
        {
            std::cerr << "Failed to load texture: " << path << " | " << IMG_GetError() << std::endl;
            continue;
        }

        track->frames.push_back(frame_texture);
    }

    //std::cout << "ANIMATION : Done loading animation track : " << track->animation.Name << std::endl;

    return track;
}