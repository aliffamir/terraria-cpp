#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

class Graphics
{
  public:
    Graphics();
    ~Graphics();

    void blitSurface(SDL_Texture* texture, const SDL_Rect* sourceRect, const SDL_Rect* destinationRect);
    void flip();
    void clear();

  private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};

#endif