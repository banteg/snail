// hide_star_field @ 0x434670 (thiscall)

#include "star_manager.h"

void StarManager::hide_star_field()
{
    int result = state;
    if (result != 0) {
        result = count;
        for (int i = 0; i < result; ++i) {
            entries[i].sprite->flags &= ~SPRITE_FLAG_RENDER_ENABLED;
            result = count;
        }
    }
}
