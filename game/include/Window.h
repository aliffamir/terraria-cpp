#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
  public:
    Window()
    {
        _window = SDL_CreateWindow("Terraria from Scratch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400,
                                   SDL_WINDOW_SHOWN);
    }

    SDL_Surface* getSurface() const
    {
        return SDL_GetWindowSurface(_window);
    }

    void render()
    {
        SDL_FillRect(getSurface(), nullptr, SDL_MapRGB(getSurface()->format, 255, 255, 255));
    }

    void update()
    {
        SDL_UpdateWindowSurface(_window);
    }

    ~Window()
    {
        if (_window && SDL_WasInit(SDL_INIT_VIDEO))
        {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }
    }

  private:
    // TODO: use smart pointer std::unique_ptr
    SDL_Window* _window;
};

#endif