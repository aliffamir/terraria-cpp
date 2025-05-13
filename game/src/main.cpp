#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <iostream>
#include <print>
#include <string>

#include "Window.h"

int main(int argc, char* argv[])
{
    // Start up SDL and create window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::print("Failed to initialise SDL! SDL Error: {}\n", SDL_GetError());
        return 0;
    }

    Window gameWindow;

    bool gameRunning = true;
    SDL_Event e;

    while (gameRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }

        gameWindow.render();
        gameWindow.update();
    }

    SDL_Quit();

    return 0;
}