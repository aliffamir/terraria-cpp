#ifndef gameLogic_h
#define gameLogic_h

#include "Input.h"

bool initGameplay();
bool gameplayFrame(double deltaTime, int width, int height, const Input& input, FrameOutput& frame);
void closeGameLogic();

#endif