// set_color_grayscale @ 0x44db90 (thiscall, ret 0x4) — tColour::Grey(float)

#include "sprite.h"

void tColour::Grey(float intensity)
{
    a = 1.0f;
    r = intensity;
    g = intensity;
    b = intensity;
}
