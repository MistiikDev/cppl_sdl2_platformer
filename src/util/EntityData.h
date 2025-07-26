#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H

#include <string>
#include "Vec2f.h"

struct EntityData {
    std::string Name;
    std::string Class;
    Vec2f Position;

    uint32_t ID;

    double Mass;
    bool Anchored;
    bool CanCollide;
    bool fixedToCamera;
    bool Passive;

    std::string TexturePath;
    std::string RenderingGroup;
    
    int RenderingLayer;
};

#endif