/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip @ 0x448a40 */
/* selector: initialize_tip */

// Builds one gameplay tip slot, including the main border widget, optional OK or Disable buttons, and the timed auto-dismiss rate for transient tips.
char __thiscall sub_448A40(_DWORD *this, int a2, int a3)
{
  int v4; // edi
  _DWORD *v5; // eax
  int v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  int v10; // ecx
  char *v11; // ecx
  char result; // al
  int v13; // [esp-8h] [ebp-24h]
  float v14; // [esp-4h] [ebp-20h]
  float v15; // [esp+0h] [ebp-1Ch]
  float v16; // [esp+0h] [ebp-1Ch]
  float v17; // [esp+0h] [ebp-1Ch]
  _DWORD v18[4]; // [esp+Ch] [ebp-10h] BYREF

  *this = 1;
  if ( a2 )
    *(this + 2) = a2;
  else
    *(this + 2) = &unk_4AC5C8;
  *(this + 3) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = *(this + 2);
  v14 = *(float *)(v4 + 4);
  v13 = (unsigned __int8)(~(unsigned __int8)*(_DWORD *)v4 & 4) >> 1;
  v5 = set_color_rgba(v18, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(this + 3),
    2,
    *(char **)(v4 + 16),
    20,
    *(_DWORD *)(v4 + 4),
    *(float *)(v4 + 8),
    (int)v5,
    v13,
    v14);
  v6 = *(this + 2);
  if ( (*(_BYTE *)v6 & 2) != 0 )
  {
    *(this + 6) = 0;
    *((float *)this + 7) = 1.0 / (*(float *)(v6 + 12) * 60.0);
  }
  if ( (*(_BYTE *)v6 & 1) != 0 )
  {
    *(this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    if ( a3 )
    {
      v17 = *(float *)(*(this + 2) + 4);
      v9 = set_color_rgba(v18, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(this + 4), 20, aOk, 20, 0, 0.0, (int)v9, 2, v17);
      v10 = *(this + 3);
      *(this + 5) = 0;
      stack_widget_below(*(this + 4), v10);
    }
    else
    {
      v15 = *(float *)(*(this + 2) + 4) + 40.0;
      v7 = set_color_rgba(v18, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(this + 4), 20, aOk, 20, 0, 0.0, (int)v7, 2, v15);
      *(this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v16 = *(float *)(*(this + 2) + 4) - 60.0;
      v8 = set_color_rgba(v18, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(this + 5), 20, aDisable, 20, 0, 0.0, (int)v8, 2, v16);
      stack_widget_below(*(this + 5), *(this + 3));
      stack_widget_below(*(this + 4), *(this + 3));
    }
  }
  else
  {
    *(this + 4) = 0;
    *(this + 5) = 0;
  }
  v11 = (char *)*(this + 2);
  *(this + 1) = *((_DWORD *)MEMORY[0x4DF904] + 110);
  result = *v11;
  if ( (*v11 & 1) != 0 )
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 22;
  return result;
}

