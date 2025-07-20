#include "AudioData.h"
#include "map"

class AudioManager { 
    public: 
        static std::map<std::string&, AudioTrack*> audioTracks;

        static void LoadAudio(AudioData& trackData) {
            auto track = new AudioTrack {trackData};

            audioTracks[trackData.TrackName] = track;
        }

        static void ClearQueue() {
            audioTracks.clear();
        }
};