#include "WindowRenderer.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include "AnimationLoader.h"

#include "Game.h"

void Game::Start(const SDL_WindowFlags windowFlag) {
    std::cout << "CORE : Loading SDL dependencies" << std::endl;

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

    AnimationLoader::Init();
    AudioManager::Init();

    AnimationLoader::LoadAnimDefinitions("src/assets/data/entity_animations.json");
    AudioManager::PreloadAudioFiles("src/assets/data/sound.json");

    // Create the rendering box, and start rendering to the screen
    this->_InputManager = new InputManager { };
    this->AppRenderer = new WindowRenderer { this->Window, SDL_RENDERER_ACCELERATED, LOGICAL_WIDTH, LOGICAL_HEIGTH };
    this->levelManager = new LevelManager { this->AppRenderer->entityManager };

    this->levelManager->UnloadCurrentLevel();
    this->levelManager->LoadLevel(this, "level1");

    std::string bg_music = "bg_music";

    AudioManager::PlayAudio(bg_music);

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

            switch (this->AppEventPoll.type) {
                case SDL_QUIT:
                    this->Running = false;
                    this->Stop();
                    break;
                case SDL_WINDOWEVENT_RESIZED: {
                    // int newWidth = this->AppEventPoll.window.data1;
                    // int newHeight = this->AppEventPoll.window.data2;

                    // std::cout << "Window resized to: " << newWidth << "x" << newHeight << std::endl;

                    // AppRenderer->SetViewportSize(newWidth, newHeight);
                    break;
                }
                default:
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

void Game::GetLogicalWindowSize(int& w, int& h) {
    w = this->AppRenderer->logicalWidth;
    h = this->AppRenderer->logicalHeigth;
}

void Game::Stop() {
    AudioManager::Quit();
    
    this->levelManager->UnloadCurrentLevel();
    this->_InputManager->Quit();

    this->AppRenderer->entityManager->ClearEntities();
    this->AppRenderer->Quit();

    SDL_DestroyWindow(this->Window);

    std::cout << "Quitting game...";

    SDL_Quit();
}