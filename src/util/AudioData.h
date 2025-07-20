#ifndef AUDIO_DATA_H
#define AUDIO_DATA_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

enum class AudioType {
    MUSIC,
    SFX
};

struct AudioData {
    AudioType audioType;
    std::string TrackName;
    std::string TrackPath;

    bool Looped;
    float Duration;
};

#endif