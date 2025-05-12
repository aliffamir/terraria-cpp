#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <iostream>
#include <print>
#include <string>

#include "FrameOutput.h"
#include "GameLogic.h"
#include "GameWindowBuffer.h"
#include "Input.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 400;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

GameWindowBuffer gBuffer;

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
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

                return resetWindowBuffer(gBuffer, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
        }
    }

    return isSuccess;
}

void close()
{
    // Free loaded image
    SDL_DestroyTexture(gBuffer.texture);
    gBuffer.texture = nullptr;

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
        std::print("Failed to initialise SDL!\n");
    }
    else if (!initGameplay())
    {
        std::print("Failed to initialise game!\n");
    }
    else
    {
        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        Input input;
        FrameOutput frame;

        int rectX = 100;
        int rectY = 100;
        const int rectSize = 100;

        auto stop = std::chrono::high_resolution_clock::now();

        // Main  loop
        while (!quit)
        {
            auto start = std::chrono::high_resolution_clock::now();
            double deltaTime =
                (std::chrono::duration_cast<std::chrono::microseconds>(start - stop)).count() / 1000000.0;
            stop = std::chrono::high_resolution_clock::now();

            // we don't want delta time to drop too low, like let's say under 5 fps. you can set this to whatever you
            // want
            // or remove it but I recomand keeping it
            float augmentedDeltaTime = deltaTime;
            if (augmentedDeltaTime > 1.0 / 5)
            {
                augmentedDeltaTime = 1.0 / 5;
            }

            // Event loop - handles events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                processEvent(input, e);
            }

            frame.rects.clear();

            if (!gameplayFrame(augmentedDeltaTime, SCREEN_WIDTH, SCREEN_HEIGHT, input, frame))
            {
                std::print("Failed to process gameplay frame!\n");
                break;
            }

            gBuffer.clear(0, 0, 0);

            // Render frame output
            for (const auto& rect : frame.rects)
            {
                for (int y = 0; y < rect.h; ++y)
                {
                    for (int x = 0; x < rect.w; ++x)
                    {
                        gBuffer.draw(rect.x + x, rect.y + y, rect.r, rect.g, rect.b, rect.a);
                    }
                }
            }

            // Push buffer to screen
            renderBufferToScreen(gRenderer, gBuffer);
            SDL_RenderPresent(gRenderer);

            processInputAfter(input);

            // // Clear screen
            // SDL_RenderClear(gRenderer);

            // // Render texture to screen
            // SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

            // // Update screen
            // SDL_RenderPresent(gRenderer);
        }
    }

    closeGameLogic();
    // Free resources and close SDL
    close();

    return 0;
}