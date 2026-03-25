/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_border @ 0x403360 */
/* selector: kill_border */

void __stdcall sub_403360(_DWORD *a1)
{
  int v1; // eax

  if ( a1 )
  {
    v1 = a1[104];
    if ( v1 )
    {
      if ( (v1 & 0x400) == 0 )
      {
        LOBYTE(v1) = v1 & 1;
        BYTE1(v1) |= 2u;
        a1[104] = v1;
        if ( (v1 & 0x100000) != 0 )
        {
          kill_border(a1[454]);
          kill_border(a1[455]);
          kill_border(a1[456]);
        }
      }
    }
  }
}

