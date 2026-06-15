// set_color_alpha @ 0x44db80 (thiscall, ret 0x4)

#include "sprite.h"

int Color4f::set_color_alpha(int alpha_bits)
{
    *(int*)&a = alpha_bits;
    return alpha_bits;
}
