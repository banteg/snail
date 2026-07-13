// Process-owned frame-loop flags and timing state.
#ifndef MAIN_LOOP_STATE_H
#define MAIN_LOOP_STATE_H

extern unsigned char g_render_queue_active; // data_4b7236
extern float g_mean_update_steps_per_frame; // data_4b7638
extern float g_current_frame_update_steps; // data_4b763c
extern unsigned char g_window_deactivated; // data_4b7654
extern unsigned char g_fixed_update_abort_requested; // data_4b7758
extern unsigned char g_frame_render_requested; // data_4b7759
extern float g_main_loop_frame_count; // data_4b7768

extern unsigned char g_main_loop_exit_requested; // data_4df864
extern unsigned char g_game_initialization_pending; // data_4df90c
extern float g_frame_time_accumulator; // data_4dfafc
extern float g_previous_frame_timestamp_seconds; // data_4dfb00
extern float g_current_frame_timestamp_seconds; // data_4dfb04

#endif
