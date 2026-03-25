/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_right_mouse_button_state @ 0x407830 */
/* selector: read_right_mouse_button_state */

// Clears the companion right-button latch byte for the requested slot and returns the current right mouse button state byte.
char __cdecl sub_407830(int a1)
{
  unk_4B7230[a1] = 0;
  return MEMORY[0x4B7640][a1];
}

