#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <vector>

class Entity;
class Animator {
    public:
        Animator(Entity* e);

        void Play(std::string AnimationName, float speed);
        void Stop(std::string AnimationName);

        void UpdateAnimations(float deltaTime);
    private:
        Entity* target;
};

#endif
