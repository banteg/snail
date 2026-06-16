// destroy_star_field @ 0x434270 (thiscall)

#include "star_field.h"

int StarField::destroy_star_field()
{
    int i = 0;
    int result = count;
    for (; i < result; ++i) {
        entries[i].active = 0;
        entries[i].sprite->kill_sprite();
        result = count;
    }

    state = 0;
    return result;
}
