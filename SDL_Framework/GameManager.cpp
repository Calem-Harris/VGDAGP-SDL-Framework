#include "GameManager.h"

namespace SDLFramework {
	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}

		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
        //Main Game Loop
        while (!mQuit) {
            mTimer->Update();
            //Event Polling Loop
            //While there are events inside of our events varaible...
            while (SDL_PollEvent(&mEvents)) {
                //Handle each and every event we want to look for
                switch (mEvents.type) {
                case SDL_QUIT:
                    mQuit = true;
                    break;
                }
            }

            if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
                mTimer->Reset();
                Update();
                LateUpdate();
                Render();
            }
        }
	}

    void GameManager::Update() {
        std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;
    }

    void GameManager::LateUpdate() {

    }

    void GameManager::Render() {
        mGraphics->ClearBackBuffer();
        mGraphics->Render();
    }

    GameManager::GameManager() : mQuit(false) {
        //calling to our Graphics Singleton
        mGraphics = Graphics::Instance();

        if (!Graphics::Initialized()) {
            mQuit = true;
        }

        //Initialize all other modules
        mTimer = Timer::Instance();
    } 

    GameManager::~GameManager() {
        //Release Modules
        Graphics::Release();
        mGraphics = nullptr;

        Timer::Release();
        mTimer = nullptr;

        //Quit SDl Subsystems
        SDL_Quit();
    }
    //Namespace bracket is below
}