#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool quit = false;

int main(int argc, char* args[])
{
    //Initialize SDL subsytems
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        //We have failed to initialize
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    //TODO: DRAW A WINDOW
    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        //We have failed to create a window
        std::cerr << "Unable to create Window! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    //Anything after this can assume that our Window was able to successfully create itself
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        //We have failed to create a renderer
        std::cerr << "Unable to get renderer. SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Event events = {};

    //Main Game Loop
    while (!quit) {
        //Event Polling Loop
        //While there are events inside of our events varaible...
        while (SDL_PollEvent(&events)) {
            //Handle each and every event we want to look for
            switch (events.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        //Draw code goes down here
        SDL_RenderFillRect(renderer, nullptr);
        SDL_RenderPresent(renderer);
    }

    //Destroy the renderer
    SDL_DestroyRenderer(renderer);
    //Destroy the window
    SDL_DestroyWindow(window);

    //Terminate SDL subsystems
    SDL_Quit();
    return 0;
}
