#include "InputManager.h"

InputManager::InputManager() {
    this->b_isListening = true;
}

void InputManager::BindAction(const char* ActionName, Sint32 keyCode, ActionCallback callback) {
    if (callback == NULL) {
        std::cerr << "ERROR: Binded action : " << ActionName << " without any callback!" << std::endl;
        
        return;
    }   

    Action action { ActionName, keyCode, callback };

    this->actions.push_back(action);
}

void InputManager::UnbindAction(const char* ActionName) {
    auto iterator = std::find_if(this->actions.begin(), this->actions.end(), [ActionName](const Action& action){
        return action.ActionName == ActionName;
    });

    if (iterator != this->actions.end()) {
        this->actions.erase(iterator);
    }
}


void InputManager::Listen(SDL_Event& event) {
    if (!b_isListening) { return; }

    if (event.type == SDL_QUIT) {
        this->Quit();
    }

    Sint32 keyCode = -1;
    Uint8 inputState = 0;

    bool b_isInputValid = false;

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        keyCode = event.key.keysym.sym;
        inputState = (event.type == SDL_KEYDOWN) ? SDL_PRESSED : SDL_RELEASED;
        b_isInputValid = true;

    } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        keyCode = static_cast<Sint32>(event.button.button);
        inputState = (event.type == SDL_MOUSEBUTTONDOWN) ? SDL_PRESSED : SDL_RELEASED;
        b_isInputValid = true;

    } else if (event.type == SDL_MOUSEMOTION) {
        keyCode = event.button.button;
        inputState = SDL_PRESSED;

        // Template for futur event signal manager;
        int x = event.motion.x;
        int y = event.motion.y;

        Vec2f MouseHover { static_cast<float>(x), static_cast<float>(y) };

        this->MouseMoveEvent.Invoke(MouseHover);
    }

    if (b_isInputValid) {
        for (const Action& action : this->actions) {
            if (action.keycode == keyCode) {
                if (action.callBack) {
                    action.callBack(action.ActionName, inputState);
                } else {
                    std::cerr << "[ERROR] Callback for action '" << action.ActionName << "' is null!\n";
                }
            }
        } 
    }
}

void InputManager::Quit() {
    std::cout << "Quitting input listener." << std::endl;

    this->b_isListening = false;
}

// 

Vec2f InputManager::GetMousePosition() {
    int x, y;

    SDL_GetMouseState(&x, &y);

    return Vec2f(x, y);
}