#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals
{
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 400;
constexpr float SPRITE_SCALE = 1.0f;
} // namespace Globals

struct Vector2
{
    int x;
    int y;

    Vector2() : x{0}, y{0}
    {
    }

    Vector2(int x, int y) : x{x}, y{y}
    {
    }

    Vector2 zero()
    {
        return Vector2(0, 0);
    }
};

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

#endif