/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_grayscale @ 0x44db90 */
/* selector: set_color_grayscale */

// Stores one uniform grayscale RGB value into the destination color slot, forces alpha to `1.0`, and returns the grayscale input.
int __thiscall sub_44DB90(_DWORD *this, int a2)
{
  *(this + 3) = 1065353216;
  *this = a2;
  *(this + 1) = a2;
  *(this + 2) = a2;
  return a2;
}

