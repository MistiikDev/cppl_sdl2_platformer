#include "InputManager.h"

InputManager::InputManager() {
    this->b_isListening = true;
}

void InputManager::BindAction(const char* ActionName, SDL_KeyCode keyCode, ActionCallback callback) {
    if (callback == NULL) {
        std::cerr << "ERROR: Binded action : " << ActionName << " without any callback!" << std::endl;
        
        return;
    }   

    Action action { ActionName, keyCode, callback };

    this->actions.push_back(action);
}

void InputManager::UnbindAction(const char* ActionName) {

}

void InputManager::Listen(SDL_Event& event) {
    if (!b_isListening) { return; }

    if (event.type == SDL_QUIT) {
        this->Quit();
    }

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {           
        SDL_Keycode keyCode = event.key.keysym.sym;
        Uint8 inputState = (event.type == SDL_KEYDOWN) ? SDL_PRESSED : SDL_RELEASED;

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