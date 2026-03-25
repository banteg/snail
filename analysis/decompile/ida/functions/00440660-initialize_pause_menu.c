/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_pause_menu @ 0x440660 */
/* selector: initialize_pause_menu */

void __thiscall sub_440660(int *this)
{
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD v5[4]; // [esp+4h] [ebp-10h] BYREF

  *(this + 1) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v2 = set_color_rgba(v5, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 1), 20, aEndGame, 20, 0, 145.0, (int)v2, 2, 0.0);
  set_frontend_widget_shortcut_key((_DWORD *)*(this + 1), 11);
  *this = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v5, 1065353216, 1065353216, 1065353216, 1022739087);
  initialize_frontend_widget(*this, 20, aOptions, 20, 0, 190.0, (int)v3, 2, 0.0);
  set_frontend_widget_shortcut_key((_DWORD *)*this, 111);
  layout_frontend_widget(*this);
  stack_widget_below(*this, *(this + 1));
  *(this + 2) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = set_color_rgba(v5, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 2), 20, aResume, 20, 0, 320.0, (int)v4, 2, 0.0);
  set_frontend_widget_shortcut_key((_DWORD *)*(this + 2), 5);
  stack_widget_below(*(this + 2), *this);
  capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
}

