// Headless input: no devices, so every poll leaves the recovered input state
// as it is. Stage 4 feeds SDL3 events into the same state.

#include "input_polling.h"

int update_keyboard_input(HWND) { return 0; }
int update_joystick_input(HWND) { return 0; }
int update_mouse(HWND) { return 0; }
int read_repeating_text_input_key_code() { return 0; }
