#ifndef INPUT_POLLING_H
#define INPUT_POLLING_H

#include "win32_window_state.h"

// The startup loop passes the owned game window to every device poller. The
// keyboard and joystick implementations do not consume it, but their cdecl ABI
// still owns the argument and the caller releases all three arguments together.
int update_keyboard_input(HWND hwnd); // @ 0x44b870
int update_joystick_input(HWND hwnd); // @ 0x44b570
int update_mouse(HWND hwnd); // @ 0x44bc50

#endif
