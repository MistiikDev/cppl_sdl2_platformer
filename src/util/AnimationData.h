#ifndef ANIMATION_H
#define ANIMATION_H 

#include <vector>
#include <map>
#include <string>

struct AnimationData {
    float duration;
    bool looped;
    
    std::string Name;
    std::vector<std::string> framePaths;
};


#endif