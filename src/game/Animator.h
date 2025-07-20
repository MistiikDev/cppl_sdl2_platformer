#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <vector>

#include "Animation.h"

class Entity;
class Animator {
    public:
        Animator(Entity* e) {target = e;};

        void Play(std::string& AnimationName, float speed);
        void Stop(std::string& AnimationName);
        
        void LoadAnimation(Animation& animation);
        void UpdateAnimations(float deltaTime);
    private:
        Entity* target;
        std::map<std::string, AnimationTrack*> loadedAnimation;
};

#endif
