#include "AudioTrack.h"
#include "AudioManager.h"

#define DEFAULT_CHANNEL -1 // will set to the first free channel

void AudioTrack::Play() {
    std::cout << "Track " << data.TrackName << " looped? " << std::boolalpha << data.Looped << "\n";
    
    if (this->data.audioType == AudioType::MUSIC) {
        if (!this->music) {
            std::cerr << "Play failed: music pointer is null for " << this->data.TrackName << "\n";
            return;
        }
        Mix_PlayMusic(this->music, this->data.Looped ? -1 : 1);
    } else {
        if (!this->chunk) {
            std::cerr << "Play failed: chunk pointer is null for " << this->data.TrackName << "\n";
            return;
        }
        
        if (this->channel != -1) {
            Mix_HaltChannel(this->channel); // Stop any previous play on this channel
        }
        
        this->channel = Mix_PlayChannel(DEFAULT_CHANNEL, this->chunk, this->data.Looped ? -1 : 0);
    }
    this->isPlaying = true;
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