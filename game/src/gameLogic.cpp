#include <iostream>

struct GameData
{
    int positionX = 0;
    int positionY = 0;
    int fpsCounter = 0;
    double timer = 0;
};

// internal linkage
static GameData data;

// Called to create game
bool initGameplay()
{
    data = {};
    return true;
};

// Called every frame
bool gameplayFrame(double deltaTime, int width, int height) {};

// game cleanup goes here
void closeGameLogic() {};