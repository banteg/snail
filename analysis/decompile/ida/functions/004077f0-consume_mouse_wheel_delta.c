/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: consume_mouse_wheel_delta @ 0x4077f0 */
/* selector: consume_mouse_wheel_delta */

// Returns the latched mouse-wheel delta for the requested slot and clears it back to zero.
int __cdecl sub_4077F0(int a1)
{
  int result; // eax

  result = unk_4DFAD0[a1];
  unk_4DFAD0[a1] = 0;
  return result;
}

