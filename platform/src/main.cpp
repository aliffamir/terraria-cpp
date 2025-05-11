#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <iostream>
#include <print>
#include <string>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 400;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gTexture = nullptr;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

bool init()
{
    bool isSuccess = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::print("SDL could not initialise. SDL Error: {}\n", SDL_GetError());
        isSuccess = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::print("Warning: Linear texture filtering not enabled.");
        }

        // Create window
        gWindow = SDL_CreateWindow("Terraria CPP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!gWindow)
        {
            std::print("Window could not be created. SDL Error: {}\n", SDL_GetError());
            isSuccess = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (!gRenderer)
            {
                std::print("Renderer could not be created. SDL Error: {}\n", SDL_GetError());
                isSuccess = false;
            }
            else
            {
                // Initialise renderer color (background)
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialise PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::print("SDL_image coulud not initialise. SDL_image Error: {}\n", IMG_GetError());
                    isSuccess = false;
                }
            }
        }
    }

    return isSuccess;
}

SDL_Texture* loadTexture(std::string path)
{
    // The final texture that we will return
    SDL_Texture* newTexture = nullptr;

    // Load the image at the specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        std::print("Failed to load image {0}. SDL_image Error: {1}\n", path, IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels - Converts SDL Surface to Texture
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (!newTexture)
        {
            std::print("Failed to create texture {0}. SDL Error: {1}\n", path, SDL_GetError());
        }

        // Free loaded surface from memory
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia()
{
    bool isSuccess = true;

    // Load PNG texture into global texture variable
    gTexture = loadTexture("../assets/pacman.png"); // use relative path for now (need to figure out
                                                    // how to set the path from CMakeLists)
    if (!gTexture)
    {
        std::print("Failed to load texture image.\n");
        isSuccess = false;
    }

    return isSuccess;
}

void close()
{
    // Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    // Start up SDL and create window
    if (!init())
    {
        std::print("Failed to initialise SDL\n");
    }
    else
    {
        if (!loadMedia())
        {
            std::print("Failed to load media.\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Main  loop
            while (!quit)
            {
                // Event loop - handles events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                // Clear screen
                SDL_RenderClear(gRenderer);

                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}