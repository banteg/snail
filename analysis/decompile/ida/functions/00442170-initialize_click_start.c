/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_click_start @ 0x442170 */
/* selector: initialize_click_start */

// Initializes the `Click to Start` prompt owner for the subgame intro and hides that prompt immediately when the app-side replay-launch active bit is already set, so persistent replay starts skip the normal click gate.
void __thiscall sub_442170(int this, int a2)
{
  _DWORD *v3; // eax
  int v4; // eax
  char *v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  _DWORD *v9; // ecx
  _DWORD v10[4]; // [esp+8h] [ebp-10h] BYREF

  *(_DWORD *)(this + 132) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1022739087);
  initialize_frontend_widget(*(_DWORD *)(this + 132), 4194306, aClickToStart, 20, 0, 200.0, (int)v3, 2, 0.0);
  hide_border_init(*(_DWORD **)(this + 132));
  v4 = *(_DWORD *)(this + 4);
  *(_BYTE *)(this + 168) = 1;
  *(_DWORD *)(this + 152) = a2;
  if ( (v4 & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v5 = (char *)MEMORY[0x4DF904] + 1452;
    v6 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v6 )
    {
      *(_DWORD *)(v6 + 8) = this;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v5 + 8) + 12) = *(_DWORD *)v5;
      v7 = *(_DWORD *)(*(_DWORD *)v5 + 8);
      *(_DWORD *)v5 = v7;
      *(_DWORD *)(v7 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v5 = this;
      *(_DWORD *)(this + 8) = 0;
      *(_DWORD *)(*(_DWORD *)v5 + 12) = 0;
    }
    *(_DWORD *)(this + 4) |= 0x200u;
  }
  v8 = *(_DWORD *)(this + 152);
  *(_DWORD *)(this + 128) = 2;
  *(_DWORD *)(v8 + 772) = 0;
  *(_DWORD *)(this + 28) = 0;
  *(_DWORD *)(this + 32) = 0;
  v9 = *(_DWORD **)(this + 132);
  if ( *((_BYTE *)MEMORY[0x4DF904] + 17198056) )
    hide_border_init(v9);
  else
    unhide_border_init(v9);
}

