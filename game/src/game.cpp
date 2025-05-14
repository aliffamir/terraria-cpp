#include "game.h"
#include "graphics.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
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
        std::print("Failed to initialise SDL! SDL Error: {0}\n", SDL_GetError());
        return;
    }

    gameLoop();
}

Game::~Game()
{
}

void Game::gameLoop()
{
    Graphics graphics;
    Input input;
    SDL_Event event;

    _player = Sprite(graphics, "../assets/sprites/walk.png", 0, 128, 64, 64, 100, 100);

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

        // draw(graphics);
        graphics.clear();
        _player.draw(graphics, 100, 100);
        graphics.flip();
    }
}

void Game::draw(Graphics& graphics)
{
    graphics.clear();
    _player.draw(graphics, 100, 100);
    graphics.flip();
}

void Game::update(float deltaTime)
{
}