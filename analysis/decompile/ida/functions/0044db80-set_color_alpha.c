/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_alpha @ 0x44db80 */
/* selector: set_color_alpha */

// Stores one float alpha value into the destination color slot's alpha lane and returns that same alpha value.
int __thiscall sub_44DB80(_DWORD *this, int a2)
{
  *(this + 3) = a2;
  return a2;
}

