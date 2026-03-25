/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_border @ 0x4032a0 */
/* selector: allocate_border */

int __thiscall sub_4032A0(_DWORD *this)
{
  int v1; // eax
  _DWORD *i; // edx
  int result; // eax

  v1 = 0;
  for ( i = this + 521; *i; i += 457 )
  {
    if ( ++v1 >= 150 )
    {
      report_errorf(aRunOutOfBorder);
      return 0;
    }
  }
  result = (int)(this + 457 * v1 + 417);
  *(_DWORD *)(result + 412) = *((_DWORD *)MEMORY[0x4DF904] + 327);
  return result;
}

