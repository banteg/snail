// clear_frame_timer_state @ 0x407910 (thiscall)

#include "frame_timer_state.h"

void FrameTimerState::clear_frame_timer_state()
{
    elapsed_ticks = 0;
    primary_timestamp = 0;
}
