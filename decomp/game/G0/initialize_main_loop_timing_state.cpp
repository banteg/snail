// initialize_main_loop_timing_state @ 0x406da0 (cdecl)

#include "main_loop_state.h"

void initialize_main_loop_timing_state()
{
    g_mean_update_steps_per_frame = 1.0f;
    g_current_frame_update_steps = 1.0f;
    g_main_loop_frame_count = 1.0f;
}
