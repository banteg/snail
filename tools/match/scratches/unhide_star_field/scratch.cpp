// unhide_star_field @ 0x4346b0 (thiscall)

#include "star_manager.h"

void StarManager::unhide_star_field()
{
    int result = state;
    if (result != 0) {
        result = count;
        for (int i = 0; i < result; ++i) {
            entries[i].sprite->flags |= SPRITE_FLAG_RENDER_ENABLED;
            result = count;
        }
    }
}
