#ifndef ANIMATION_H
#define ANIMATION_H 

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct AnimationData {
    int frameCount;
    float duration;

    std::map<SDL_Rect&, SDL_Texture*> frames; // Rendering bounding box -> Texture;
};

struct Animation {
    Animation(AnimationData& animationData): animationData(animationData) {};

    AnimationData& animationData;

    int currentFrame;
    float elapsedTime;

    bool isLooping;
    bool isFinished;

    void Play(float speed = 1.0f);
    void Stop();
    void Pause();
};

#endif