/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_key_pressed_edge @ 0x44bb10 */
/* selector: is_key_pressed_edge */

// Returns true when the supplied keyboard scancode is down in the current DirectInput key-state table and was up in the previous frame's table.
bool __cdecl sub_44BB10(unsigned __int8 a1)
{
  return MEMORY[0x777C4C][a1] == (char)0x80 && !MEMORY[0x777B4C][a1];
}

