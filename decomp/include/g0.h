// Shared G0.o functions, partial. iOS STABS name G0.h.
#ifndef G0_H
#define G0_H

void initialize_default_runtime_config(); // @ 0x406c20
int log_startup_timestamp(); // @ 0x406d30
void initialize_main_loop_display_state(); // @ 0x406d70
void initialize_main_loop_timing_state(); // @ 0x406da0
int handle_game_window_activate(); // @ 0x4072f0
int show_and_focus_game_window(); // @ 0x4073b0
char handle_game_window_deactivate(); // @ 0x407440
void minimize_game_window(); // @ 0x407490
int consume_mouse_wheel_delta(int slot); // @ 0x4077f0
unsigned char read_left_mouse_button_state(int slot); // @ 0x407810
unsigned char read_right_mouse_button_state(int slot); // @ 0x407830
int snapshot_current_display_mode(); // @ 0x407850
int restore_desktop_display_mode(); // @ 0x407860
int probe_display_mode_count(); // @ 0x407880
int* read_current_display_resolution(int* out_width, int* out_height); // @ 0x4078b0
char initialize_audio_subsystem(); // @ 0x407a10
int shutdown_bass_audio_window(); // @ 0x407b00
int construct_game_runtime(); // @ 0x407b60

#endif
