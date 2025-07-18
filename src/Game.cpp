#include "Game.h"
#include "WindowRenderer.h"
#include "InputManager.h"
#include "Player.h"

void Game::Start(const SDL_WindowFlags windowFlag) {
    std::cout << "Starting Game.." << '\n';

    int Init = SDL_Init( SDL_INIT_EVERYTHING );

    assert (Init == 0 && "Error while SDL INIT ");

    SDL_Window* activeWindow = SDL_CreateWindow(
        "CPPL", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, 
        HEIGTH, 
        windowFlag
    );
    
    assert(activeWindow != NULL && "Error while creating window!");

    this->Running = true;
    this->Window = activeWindow;

    // Create the rendering box, and start rendering to the screen
    this->AppRenderer = new WindowRenderer { this->Window, SDL_RENDERER_ACCELERATED };
    this->_InputManager = new InputManager();

    Entity* Background = this->AppRenderer->entityManager->CreateEntity(this, Vec2f::zero, "src/art/background/day_background.png", 10000); 
    Entity* Ground = this->AppRenderer->entityManager->CreateEntity(this, GroundScreenLoc, "src/art/background/soil.jpg", 10000); 
    Player* Player = this->AppRenderer->entityManager->CreatePlayer(this, MidScreenLoc + Vec2f {0, -100}, "src/art/sprites/player_sprite_sized.png", 60);

    Background->CanCollide = false;
    Background->Anchored = true;
    Background->Name = "Day Background";

    Ground->CanCollide = true;
    Ground->Anchored = true;
    Ground->Name = "Ground";

    Player->CanCollide = true;
    Player->Anchored = false;
    Player->Name = "Player1";

    this->AppRenderer->entityManager->AwakeEntities();

    //
    this->Run();
}

void Game::Run() {
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = now;
    double freq = (double)SDL_GetPerformanceFrequency();

    while (this->Running) {
            now = SDL_GetPerformanceCounter();
            this->DeltaTime = (double)(now - last) / freq; // Seconds

            last = now;

        // Handle events
        while (SDL_PollEvent(&this->AppEventPoll)) {
            this->_InputManager->Listen(this->AppEventPoll);

            if (this->AppEventPoll.type == SDL_QUIT) {
                this->Running = false;
                this->Stop();
                break;
            }
        }

        // Update and Render
        this->AppRenderer->ClearViewport();

        this->AppRenderer->entityManager->UpdateEntities(this->DeltaTime);

        this->AppRenderer->Render();
        this->AppRenderer->Display();

        SDL_Delay((Uint32)(1000.0f / 144.0f)); // Cap at 144Hz
    }
}

void Game::Stop() {
    std::cout << "Destroying deps:" << '\n';

    this->AppRenderer->Quit();
    this->_InputManager->Quit();
    this->AppRenderer->entityManager->ClearEntities();
    
    SDL_DestroyWindow(this->Window);

    std::cout << "Quitting game...";
    SDL_Quit();
}