#ifndef GAME_WINDOW_BUFFER_H
#define GAME_WINDOW_BUFFER_H

#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>

struct GameWindowBuffer
{
    SDL_Texture* texture = nullptr;
    // each pixel is 4 byte
    std::vector<uint32_t> pixels;
    int w{0};
    int h{0};

    inline void draw(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    {
        if (x < 0 || y < 0 || x >= w || y >= h)
            return;

        pixels[y * w + x] = (a << 24) | (r << 16) | (g << 8) | b;
    }

    void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
    {
        uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;
        std::fill(pixels.begin(), pixels.end(), color);
    }
};

bool resetWindowBuffer(GameWindowBuffer& buffer, SDL_Renderer* renderer, int width, int height);
void renderBufferToScreen(SDL_Renderer* renderer, GameWindowBuffer& buffer);

#endif