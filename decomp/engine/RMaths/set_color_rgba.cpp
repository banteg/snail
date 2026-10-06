// set_color_rgba @ 0x44db60 (thiscall, ret 0x10)
// Legacy explicit-receiver transcription of tColour(float, float, float, float).
// See authored-abi-control for the equally exact real constructor definition.

#include "sprite.h"

tColour* tColour::Set(float r_, float g_, float b_, float a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    return this;
}
