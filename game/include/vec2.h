#ifndef VEC2_H
#define VEC2_H

class Vec2
{
  public:
    int x{};
    int y{};

    Vec2(int x, int y);

    inline Vec2 operator+(const Vec2 vec) const;
    inline Vec2 operator-(const Vec2 vec) const;
    inline Vec2 operator*(int scalar) const;
};

#endif