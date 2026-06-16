// initialize_tip_manager @ 0x448cf0 (thiscall, ret)

#include "tip_manager.h"

void TipManager::initialize_tip_manager()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        slot->active = 0;
        ++slot;
        --count;
    } while (count != 0);
}
