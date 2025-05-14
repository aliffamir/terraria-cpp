#include "game.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <print>

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::print("Failed to initialise SDL! SDL Error: {}\n", SDL_GetError());
        return;
    }
}

Game::~Game()
{
    SDL_Quit();
}

void Game::gameLoop()
{
    Graphics graphics;

    SDL_Event e;

    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return;
            }
        }
    }

    draw(graphics);
}

void Game::draw(Graphics& graphics)
{
    graphics.clear();
    graphics.flip();
}

void Game::update()
{
}