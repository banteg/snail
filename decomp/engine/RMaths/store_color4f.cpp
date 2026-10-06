// store_color4f @ 0x44dbb0 (thiscall, ret 0x10)
// Authored void tColour::Set(float, float, float, float); the descriptive
// spelling coexists with the historical constructor transcription in sprite.h.

#include "sprite.h"

void tColour::store_color4f(float r_, float g_, float b_, float a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
}
