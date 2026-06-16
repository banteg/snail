// hide_star_field @ 0x434670 (thiscall, ret int)

#include "star_field.h"

int StarField::hide_star_field()
{
    int result = active;
    if (result != 0) {
        result = count;
        for (int i = 0; i < result; ++i) {
            entries[i].sprite->flags &= ~0x40;
            result = count;
        }
    }
    return result;
}
