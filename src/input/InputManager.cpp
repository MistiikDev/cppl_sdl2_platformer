#include "InputManager.h"

SIGNAL<Sint32, Uint8> InputManager::UserInput("User Input");
SIGNAL<Vec2f&> InputManager::MouseMoveEvent("Mouse Movement");

void InputManager::BindAction(std::string& ActionName, Sint32 keyCode, ActionCallback callback) {
    if (callback == NULL) {
        std::cerr << "ERROR: Binded action : " << ActionName << " without any callback!" << std::endl;
        
        return;
    }   

    Action action { ActionName, keyCode, callback };

    this->actions.push_back(action);
}

void InputManager::UnbindAction(std::string& ActionName) {
    auto iterator = std::find_if(this->actions.begin(), this->actions.end(), [ActionName](const Action& action){
        return action.ActionName == ActionName;
    });

    if (iterator != this->actions.end()) {
        this->actions.erase(iterator);
    }
}


void InputManager::Listen(SDL_Event& event) {
    if (!b_isListening) { return; }

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

        int x = 3; // Some X Value;
        int y = 4; // Some Y Value;

        Vec2f MouseHover { static_cast<float>(x), static_cast<float>(y) };

        InputManager::MouseMoveEvent.Invoke(MouseHover);
    }

    if (b_isInputValid) {

        InputManager::UserInput.Invoke(keyCode, inputState);
        
        for (Action& action : this->actions) {
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
    std::cout << "Input destructed" << std::endl;

    this->b_isListening = false;
}

// 

Vec2f InputManager::GetMousePosition() {
    int x, y;

    SDL_GetMouseState(&x, &y);

    return Vec2f(x, y);
}