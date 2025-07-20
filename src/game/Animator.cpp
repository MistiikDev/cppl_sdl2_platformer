#include "Animator.h"
#include "Entity.h"

#include <iostream>

void Animator::Play(std::string AnimationName, float speed) {
    if (this->target->LoadedAnimations.count(AnimationName) == 0 || this->target->LoadedAnimations[AnimationName]->isPlaying) {
        return;
    }
    this->target->LoadedAnimations[AnimationName]->Play(speed);
}

void Animator::Stop(std::string AnimationName) {
    if (this->target->LoadedAnimations.count(AnimationName) == 0 || this->target->LoadedAnimations[AnimationName]->isFinished) {
        return;
    }

    this->target->LoadedAnimations[AnimationName]->Stop();
}

void Animator::UpdateAnimations(float deltaTime) {
    std::vector<std::string> animationsToClear;

    for (auto& [animationName, animationTrack] : this->target->LoadedAnimations) {
        if (animationTrack) {
            animationTrack->Update(deltaTime);

            if (animationTrack->isFinished) {
                animationsToClear.push_back(animationName);
            }
        }
    }

    for (const auto& name : animationsToClear) {
        this->target->LoadedAnimations.erase(name);
    }
}