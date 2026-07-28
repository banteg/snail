// set_color_rgba @ 0x44db60 (thiscall, ret 0x10) — tColour::Set(float, float, float, float)

#include "sprite.h"

tColour* tColour::Set(float r_, float g_, float b_, float a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    return this;
}
