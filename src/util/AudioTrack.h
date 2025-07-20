#include "AudioData.h"
#include "C_Signal.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct AudioTrack {
    AudioTrack(AudioData& data): data(data) {};
    bool isPlaying = false;
    int channel = -1;
    
    AudioData& data;
    
    Mix_Music* music = nullptr;
    Mix_Chunk* chunk = nullptr;

    SIGNAL<int> OnTrackEnd;

    void Play();
    void Stop();
    void Pause();
};