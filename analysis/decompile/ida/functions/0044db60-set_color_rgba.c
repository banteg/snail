/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_rgba @ 0x44db60 */
/* selector: set_color_rgba */

// Stores one four-float RGBA color tuple into the destination color/vector slot and returns the same destination pointer.
_DWORD *__thiscall sub_44DB60(_DWORD *this, int a2, int a3, int a4, int a5)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

