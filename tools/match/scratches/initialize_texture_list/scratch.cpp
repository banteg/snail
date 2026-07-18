// initialize_texture_list @ 0x44e800 (thiscall, ret 0x4)

#include "sprite.h"

void TextureRefList::initialize_texture_list(int capacity_)
{
    count = 0;
    capacity = capacity_;
}
