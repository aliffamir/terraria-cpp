#include "Input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <cstring>

void processInputAfter(Input& input)
{
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
    {
        input.keys[i].pressed = false;
        input.keys[i].held = false;
        input.keys[i].released = false;
    }

    input.leftMouseButton.pressed = false;
    input.leftMouseButton.held = false;
    input.leftMouseButton.released = false;

    input.rightMouseButton.pressed = false;
    input.rightMouseButton.held = false;
    input.rightMouseButton.released = false;

    input.typedInput = {};
}

void resetInput(Input& input)
{
    input.leftMouseButton = {};
    input.rightMouseButton = {};

    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
    {
        input.keys[i] = {};
    }
    input.typedInput = {};
}

void processEventButton(Button& button, bool newState)
{
    // if button is pressed - newState == 1
    if (newState)
    {
        // if button is not currently being held set pressed and held to true
        if (!button.held)
        {
            button.pressed = true;
            button.held = true;
            button.released = false;
        }
    }
    else
    {
        button.pressed = false;
        button.held = false;
        button.released = true;
    }
}

void processEvent(Input& input, const SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        processEventButton(input.keys[e.key.keysym.scancode], true);
        break;

    case SDL_KEYUP:
        processEventButton(input.keys[e.key.keysym.scancode], false);
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            processEventButton(input.leftMouseButton, true);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            processEventButton(input.rightMouseButton, true);
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            processEventButton(input.leftMouseButton, false);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            processEventButton(input.rightMouseButton, false);
        }
        break;

    case SDL_MOUSEMOTION:
        input.cursorX = e.motion.x;
        input.cursorY = e.motion.y;
        break;
    }
}
