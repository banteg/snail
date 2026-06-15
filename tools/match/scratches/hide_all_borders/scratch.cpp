// hide_all_borders @ 0x4033f0 (thiscall, ret)

#include "border_batch_state.h"

class BorderManager {
public:
    int hide_all_borders();

    char unknown_000[0x38];
    BorderBatchState batch_state; // +0x38
};

int BorderManager::hide_all_borders()
{
    return batch_state.apply_all_border_visibility_mode(0);
}
