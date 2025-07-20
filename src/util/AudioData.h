#include <string>

struct AudioData {
    std::string TrackName;
    
    bool Looped;
    float Duration;
};

struct AudioTrack {
    AudioData& data;

    void Play();
    void Stop();
    void Pause();
};