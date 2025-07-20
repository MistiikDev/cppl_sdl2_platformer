#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

#include "Vec2f.h"
#include "C_Signal.h"

using ActionCallback = std::function<void(std::string&, Uint8)>;

struct Action {
    std::string ActionName;
    Sint32 keycode;
    ActionCallback callBack;
};

class InputManager {

    public:
        InputManager() { this->b_isListening = true; };

        static SIGNAL<Sint32, Uint8> UserInput; // KEYCODE, INPUT_STATE
        static SIGNAL<Vec2f&> MouseMoveEvent;

        bool b_isListening;
        bool b_isHalt;

        static Vec2f GetMousePosition();

        void BindAction(std::string& ActionName, Sint32 keyCode, ActionCallback callback);
        void UnbindAction(std::string& ActionName);

        void Listen(SDL_Event& event);
        void Quit();

    private:
        std::vector<Action> actions;
};

#endif