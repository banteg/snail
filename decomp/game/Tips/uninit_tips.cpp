// uninit_tips / cRTipManager::UnInitTips @ 0x448d10 (thiscall, ret)

#include "tip_manager.h"

void cRTipManager::UnInitTips()
{
    cRTip* tip = tips;
    int count = TIP_SLOT_COUNT;
    do {
        if (tip->active == 1) {
            tip->UnInit();
        }
        ++tip;
        --count;
    } while (count != 0);
}
