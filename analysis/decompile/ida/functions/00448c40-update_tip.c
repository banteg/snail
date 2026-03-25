/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip @ 0x448c40 */
/* selector: update_tip */

// Runs one gameplay tip slot, handling hide or show state, button-click consumption, timed expiry, and the final teardown or UI-state restore path.
void __thiscall sub_448C40(int this)
{
  _DWORD *v2; // ecx
  int v3; // ecx
  int v4; // eax
  double v5; // st7

  v2 = *(_DWORD **)(this + 12);
  if ( *((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    hide_border_init(v2);
  }
  else
  {
    unhide_border_init(v2);
    v3 = *(_DWORD *)(this + 16);
    if ( v3 && (v4 = *(_DWORD *)(v3 + 416), (v4 & 0x20) != 0)
      || (v3 = *(_DWORD *)(this + 20)) != 0 && (v4 = *(_DWORD *)(v3 + 416), (v4 & 0x20) != 0) )
    {
      LOBYTE(v4) = v4 & 0xDF;
      *(_DWORD *)(v3 + 416) = v4;
      *((_DWORD *)MEMORY[0x4DF904] + 110) = *(_DWORD *)(this + 4);
      kill_tip_widgets((_DWORD **)this);
      unhide_all_borders((int *)MEMORY[0x4DF904] + 723);
      *(_DWORD *)this = 0;
    }
    else if ( (**(_BYTE **)(this + 8) & 2) != 0 )
    {
      v5 = *(float *)(this + 28) + *(float *)(this + 24);
      *(float *)(this + 24) = v5;
      if ( v5 > 1.0 )
      {
        kill_tip_widgets((_DWORD **)this);
        *(_DWORD *)this = 0;
      }
    }
  }
}

