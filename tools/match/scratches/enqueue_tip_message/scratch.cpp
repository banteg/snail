// enqueue_tip_message @ 0x448d30 (thiscall, ret 0x8)

#include "tip_manager.h"

int report_errorf(char* format, ...);

Tip* TipManager::enqueue_tip_message(
    TipData* definition,
    int hide_disable_button)
{
    int index = 0;
    Tip* tip;
    tip = tips;

    while (1) {
        if (tip->active == 0) {
            break;
        }

        ++index;
        ++tip;
        if (index >= 3) {
            report_errorf("Run out of Tips");
            return 0;
        }
    }

    Tip* result = &tips[index];
    result->initialize_tip(definition, hide_disable_button);
    return result;
}
