#ifndef ANIMATION_H
#define ANIMATION_H 

#include <vector>
#include <map>
#include <memory>
#include <fstream>

#include "nlohmann/json.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity;

struct AnimationData {
    float duration;
    bool looped;
    
    std::string Name;
    std::vector<std::string> framePaths;
};

struct AnimationTrack {
    AnimationTrack(AnimationData& animationData, Entity* e);

    AnimationData& animation;
    Entity* targetEntity;

    std::vector<std::shared_ptr<SDL_Texture>> frames;

    int currentFrame;
    float elapsedTime;

    bool canPlay = true; // internal

    bool isLooping;
    bool isFinished;
    bool isPlaying;

    float speed;

    void Play(float speed);
    void Stop();

    void Clear();

    void Update(float deltaTime);
};

class AnimationLoader {
    public:
    
    static std::vector<AnimationData> LoadAnimDefinitions(const std::string& path, const std::string& className) {
        std::vector<AnimationData> animationPak;

        std::ifstream file(path);
        nlohmann::json j;
        file >> j;

        auto& animationJson = j[className];

        for (auto& [animationName, animationJsonData] : animationJson.items()) {
            AnimationData data;

            data.Name = animationJsonData["name"];
            data.duration = animationJsonData["duration"];
            data.looped = animationJsonData["looped"];
            data.framePaths = animationJsonData["frames"].get<std::vector<std::string>>();

            animationPak.push_back(data);
        }

        return animationPak;
    }

    static std::unique_ptr<AnimationTrack> LoadTrackFromDefinition(AnimationData& animationData, SDL_Renderer* renderer, Entity* e) {
        std::unique_ptr<AnimationTrack> track = std::make_unique<AnimationTrack>(animationData, e);
        
        track->animation = animationData;
        track->targetEntity = e;
        
        for (const auto& path : animationData.framePaths) {
            SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());

            if (!tex) {
                std::cerr << "Failed to load texture: " << path << " | " << IMG_GetError() << std::endl;
                continue;
            }

            track->frames.push_back(std::shared_ptr<SDL_Texture>(tex, SDL_DestroyTexture));
        }

        return track;
    }
};

#endif