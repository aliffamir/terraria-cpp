#include "GameWindowBuffer.h"
#include <print>

bool resetWindowBuffer(GameWindowBuffer& buffer, SDL_Renderer* renderer, int width, int height)
{
    buffer.w = width;
    buffer.h = height;
    buffer.pixels.resize(width * height);

    // clear current texture memory
    if (buffer.texture)
    {
        SDL_DestroyTexture(buffer.texture);
        buffer.texture = nullptr;
    }

    buffer.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);

    if (!buffer.texture)
    {
        std::print("Error creating texture! SDL Error: {0}\n", SDL_GetError());
        return false;
    }

    return true;
}

void renderBufferToScreen(SDL_Renderer* renderer, GameWindowBuffer& buffer)
{
    SDL_UpdateTexture(buffer.texture, nullptr, buffer.pixels.data(), buffer.w * sizeof(uint_fast32_t));
    SDL_RenderCopy(renderer, buffer.texture, nullptr, nullptr);
}