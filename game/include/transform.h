#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec2.h"

class Transform
{
  public:
    Transform(float x = 0, float y = 0);

  private:
    float _x{};
    float _y{};

    inline void TranslateX(float x);
    inline void TranslateY(float y);
    inline void Translate(const Vec2& vector);
};

#endif