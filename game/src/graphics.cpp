#include "graphics.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

Graphics::Graphics()
{
    _window = SDL_CreateWindow("Terraria from Scratch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0);
    /*
    SDL_RENDERER_ACCELERATED enforces hardware acceleration (GPU)
    fallback to SDL_RENDERER_PRESENTVSYNC
    see (https://wiki.libsdl.org/SDL2/SDL_RendererFlags)
    */
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics()
{
    if (SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        if (_window)
            SDL_DestroyWindow(_window);
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
    }
}

SDL_Surface* Graphics::loadImage(const std::string& filePath)
{
    if (!_spriteSheets.contains(filePath))
    {
        _spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect)
{
    SDL_RenderCopy(_renderer, texture, sourceRect, destinationRect);
}

void Graphics::flip()
{
    SDL_RenderPresent(_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
    return _renderer;
}
