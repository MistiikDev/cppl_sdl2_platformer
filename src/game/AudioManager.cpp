#include "AudioManager.h"

std::map<std::string, AudioTrack*> AudioManager::audioTracks;

bool AudioManager::Init()
{
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNEL_TYPE, AUDIO_BUFFER_SIZE) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        return false;
    }

    std::cout << "SDL_mixer initialized successfully.\n";

    return true;
}

void AudioManager::Quit()
{
    for (auto &[trackName, activeTrack] : audioTracks)
    {
        activeTrack->Stop();

        if (activeTrack->music)
        {
            Mix_FreeMusic(activeTrack->music);
        }

        if (activeTrack->chunk)
        {
            Mix_FreeChunk(activeTrack->chunk);
        }

        delete activeTrack;
    }

    audioTracks.clear();
    Mix_Quit();
}

void AudioManager::PreloadAudioFiles(const std::string &path)
{
    // Precook the audio from src files
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open audio JSON: " << path << "\n";
        return;
    }

    nlohmann::json j;
    file >> j;

    // Load MUSIC
    for (const auto &[musicID, musicData] : j["music"].items())
    {
        AudioData data;
        data.TrackName = musicData["name"];
        data.TrackPath = musicData["path"];
        data.Looped = musicData["isLooped"];
        data.Duration = musicData["duration"];
        data.audioType = AudioType::MUSIC;

        AudioManager::LoadAudio(data);
    }

    // Load CHUNK SFX
    for (const auto &[musicID, musicData] : j["sfx"].items())
    {
        AudioData data;
        data.TrackName = musicData["name"];
        data.TrackPath = musicData["path"];
        data.Looped = musicData["isLooped"];
        data.Duration = musicData["duration"];
        data.audioType = AudioType::SFX;

        AudioManager::LoadAudio(data);
    }
}

void AudioManager::LoadAudio(AudioData& trackData)
{
    std::cout << "AUDIO: Loading: " << trackData.TrackPath << std::endl;

    AudioTrack* track = new AudioTrack(trackData);

    if (trackData.audioType == AudioType::MUSIC)
    {
        track->music = Mix_LoadMUS(trackData.TrackPath.c_str());
    }
    else
    {
        track->chunk = Mix_LoadWAV(trackData.TrackPath.c_str());
    }

    if (!track->music && !track->chunk) {
        std::cout << "Mix_Load failed for " << trackData.TrackName << ": " << Mix_GetError() << "\n";
        
        delete track;
        return;
    } else {
        audioTracks[trackData.TrackName] = track;
    }
}

void AudioManager::PlayAudio(std::string &trackName)
{
    auto it = audioTracks.find(trackName);

    if (it == audioTracks.end() || it->second == nullptr) {
        std::cerr << "AudioTrack not found or null for: " << trackName << "\n";
        return;
    }

    it->second->Play();
};