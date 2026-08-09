// initialize_tip_manager / cRTipManager::Init @ 0x448cf0 (thiscall, ret)

#include "tip_manager.h"

void cRTipManager::Init()
{
    cRTip* tip = tips;
    int count = TIP_SLOT_COUNT;
    do {
        tip->active = 0;
        ++tip;
        --count;
    } while (count != 0);
}
