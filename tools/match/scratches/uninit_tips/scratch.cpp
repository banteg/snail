// uninit_tips @ 0x448d10 (thiscall, ret)

#include "tip_manager.h"

void TipManager::uninit_tips()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        if (slot->active == 1) {
            slot->kill_tip_widgets();
        }
        ++slot;
        --count;
    } while (count != 0);
}
