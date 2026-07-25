#ifndef SNAIL_MAIN_LOOP_TYPES_H
#define SNAIL_MAIN_LOOP_TYPES_H

/* Human-facing WinMain contract; replays preserve pointer width per tool. */
int __stdcall game_startup_and_main_loop(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd);

int* __cdecl read_current_display_resolution(
    int* out_width,
    int* out_height);

unsigned char __cdecl read_left_mouse_button_state(int slot);
unsigned char __cdecl read_right_mouse_button_state(int slot);

extern HINSTANCE g_application_instance;

/* Process-owned display dimensions and authored 640x480 coordinate space. */
extern int g_current_display_width;
extern int g_current_display_height;
extern float g_authored_view_width;
extern float g_authored_view_height;

/* Process-owned fixed-step frame-loop state. */
extern unsigned char g_render_queue_active;
extern float g_mean_update_steps_per_frame;
extern float g_current_frame_update_steps;

/*
 * Process-owned two-slot Win32 button banks. Each reader consumes its button
 * latch and returns the corresponding live state without claiming the gaps
 * between these independent globals.
 */
extern unsigned char g_right_mouse_button_latch[2];
extern unsigned char g_left_mouse_button_state[2];
extern unsigned char g_right_mouse_button_state[2];
extern unsigned char g_left_mouse_button_latch[2];

/* Adjacent owner preserved when splitting IDA's stale float[3] item. */
extern int g_estimated_texture_vram_bytes;
extern unsigned char g_window_deactivated;
extern unsigned char g_fixed_update_abort_requested;
extern unsigned char g_frame_render_requested;
extern float g_main_loop_frame_count;
extern int g_pending_window_deactivate;
extern unsigned char g_main_loop_exit_requested;
extern unsigned char g_game_initialization_pending;
extern float g_frame_time_accumulator;
extern float g_previous_frame_timestamp_seconds;
extern float g_current_frame_timestamp_seconds;

#endif
