#include "FrameOutput.h"
#include "Input.h"
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
bool gameplayFrame(double deltaTime, int width, int height, const Input& input, FrameOutput& output)
{
    // Handle movement
    if (input.keys[SDL_SCANCODE_UP].held)
        data.positionY -= int(200 * deltaTime);
    if (input.keys[SDL_SCANCODE_DOWN].held)
        data.positionY += int(200 * deltaTime);
    if (input.keys[SDL_SCANCODE_LEFT].held)
        data.positionX -= int(200 * deltaTime);
    if (input.keys[SDL_SCANCODE_RIGHT].held)
        data.positionX += int(200 * deltaTime);

    // Clamp to screen bounds
    data.positionX = std::clamp(data.positionX, 0, width - 50);
    data.positionY = std::clamp(data.positionY, 0, height - 50);

    // FPS tracking (optional)
    data.fpsCounter++;
    data.timer += deltaTime;
    if (data.timer >= 1.0)
    {
        std::cout << "FPS: " << data.fpsCounter << "\n";
        data.timer -= 1.0;
        data.fpsCounter = 0;
    }

    // Output a single red rectangle
    output.rects.push_back({data.positionX, data.positionY, 50, 50, 255, 0, 0, 255});

    return true;
};

// game cleanup goes here
void closeGameLogic() {};