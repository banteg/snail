/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_key_down @ 0x44bb40 */
/* selector: is_key_down */

// Returns true when the supplied keyboard scancode is down in the current DirectInput key-state table.
uint8_t __cdecl is_key_down(uint8_t key_code)
{
  return g_keyboard_current_state[key_code] == 0x80;
}
