#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
    //Initialize SDL subsytems
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        //We have failed to initialize
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    //TODO: DRAW A WINDOW

    //Terminate SDL subsystems
    SDL_Quit();
    return 0;
}
