#ifndef INPUT_POLLING_H
#define INPUT_POLLING_H

#include "win32_window_state.h"

// The startup loop passes the owned game window to every device poller. The
// keyboard and joystick implementations do not consume it, but their cdecl ABI
// still owns the argument and the caller releases all three arguments together.
int update_keyboard_input(HWND hwnd); // @ 0x44b870
int update_joystick_input(HWND hwnd); // @ 0x44b570
// Authored ReadImmediateDataMouse; Windows alone carries the owned HWND needed
// for DirectInput polling and clip-rectangle maintenance.
int update_mouse(HWND hwnd); // @ 0x44bc50

int enumerate_input_controllers(HWND hwnd, int* out_count); // @ 0x44b3c0
int release_input_controllers(); // @ 0x44b770
int initialize_keyboard_input(HWND hwnd); // @ 0x44b7d0
void release_keyboard_input(); // @ 0x44bb60
void initialize_mouse_authored_scale_from_clip_rect(); // @ 0x44bbb0
void update_mouse_authored_scale(float authored_width, float authored_height); // @ 0x44bbd0
float resolve_uncaptured_cursor_sensitivity_scale(float scale); // @ 0x44bc20
void click_mouse_screen(int slot, int x, int y); // @ 0x44c060
int release_mouse_input(); // @ 0x44c2c0

#endif
