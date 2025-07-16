#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <functional>

using ActionCallback = std::function<void(const char*, Uint8)>;

struct Action {
    const char* ActionName;
    SDL_Keycode keycode;
    ActionCallback callBack;
};

class InputManager {
    public:
        InputManager();

        bool b_isListening;
        bool b_isHalt;

        void BindAction(const char* ActionName, SDL_KeyCode keyCode, ActionCallback callback);
        void UnbindAction(const char* ActionName);

        void Listen(SDL_Event& event);
        void Halt();
        void Quit();

    private:
        std::vector<Action> actions;
};

#endif