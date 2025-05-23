#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "globals.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite
{
  public:
    AnimatedSprite();
    AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height,
                   float posX, float posY, float timeToUpdate);

    /*
     void playAnimation
     Plays the animation provided if it's not already playing
     */
    void playAnimation(std::string animation, bool once = false);

    /*
     void update
     Updates the animated sprite (timer)
     */
    void update(int elapsedTime);

    /*
     void draw
     Draws the sprite to the screen
     */
    void draw(Graphics& graphics, int x, int y);

  protected:
    float _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;

    /*
    void addAnimation
    Adds an animation to the _animations map
    */
    void addAnimation(int frames, int x, int y, std::string animationName, int width, int height, Vector2 offset);

    void resetAnimations();

    void stopAnimation();

    void setVisible(bool visible);

    /*
    void animationDone
    Logic that happens when an animation is done
    */
    virtual void animationDone(std::string currentAnimation);

    /*
     void setupAnimations
     A required function that sets up all animations for a sprite
     */
    virtual void setupAnimations();

  private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;
    int _frameIndex;
    int _timeElapsed;
    bool _visible;
};

#endif