#include "Animator.h"
#include <iostream>

void Animator::Play(std::string& AnimationName, float speed) {
    if (this->loadedAnimation.count(AnimationName) == 0 || this->loadedAnimation[AnimationName]->isPlaying) {
        return;
    }

    this->loadedAnimation[AnimationName]->Play(speed);
}

void Animator::Stop(std::string& AnimationName) {
    if (this->loadedAnimation.count(AnimationName) == 0 || this->loadedAnimation[AnimationName]->isFinished) {
        return;
    }

    this->loadedAnimation[AnimationName]->Stop();
}

void Animator::UpdateAnimations(float deltaTime) {
    std::vector<std::string> animationsToClear;

    for (auto& [animationName, animationTrack] : this->loadedAnimation) {
        if (animationTrack) {
            animationTrack->Update(deltaTime);

            if (animationTrack->isFinished) {
                animationsToClear.push_back(animationName);
            }
        }
    }

    for (const auto& name : animationsToClear) {
        this->loadedAnimation.erase(name);
    }
}

void Animator::LoadAnimation(Animation& animation) {
    auto track = new AnimationTrack { animation, this->target };

    this->loadedAnimation[animation.Name] = track;

    std::cout << this->loadedAnimation.size();
}