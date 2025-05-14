#ifndef GAME_H
#define GAME_H

#include "graphics.h"

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
    void update();
};

#endif