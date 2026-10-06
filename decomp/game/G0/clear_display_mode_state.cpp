// clear_display_mode_state @ 0x407910 (thiscall)

#include "display_mode_state.h"

void DisplayModeState::clear_display_mode_state()
{
    current_mode = 0;
    queued_view_sample_count = 0;
}
