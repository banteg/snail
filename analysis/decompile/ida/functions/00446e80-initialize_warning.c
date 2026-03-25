/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_warning @ 0x446e80 */
/* selector: initialize_warning */

void __thiscall sub_446E80(int *this)
{
  _DWORD *v2; // eax
  _DWORD v3[4]; // [esp+4h] [ebp-10h] BYREF

  *(this + 3) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v2 = set_color_rgba(v3, 1065353216, 1065353216, 1065353216, 1065336439);
  initialize_frontend_sprite_button(*(this + 3), 4196354, 94, 1133510656, 1115684864, v2, 0.0, 4);
  *(_DWORD *)(*(this + 3) + 376) = 0;
  hide_border_init((_DWORD *)*(this + 3));
  *(this + 2) = 1034594987;
  *(this + 1) = 0;
  *this = 0;
}

