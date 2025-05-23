#include "animatedsprite.h"
#include "graphics.h"
#include "sprite.h"

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width,
                               int height, float posX, float posY, float timeToUpdate)
    : Sprite{graphics, filePath, sourceX, sourceY, width, height, posX, posY}, _frameIndex{0},
      _timeToUpdate{timeToUpdate}, _visible{true}, _currentAnimationOnce{false}, _currentAnimation{""}
{
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string animationName, int width, int height,
                                  Vector2 offset)
{
    // Creates an individual rect for each frame of our animation from the sprite sheet
    // and add it to the rectangles vector
    std::vector<SDL_Rect> rectangles;
    for (int i{0}; i < frames; ++i)
    {
        rectangles.emplace_back(SDL_Rect{(i + x) * width, y, width, height});
    }

    _animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(animationName, rectangles));
    _offsets.insert(std::pair<std::string, Vector2>(animationName, offset));
}

void AnimatedSprite::resetAnimations()
{
    _animations.clear();
    _offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
    _currentAnimationOnce = once;
    if (_currentAnimation != animation)
    {
        _currentAnimation = animation;
        _frameIndex = 0;
    }
}

void AnimatedSprite::stopAnimation()
{
    _frameIndex = 0;
    animationDone(_currentAnimation);
}

void AnimatedSprite::setVisible(bool visible)
{
    _visible = visible;
}

void AnimatedSprite::update(int elapsedTime)
{
    Sprite::update();

    _timeElapsed += elapsedTime;
    if (_timeElapsed > _timeToUpdate)
    {
        _timeElapsed -= _timeToUpdate;
        if (_frameIndex < _animations[_currentAnimation].size() - 1)
        {
            ++_frameIndex;
        }
        else
        {
            if (_currentAnimationOnce == true)
            {
                setVisible(false);
            }
            _frameIndex = 0;
            animationDone(_currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics& graphics, int x, int y)
{
    if (_visible)
    {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + _offsets[_currentAnimation].x;
        destinationRectangle.y = y + _offsets[_currentAnimation].y;
        destinationRectangle.w = _sourceRect.w * Globals::SPRITE_SCALE;
        destinationRectangle.h = _sourceRect.h * Globals::SPRITE_SCALE;

        SDL_Rect sourceRect{_animations[_currentAnimation][_frameIndex]};
        graphics.blitSurface(_spriteSheet, &sourceRect, &destinationRectangle);
    }
}

void AnimatedSprite::animationDone(std::string currentAnimation)
{
}
