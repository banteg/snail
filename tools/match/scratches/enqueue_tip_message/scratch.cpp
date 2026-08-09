// enqueue_tip_message / cRTipManager::TipNew @ 0x448d30 (thiscall, ret 0x8)

#include "tip_manager.h"

int report_errorf(char* format, ...);

cRTip* cRTipManager::TipNew(
    cRTipData* definition,
    int hide_disable_button)
{
    int index = 0;
    cRTip* tip;
    tip = tips;

    while (1) {
        if (tip->active == 0) {
            break;
        }

        ++index;
        ++tip;
        if (index >= TIP_SLOT_COUNT) {
            report_errorf("Run out of Tips");
            return 0;
        }
    }

    cRTip* result = &tips[index];
    result->Init(definition, hide_disable_button);
    return result;
}
