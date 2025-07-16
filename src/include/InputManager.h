#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <functional>
#include <algorithm>

#include "Vec2f.h"
#include "Signal.h"

using ActionCallback = std::function<void(const char*, Uint8)>;

struct Action {
    const char* ActionName;
    Sint32 keycode;
    ActionCallback callBack;
};

class InputManager {
    public:
        InputManager();

        bool b_isListening;
        bool b_isHalt;

        Vec2f GetMousePosition();

        void BindAction(const char* ActionName, Sint32 keyCode, ActionCallback callback);
        void UnbindAction(const char* ActionName);

        SIGNAL<Vec2f&> MouseMoveEvent { "Mouse Mouvement" };

        void Listen(SDL_Event& event);
        void Halt();
        void Quit();

    private:
        std::vector<Action> actions;
};

#endif