/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_border_init @ 0x4010e0 */
/* selector: hide_border_init */

void __thiscall sub_4010E0(_DWORD *this)
{
  int v1; // eax

  v1 = *(this + 104);
  if ( (v1 & 0x1000) == 0 )
  {
    BYTE1(v1) |= 0x10u;
    *(this + 17) = 0;
    *(this + 104) = v1;
    reset_tooltip((int)(this + 163));
  }
}

