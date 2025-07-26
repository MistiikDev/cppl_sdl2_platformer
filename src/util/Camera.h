#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vec2f.h"

class WindowRenderer;
class Camera {
    public:
        Camera(int w, int h);

        bool isFocusing;
        bool isFollowing;
        
        double Depth;

        Vec2f Position;
        Vec2f ViewportSize;
        Vec2f Target;

        void Focus(bool isFocusing);
        
        void Follow(Vec2f& targetPosition);
        Vec2f ScaleToZoom(Vec2f& size);
        Vec2f WorldToScreen(Vec2f& WorldPosition);
        Vec2f ScreenToWorldPosition(Vec2f& ScreenPosition);
    private: 
        SDL_Renderer* ActiveRenderer;
};

#endif