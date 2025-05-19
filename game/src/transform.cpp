#include "transform.h"
#include "vec2.h"

Transform::Transform(float x, float y) : _x{x}, _y{y}
{
}

void Transform::TranslateX(float x)
{
    _x += x;
}

void Transform::TranslateX(float y)
{
    _y += y;
}

void Transform::Translate(const Vec2& vector)
{
    _x += vector.x;
    _y += vector.y;
}