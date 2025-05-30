#ifndef GAME_H
#define GAME_H

#include "player.h"

class Graphics;

class Game
{
  public:
    Game();
    ~Game();

  private:
    /*
    Main game loop
    */
    void gameLoop();

    /* Draws our frames, called every frame */
    void draw(Graphics& graphics);

    /* Updates the state of our game every frame (i.e. player, world, enemy) */
    void update(float deltaTime);

    Player _player;
};

#endif