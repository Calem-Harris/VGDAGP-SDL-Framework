#include "Graphics.h"

namespace SDLFramework {
	//This is how we initialize static members in a class
	//Specifically ones that we do NOT want to be constants!!
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	//This is where we make this class a singleton
	Graphics* Graphics::Instance() {
		//We are checking to see if sInstance already has an instance of Graphics stored in it
		if (sInstance == nullptr) {
			//If not, create a new instance of Graphics
			sInstance = new Graphics();
		}

		//Returns our Graphics instance AFTER making sure there is one.
		return sInstance;
	}

	void Graphics::Release() {
		delete sInstance;
		sInstance = nullptr;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}
}