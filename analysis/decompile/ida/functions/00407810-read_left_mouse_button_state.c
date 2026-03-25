/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_left_mouse_button_state @ 0x407810 */
/* selector: read_left_mouse_button_state */

// Clears the companion left-button latch byte for the requested slot and returns the current left mouse button state byte.
char __cdecl sub_407810(int a1)
{
  unk_4B7764[a1] = 0;
  return unk_4B7234[a1];
}

