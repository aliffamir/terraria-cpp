#include "sprite.h"
#include "globals.h"
#include "graphics.h"
#include <print>

Sprite::Sprite() {};

Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height,
               float posX, float posY)
    : _x{posX}, _y{posY}
{
    _sourceRect.x = sourceX;
    _sourceRect.y = sourceY;
    _sourceRect.w = width;
    _sourceRect.h = height;

    _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (!_spriteSheet)
    {
        std::print("\nFailed to load sprite! SDL_Error: {}\n", SDL_GetError());
    }
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
    SDL_Rect destinationRectangle{x, y, static_cast<int>(_sourceRect.w * Globals::SPRITE_SCALE),
                                  static_cast<int>(_sourceRect.h * Globals::SPRITE_SCALE)};
    graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

void Sprite::update()
{
}