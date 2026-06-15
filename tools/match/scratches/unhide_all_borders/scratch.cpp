// unhide_all_borders @ 0x403400 (thiscall, ret)

#include "border_batch_state.h"

class BorderManager {
public:
    int unhide_all_borders();

    char unknown_000[0x38];
    BorderBatchState batch_state; // +0x38
};

int BorderManager::unhide_all_borders()
{
    return batch_state.apply_all_border_visibility_mode(1);
}
