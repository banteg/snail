/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_white @ 0x44dc50 */
/* selector: set_color_white */

// Thin wrapper around `set_color_grayscale` that initializes one destination color slot to opaque white.
int __thiscall sub_44DC50(_DWORD *this)
{
  return set_color_grayscale(this, 1065353216);
}

