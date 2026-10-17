// Shared GDX.o functions, partial. The index-buffer error names GDX.h.
#ifndef GDX_H
#define GDX_H

int initialize_game_window_and_input_wrapper(char* window_name); // @ 0x4119c0
int initialize_game_window_and_input(char* window_name); // @ 0x4119d0
int uninitialize_input_devices(); // @ 0x411d80
int end_overlay_render_state(); // @ 0x411de0
int begin_overlay_render_state(); // @ 0x411e10

#endif
