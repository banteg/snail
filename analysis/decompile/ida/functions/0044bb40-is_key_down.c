/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_key_down @ 0x44bb40 */
/* selector: is_key_down */

// Returns true when the supplied keyboard scancode is down in the current DirectInput key-state table.
bool __cdecl sub_44BB40(unsigned __int8 a1)
{
  return MEMORY[0x777C4C][a1] == (char)0x80;
}

