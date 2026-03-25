/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhighlight_border @ 0x4027e0 */
/* selector: unhighlight_border */

// Clears the active highlight state on one frontend border/widget and restores its non-highlighted visual bits.
int __thiscall sub_4027E0(_DWORD *this)
{
  int result; // eax

  result = *(this + 133);
  *(this + 131) = 0;
  *(this + 135) = result;
  return result;
}

