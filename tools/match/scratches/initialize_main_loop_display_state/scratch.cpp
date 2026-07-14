// initialize_main_loop_display_state @ 0x406d70 (cdecl)

#include "display_mode_state.h"
#include "main_loop_state.h"
#include "transform_matrix.h"

extern DisplayModeState g_display_mode_state; // data_4df9e0
extern TransformMatrix g_object_texture_transform_matrix; // data_5031d8

void initialize_main_loop_timing_state(); // @ 0x406da0

void initialize_main_loop_display_state()
{
    g_display_mode_state.clear_display_mode_state();
    g_window_deactivated = 0;
    g_pending_window_deactivate = 0;
    g_object_texture_transform_matrix.set_matrix_identity();
    initialize_main_loop_timing_state();
}
