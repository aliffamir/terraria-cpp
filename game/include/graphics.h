#ifndef GRAPHICS_H
#define GRAPHICS_H

// Forward declare these structs so we don't have to include SDL2 here
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

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