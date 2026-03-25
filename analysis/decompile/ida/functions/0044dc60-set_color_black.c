/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_black @ 0x44dc60 */
/* selector: set_color_black */

// Thin wrapper around `set_color_grayscale` that initializes one destination color slot to opaque black.
int __thiscall sub_44DC60(_DWORD *this)
{
  return set_color_grayscale(this, 0);
}

