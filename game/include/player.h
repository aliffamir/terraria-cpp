#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"
#include "graphics.h"

class Player : public AnimatedSprite
{
  public:
    Player() = default;
    Player(Graphics& graphics, float x, float y);
    void draw(Graphics& graphics);
    void update(float elapsedTime);

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();

    /*
    void moveLeft
    Moves the player left by -dx
    */
    void moveLeft();

    /*
    void moveRight
    Moves the player right by +dx
    */
    void moveRight();

    /*
    void stopMoving
    Stops moving the player
    */
    void stopMoving();

  private:
    // change in x and y position
    float _dx;
    float _dy;

    Direction _facing;
};

#endif