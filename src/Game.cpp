#include "Game.h"
#include "WindowRenderer.h"
#include "InputManager.h"

void Game::Start(SDL_WindowFlags windowFlag) {
    std::cout << "Starting Game.." << '\n';

    int Init = SDL_Init( SDL_INIT_EVERYTHING );

    if (Init != 0) {
        std::cerr << "Error while SDL INIT : " << SDL_GetError() << '\n';

        return;
    }

    SDL_Window* activeWindow = SDL_CreateWindow("CPPL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, windowFlag);
    
    if (activeWindow == NULL) {
        std::cerr << "Error while creating window: " << SDL_GetError() << '\n';

        return;
    }

    this->running = true;
    this->window = activeWindow;

    // Create the rendering box, and start rendering to the screen
    this->AppRenderer = new WindowRenderer { this->window, SDL_RENDERER_ACCELERATED };
    this->inputManager = new InputManager();

    // Hardcoded entities to display
    for (EntityMetaData eMD : demoMap) {
        if (eMD.b_isPlayer) {
            this->AppRenderer->entityManager->CreatePlayer(this, eMD.position, eMD.textureLoc); 
        } 
        else {
            this->AppRenderer->entityManager->CreateEntity(this, eMD.position, eMD.textureLoc); 
        }
    }

    this->AppRenderer->entityManager->AwakeEntities();

    //
    this->Run();
}

void Game::Run() {
    Uint32 lastFrameTime = SDL_GetTicks();

    while (this->running) {
        Uint32 currentFrameTime = SDL_GetTicks();
        this->deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert to seconds
        lastFrameTime = currentFrameTime;

        // Handle events
        while (SDL_PollEvent(&this->AppEventPoll)) {
            this->inputManager->Listen(this->AppEventPoll);

            if (this->AppEventPoll.type == SDL_QUIT) {
                this->running = false;
                this->Stop();
                break;
            }
        }

        // Update and Render
        this->AppRenderer->ClearViewport();
        this->AppRenderer->entityManager->UpdateEntities(this->deltaTime);
        this->AppRenderer->Render();
        this->AppRenderer->Display();
    }
}

void Game::Stop() {
    std::cout << "Destroying deps:" << '\n';

    this->AppRenderer->Quit();
    this->inputManager->Quit();
    this->AppRenderer->entityManager->ClearEntities();
    
    SDL_DestroyWindow(this->window);

    std::cout << "Quitting game...";
    SDL_Quit();
}