// initialize_main_loop_frame_state @ 0x406d70 (cdecl)

#include "frame_timer_state.h"
#include "transform_matrix.h"

extern FrameTimerState g_frame_timer_state; // data_4df9e0
extern unsigned char g_window_deactivated; // data_4b7654
extern int g_pending_window_deactivate; // data_4df860
extern TransformMatrix g_object_texture_transform_matrix; // data_5031d8
extern float g_mean_update_steps_per_frame; // data_4b7638
extern float g_current_frame_update_steps; // data_4b763c
extern float g_main_loop_frame_count; // data_4b7768

void initialize_main_loop_frame_state()
{
    g_frame_timer_state.clear_frame_timer_state();
    g_window_deactivated = 0;
    g_pending_window_deactivate = 0;
    set_matrix_identity(&g_object_texture_transform_matrix);

    g_mean_update_steps_per_frame = 1.0f;
    g_current_frame_update_steps = 1.0f;
    g_main_loop_frame_count = 1.0f;
}
