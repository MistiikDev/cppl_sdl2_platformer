#include "Entity.h"
#include "Animation.h"

AnimationTrack::AnimationTrack(Animation& animationData, Entity* e): animation(animationData), targetEntity(e) {
    this->elapsedTime = 0.0f;
    this->isLooping = animationData.looped;
    this->currentFrame = 0;

    this->isPlaying = false;
    this->isFinished = false;
}

void AnimationTrack::Update(float deltaTime) {
    if (this->isFinished || !this->isPlaying) return;

    int frameCount = static_cast<int>(this->animation.frames.size());
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
        SDL_Texture* frameTexture = this->animation.frames[this->currentFrame].get();

        SDL_Rect frameBoundingBox{};
        SDL_QueryTexture(frameTexture, nullptr, nullptr, &frameBoundingBox.w, &frameBoundingBox.h);

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
}

void AnimationTrack::Clear() {
    this->isFinished = true;
}