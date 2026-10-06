// update_tip_manager / cRTipManager::AI @ 0x448d80 (thiscall, ret)

#include "tip_manager.h"

void cRTipManager::AI()
{
    cRTip* tip = tips;
    int count = TIP_SLOT_COUNT;
    do {
        if (tip->active == 1) {
            tip->AI();
        }
        ++tip;
        --count;
    } while (count != 0);
}
