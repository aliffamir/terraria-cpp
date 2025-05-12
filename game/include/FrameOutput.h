#ifndef FRAME_OUTPUT_H
#define FRAME_OUTPUT_H

#include <vector>

struct RenderableRect
{
    int x, y, w, h;
    unsigned char r, g, b, a;
};

struct FrameOutput
{
    std::vector<RenderableRect> rects{};
};

#endif