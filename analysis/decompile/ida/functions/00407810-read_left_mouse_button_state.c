/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_left_mouse_button_state @ 0x407810 */
/* selector: read_left_mouse_button_state */

// Clears the companion left-button latch byte for the requested slot and returns the current left mouse button state byte.
unsigned __int8 __cdecl read_left_mouse_button_state(int slot)
{
  g_left_mouse_button_latch[slot] = 0;
  return g_left_mouse_button_state[slot];
}
