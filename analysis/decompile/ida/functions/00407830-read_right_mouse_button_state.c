/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_right_mouse_button_state @ 0x407830 */
/* selector: read_right_mouse_button_state */

// Clears the companion right-button latch byte for the requested slot and returns the current right mouse button state byte.
unsigned __int8 __cdecl read_right_mouse_button_state(int slot)
{
  g_right_mouse_button_latch[slot] = 0;
  return g_right_mouse_button_state[slot];
}
