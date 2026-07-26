/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_key_pressed_edge @ 0x44bb10 */
/* selector: is_key_pressed_edge */

// Returns true when the supplied keyboard scancode is down in the current DirectInput key-state table and was up in the previous frame's table.
uint8_t __cdecl is_key_pressed_edge(uint8_t key_code)
{
  return g_keyboard_current_state[key_code] == 0x80 && g_keyboard_previous_state[key_code] == 0;
}
