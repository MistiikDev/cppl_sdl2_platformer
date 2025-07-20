#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <iostream>
#include <map>
#include <fstream>

#include "nlohmann/json.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "AudioData.h"
#include "AudioTrack.h"

#define AUDIO_FREQUENCY 44188
#define CHANNEL_TYPE 2 // Stereo
#define AUDIO_BUFFER_SIZE 2048

class AudioManager { 
    public: 
        static std::map<std::string, AudioTrack*> audioTracks;

        static bool Init();

        static void Quit();

        static void PreloadAudioFiles(const std::string& path);

        static void LoadAudio(AudioData& trackData);
        static void PlayAudio(std::string& trackName);
};

#endif