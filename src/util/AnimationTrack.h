#ifndef ANIMATION_TRACK_H
#define ANIMATION_TRACK_H

#include <vector>
#include <memory>
#include <fstream>

#include "nlohmann/json.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "AnimationData.h"

class Entity;
struct AnimationTrack {
    AnimationTrack(const AnimationData& animationData, Entity* e);

    AnimationData animation;
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

#endif