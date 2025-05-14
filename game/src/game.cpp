#include "game.h"
#include "graphics.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <print>

namespace
{
constexpr int FPS{60};
constexpr int MAX_FRAME_TIME{6 * 1000 / FPS};
} // namespace
Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::print("Failed to initialise SDL! SDL Error: {}\n", SDL_GetError());
        return;
    }
    gameLoop();
}

Game::~Game()
{
    SDL_Quit();
}

void Game::gameLoop()
{
    Graphics graphics;
    Input input;
    SDL_Event event;

    int LAST_UPDATE_TIME = static_cast<int>(SDL_GetTicks());
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            // reset our pressed and released keys every frame
            input.beginNewFrame();

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.repeat == 0)
                {
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                input.keyUpEvent(event);
            }
            else if (event.type == SDL_QUIT)
            {
                return;
            }
        }

        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            return;
        }

        const int CURRENT_TIME_MS{static_cast<int>(SDL_GetTicks())};
        int ELAPSED_TIME_MS{CURRENT_TIME_MS - LAST_UPDATE_TIME};
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        draw(graphics);
    }
}

void Game::draw(Graphics& graphics)
{
    graphics.clear();
    graphics.flip();
}

void Game::update(float deltaTime)
{
}