// uninit_tips @ 0x448d10 (thiscall, ret)

#include "tip_manager.h"

void TipManager::uninit_tips()
{
    Tip* tip = tips;
    int count = 3;
    do {
        if (tip->active == 1) {
            tip->kill_tip_widgets();
        }
        ++tip;
        --count;
    } while (count != 0);
}
