// update_tip_manager @ 0x448d80 (thiscall, ret)

#include "tip_manager.h"

void TipManager::update_tip_manager()
{
    Tip* tip = tips;
    int count = TIP_SLOT_COUNT;
    do {
        if (tip->active == 1) {
            tip->update_tip();
        }
        ++tip;
        --count;
    } while (count != 0);
}
