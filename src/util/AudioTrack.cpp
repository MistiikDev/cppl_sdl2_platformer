#include "AudioTrack.h"
#include "AudioManager.h"

#define DEFAULT_CHANNEL -1 // will set to the first free channel

void AudioTrack::Play() {
    this->isPlaying = true;
    
    if (this->data.audioType == AudioType::MUSIC) {
        Mix_PlayMusic(this->music, this->data.Looped ? -1 : 1);
    } else {
        this->channel = Mix_PlayChannel(DEFAULT_CHANNEL, this->chunk, this->data.Looped ? -1 : 0);
    }
}

void AudioTrack::Stop() {
    this->isPlaying = false;
    if (this->data.audioType == AudioType::MUSIC) {
        Mix_HaltMusic();
    } else {
        Mix_HaltChannel(this->channel);
    }
}

void AudioTrack::Pause() {
    if (this->data.audioType == AudioType::MUSIC) {
        Mix_PauseMusic();
    } else {
        Mix_Pause(this->channel);
    }
}