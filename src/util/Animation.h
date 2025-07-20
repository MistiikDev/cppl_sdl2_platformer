#ifndef ANIMATION_H
#define ANIMATION_H 

#include <vector>
#include <thread>
#include <map>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity;

struct Animation {
    float duration;
    bool looped;
    
    std::string Name;
    
    std::vector<std::shared_ptr<SDL_Texture>> frames;
};

struct AnimationTrack {
    AnimationTrack(Animation& animationData, Entity* e);

    Animation& animation;
    Entity* targetEntity;

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