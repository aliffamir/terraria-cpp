#ifndef Input_H
#define Input_H

#include <SDL2/SDL_keycode.h>
#include <array>

struct Button
{
    bool pressed{0};
    bool held{0};
    bool released{0};
    bool altDown{0};
};

struct Input
{
    // C-style array of Buttons - using the SDL_Scancode enum (https://wiki.libsdl.org/SDL2/SDL_Scancode)
    Button keys[SDL_NUM_SCANCODES];

    int cursorX{0};
    int cursorY{0};

    Button leftMouseButton{};
    Button rightMouseButton{};

    std::array<char, 20> typedInput{};

    // To track if window is in focus
    bool focused = false;
};

// Forward declarations
void processInputAfter(Input& input);
void resetInput(Input& input);
void processEventButton(Button& button, bool newState);

#endif