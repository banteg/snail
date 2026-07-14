// pack_color_rgba_u8 @ 0x44dbf0 (thiscall, ret 0x4)

#include "sprite.h"

tColourSmall* tColourSmall::pack_color_rgba_u8(Color4f* color)
{
    r = (unsigned char)(color->r * 255.0f);
    g = (unsigned char)(color->g * 255.0f);
    b = (unsigned char)(color->b * 255.0f);
    a = (unsigned char)(color->a * 255.0f);
    return this;
}
