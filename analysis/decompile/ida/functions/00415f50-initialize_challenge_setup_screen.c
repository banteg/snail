/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_challenge_setup_screen @ 0x415f50 */
/* selector: initialize_challenge_setup_screen */

// Builds the mode-1 front-end setup screen with Select Difficulty, Select Speed, Play, Watch Replay, and Back controls before challenge gameplay starts.
float *__thiscall sub_415F50(int *this)
{
  float *result; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  float v8; // [esp+4h] [ebp-54h]
  _DWORD v9[4]; // [esp+8h] [ebp-50h] BYREF
  _DWORD v10[4]; // [esp+18h] [ebp-40h] BYREF
  _DWORD v11[4]; // [esp+28h] [ebp-30h] BYREF
  _DWORD v12[4]; // [esp+38h] [ebp-20h] BYREF
  _DWORD v13[4]; // [esp+48h] [ebp-10h] BYREF

  capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
  load_frontend_level_by_mode_and_index((char *)(*this + 43124), *(_DWORD *)(*this + 64), *(_DWORD *)(*this + 68));
  result = (float *)(*(_DWORD *)(*this + 64) - 1);
  if ( *(_DWORD *)(*this + 64) == 1 )
  {
    *(this + 8) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v3 = set_color_rgba(v9, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(this + 8), 1048580, aSelectDifficul, 20, 1101004800, 80.0, (int)v3, 2, 0.0);
    *(float *)(*(this + 8) + 380) = (double)unk_4DF960 * 0.0099999998;
    *(_DWORD *)(*(this + 8) + 384) = *(_DWORD *)(*(this + 8) + 380);
    (**(void (__thiscall ***)(_DWORD))*(this + 8))(*(this + 8));
    *(this + 7) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v4 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(this + 7), 1048580, aSelectSpeed, 20, 1101004800, 145.0, (int)v4, 2, 0.0);
    *(float *)(*(this + 7) + 380) = (double)unk_4DF958 * 0.0099999998;
    *(_DWORD *)(*(this + 7) + 384) = *(_DWORD *)(*(this + 7) + 380);
    stack_widget_below(*(this + 7), *(this + 8));
    (**(void (__thiscall ***)(_DWORD))*(this + 7))(*(this + 7));
    v8 = 0.0;
    if ( *(_DWORD *)(*this + 16461904) == 1 )
      v8 = 100.0;
    *(this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v5 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(this + 4), 1073741846, aPlay, 20, 1101004800, 250.0, (int)v5, 2, v8);
    stack_widget_below(*(this + 4), *(this + 7));
    *(this + 9) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v6 = set_color_rgba(v12, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(this + 9), 1073741846, aWatchReplay, 20, 1101004800, 70.0, (int)v6, 2, -100.0);
    stack_widget_below(*(this + 9), *(this + 7));
    if ( *(_DWORD *)(*this + 16461904) != 1 )
      hide_border_init((_DWORD *)*(this + 9));
    *(this + 6) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v7 = set_color_rgba(v13, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(this + 6), 22, aBack, 20, 1101004800, 20.0, (int)v7, 2, 0.0);
    return stack_widget_below(*(this + 6), *(this + 9));
  }
  return result;
}

