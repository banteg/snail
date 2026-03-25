/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_times_up @ 0x445e20 */
/* selector: update_times_up */

void __thiscall sub_445E20(int this)
{
  double v2; // st7

  if ( *(_DWORD *)this )
  {
    if ( *(_DWORD *)this == 1 )
    {
      v2 = *(float *)(this + 12) + *(float *)(this + 8);
      *(float *)(this + 8) = v2;
      if ( v2 > 1.0 )
        *(_DWORD *)this = 2;
    }
    else if ( *(_DWORD *)this == 2 )
    {
      uninit_times_up((_DWORD **)this);
      kill_subgoldy((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]);
      *(_DWORD *)this = 0;
    }
  }
}

