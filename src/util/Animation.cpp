#include "Entity.h"
#include "Animation.h"

AnimationTrack::AnimationTrack(AnimationData& animationData, Entity* e): animation(animationData), targetEntity(e) {
    this->elapsedTime = 0.0f;
    this->isLooping = animationData.looped;
    this->currentFrame = 0;

    this->isPlaying = false;
    this->isFinished = false;
}

void AnimationTrack::Update(float deltaTime) {
    if (this->isFinished || !this->isPlaying) return;

    int frameCount = static_cast<int>(this->frames.size());
    if (frameCount == 0) return;

    float frameDuration = this->animation.duration / frameCount;
    bool frameAdvanced = false;
    this->elapsedTime += deltaTime;

    
    while (this->elapsedTime >= frameDuration) {
        this->elapsedTime -= frameDuration;
        this->currentFrame++;
        frameAdvanced = true;

        if (this->currentFrame >= frameCount) {
            if (this->animation.looped) {
                this->currentFrame = 0;
            } else {
                this->Stop();
                return;
            }
        }
    }

    if (frameAdvanced) {
        SDL_Texture* frameTexture = this->frames[this->currentFrame].get();
        
        if (!frameTexture) {
            std::cerr << "[Animation] Null texture in frame " << this->currentFrame << std::endl;
            return;
        }

        SDL_Rect frameBoundingBox{};
        if (SDL_QueryTexture(frameTexture, nullptr, nullptr, &frameBoundingBox.w, &frameBoundingBox.h) != 0) {
            std::cerr << "[Animation] SDL_QueryTexture failed: " << SDL_GetError() << "\n";
            return;
        }

        this->targetEntity->SetTexture(frameTexture);
        this->targetEntity->SetEntityRenderingBounds(frameBoundingBox);
    }
}

void AnimationTrack::Play(float speed) {
    this->isPlaying = true;
    this->isFinished = false;

    this->speed = (speed > 0) ? speed : 1.0f;
}


void AnimationTrack::Stop() {
    this->isPlaying = false;
    this->targetEntity->ResetTextureDefault();

    this->currentFrame = 0;
}

void AnimationTrack::Clear() {
    this->isFinished = true;
}