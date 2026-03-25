/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: highlight_border @ 0x402800 */
/* selector: highlight_border */

// Sets the active highlight state on one frontend border/widget so hover/selection visuals render in the highlighted style.
int __thiscall sub_402800(_DWORD *this)
{
  int result; // eax

  result = *(this + 134);
  *(this + 131) = 1065353216;
  *(this + 135) = result;
  return result;
}

