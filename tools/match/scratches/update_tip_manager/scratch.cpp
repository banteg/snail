// update_tip_manager @ 0x448d80 (fastcall, ret)

#include "tip_manager.h"

void TipManager::update_tip_manager()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        if (slot->active == 1) {
            slot->update_tip();
        }
        ++slot;
        --count;
    } while (count != 0);
}
