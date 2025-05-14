#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

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

    /* SDL_Surface* loadImage
    Loads an image into the _spriteSheets map if it doesn't already exist.
    As a result, each image will only ever be loaded once
    Returns the image from the map regardless of whether or not it was just loaded
    */
    SDL_Surface* loadImage(const std::string& filePath);

    void blitSurface(SDL_Texture* texture, const SDL_Rect* sourceRect, const SDL_Rect* destinationRect);
    void flip();
    void clear();
    SDL_Renderer* getRenderer() const;

  private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif