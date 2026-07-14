// set_color_rgba @ 0x44db60 (thiscall, ret 0x10)

#include "sprite.h"

tColour* tColour::set_color_rgba(float r_, float g_, float b_, float a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    return this;
}
