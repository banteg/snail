/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_options_menu @ 0x41ace0 */
/* selector: initialize_options_menu */

// Constructs the Options screen widgets, seeds them from SnailMail.cfg, and links the fullscreen, sounds, music, and back controls. Cross-port Android and iOS symbols match this helper to `cROptions::Init()`.
float *__thiscall sub_41ACE0(int this)
{
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  float *result; // eax
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  hide_all_borders((int *)MEMORY[0x4DF904] + 723);
  *((_BYTE *)MEMORY[0x4DF904] + 1384) = 1;
  *(_DWORD *)(this + 20) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v2 = set_color_rgba(v7, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(_DWORD *)(this + 20), 20, MEMORY[0x4DFB08], 20, 1119092736, 75.0, (int)v2, 2, 0.0);
  *(float *)(*(_DWORD *)(this + 20) + 1784) = *(float *)(*(_DWORD *)(this + 20) + 1784) + 8.0;
  *(_DWORD *)(this + 24) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v7, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(_DWORD *)(this + 24), 9437188, aSoundsVolume, 20, 1119092736, 400.0, (int)v3, 2, 0.0);
  stack_widget_below(*(_DWORD *)(this + 24), *(_DWORD *)(this + 20));
  *(float *)(*(_DWORD *)(this + 24) + 380) = unk_4DF918;
  *(float *)(*(_DWORD *)(this + 24) + 384) = unk_4DF918;
  (***(void (__thiscall ****)(_DWORD))(this + 24))(*(_DWORD *)(this + 24));
  *(_DWORD *)(this + 28) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = set_color_rgba(v7, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(_DWORD *)(this + 28), 1048580, aMusicVolume, 20, 1119092736, 400.0, (int)v4, 2, 0.0);
  stack_widget_below(*(_DWORD *)(this + 28), *(_DWORD *)(this + 24));
  *(float *)(*(_DWORD *)(this + 28) + 380) = unk_4DF91C;
  *(float *)(*(_DWORD *)(this + 28) + 384) = unk_4DF91C;
  (***(void (__thiscall ****)(_DWORD))(this + 28))(*(_DWORD *)(this + 28));
  *(_DWORD *)(this + 16) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v5 = set_color_rgba(v7, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(_DWORD *)(this + 16), 20, aBack, 20, 1119092736, 400.0, (int)v5, 2, 0.0);
  result = stack_widget_below(*(_DWORD *)(this + 16), *(_DWORD *)(this + 28));
  *(float *)(this + 32) = unk_4DF918;
  return result;
}

