// store_color4f @ 0x44dbb0 (thiscall, ret 0x10)

#include "sprite.h"

int Color4f::store_color4f(int r_, int g_, int b_, int a_)
{
    *(int*)&r = r_;
    *(int*)&g = g_;
    *(int*)&b = b_;
    *(int*)&a = a_;
    return b_;
}
