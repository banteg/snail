// enqueue_tip_message @ 0x448d30 (thiscall, ret 0x8)

#include "tip_manager.h"

int report_errorf(char* format, ...);

TipSlot* TipManager::enqueue_tip_message(
    TipMessageDefinition* definition,
    int show_disable_button)
{
    int index = 0;
    TipSlot* slot;
    slot = slots;

    while (1) {
        if (slot->active == 0) {
            break;
        }

        ++index;
        ++slot;
        if (index >= 3) {
            report_errorf("Run out of Tips");
            return 0;
        }
    }

    TipSlot* result = &slots[index];
    result->initialize_tip(definition, show_disable_button);
    return result;
}
