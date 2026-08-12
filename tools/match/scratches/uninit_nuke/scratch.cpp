// uninit_nuke @ 0x4470e0 (thiscall, ret)

#include "nuke.h"

void cRNuke::uninit_nuke()
{
    if (state == NUKE_STATE_ACTIVE) {
        for (int i = 0; i < NUKE_SPRITE_SLOT_COUNT; i++) {
            sprite_slots[i]->Kill();
        }
        state = NUKE_STATE_INACTIVE;
    }
}
