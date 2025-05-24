#include "player.h"
#include <string>

namespace PlayerConstants
{
const float WALK_SPEED = 0.2f;
}

Player::Player(Graphics& graphics, float x, float y)
    : AnimatedSprite{graphics, "../assets/sprites/walk.png", 0, 64, 64, 64, x, y, 100}
{
    graphics.loadImage("../assets/sprites/walk.png");
    setupAnimations();
    playAnimation("WalkLeft");
}

void Player::setupAnimations()
{
    addAnimation(2, 0, 64, "IdleLeft", 64, 64, Vector2{0, 0});
    addAnimation(2, 0, 128, "IdleRight", 64, 64, Vector2{0, 0});
    addAnimation(9, 0, 64, "WalkLeft", 64, 64, Vector2{0, 0});
    addAnimation(9, 0, 192, "WalkRight", 64, 64, Vector2{0, 0});
}

void Player::animationDone(std::string currentAnimation)
{
}

void Player::moveLeft()
{
    _dx = -PlayerConstants::WALK_SPEED;
    playAnimation("WalkLeft");
    _facing = LEFT;
}

void Player::moveRight()
{
    _dx = PlayerConstants::WALK_SPEED;
    playAnimation("WalkRight");
    _facing = RIGHT;
}

void Player::stopMoving()
{
    _dx = 0.0f;
    playAnimation(_facing == LEFT ? "IdleLeft" : "IdleRight");
}

void Player::update(float elapsedTime)
{
    _x += _dx * elapsedTime;
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics& graphics)
{
    AnimatedSprite::draw(graphics, _x, _y);
}