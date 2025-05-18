#include "vec2.h"

Vec2::Vec2(int x, int y) : x{x}, y{y}
{
}

inline Vec2 Vec2::operator+(const Vec2 vec) const
{
    return Vec2{this->x + vec.x, this->y + vec.y};
}

inline Vec2 Vec2::operator-(const Vec2 vec) const
{
    return Vec2{this->x - vec.x, this->y - vec.y};
}

inline Vec2 Vec2::operator*(int scalar) const
{
    return Vec2{this->x * scalar, this->y * scalar};
}
