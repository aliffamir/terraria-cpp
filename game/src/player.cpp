#include "player.h"
#include <string>

Player::Player(Graphics& graphics, float x, float y)
    : AnimatedSprite{graphics, "../assets/sprites/walk.png", 0, 64, 64, 64, x, y, 100}
{
    graphics.loadImage("../assets/sprites/walk.png");
}

void Player::setupAnimations()
{
    addAnimation(9, 0, 64, "WalkLeft", 64, 64, Vector2{0, 0});
    addAnimation(9, 0, 192, "WalkRight", 64, 64, Vector2{0, 0});
}

void Player::animationDone(std::string currentAnimation)
{
}

void Player::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics& graphics)
{
    AnimatedSprite::draw(graphics, _x, _y);
}