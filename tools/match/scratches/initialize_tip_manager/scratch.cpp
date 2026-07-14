// initialize_tip_manager @ 0x448cf0 (thiscall, ret)

#include "tip_manager.h"

void TipManager::initialize_tip_manager()
{
    Tip* tip = tips;
    int count = TIP_SLOT_COUNT;
    do {
        tip->active = 0;
        ++tip;
        --count;
    } while (count != 0);
}
