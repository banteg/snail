/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_ghost @ 0x43d230 */
/* selector: initialize_subgoldy_ghost */

unsigned int __thiscall sub_43D230(_DWORD *this, int a2)
{
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *v6; // ecx
  _DWORD *v7; // eax
  int v8; // ecx
  _DWORD *v9; // eax
  _DWORD *v10; // ecx
  int v11; // esi
  unsigned int result; // eax
  _DWORD v13[4]; // [esp+10h] [ebp-10h] BYREF

  v3 = allocate_sprite(g_sprite_manager, a2, 159, -1, -1);
  *(this + 38) = v3;
  v4 = v3[1];
  BYTE1(v4) |= 8u;
  v3[1] = v4;
  *(_DWORD *)(*(this + 38) + 104) = 0;
  *(_DWORD *)(*(this + 38) + 108) = 0;
  *(_DWORD *)(*(this + 38) + 120) = 0;
  v5 = set_color_rgba(v13, 1065353216, 1065353216, 1065353216, 1065353216);
  v6 = (_DWORD *)(*(this + 38) + 44);
  *v6 = *v5;
  v6[1] = v5[1];
  v6[2] = v5[2];
  v6[3] = v5[3];
  *(_DWORD *)(*(this + 38) + 96) = 1056964608;
  *(_DWORD *)(*(this + 38) + 100) = 1056964608;
  *(_DWORD *)(*(this + 38) + 72) = 1083179008;
  *(_DWORD *)(*(this + 38) + 76) = 1065353216;
  *(_DWORD *)(*(this + 38) + 80) = 0;
  v7 = allocate_sprite(g_sprite_manager, a2, 159, -1, -1);
  *(this + 39) = v7;
  v8 = v7[1];
  BYTE1(v8) |= 8u;
  v7[1] = v8;
  *(_DWORD *)(*(this + 39) + 104) = 0;
  *(_DWORD *)(*(this + 39) + 108) = 0;
  *(_DWORD *)(*(this + 39) + 120) = 0;
  v9 = set_color_rgba(v13, 1065353216, 1065353216, 1065353216, 1065353216);
  v10 = (_DWORD *)(*(this + 39) + 44);
  *v10 = *v9;
  v10[1] = v9[1];
  v10[2] = v9[2];
  v10[3] = v9[3];
  *(_DWORD *)(*(this + 39) + 96) = 1056964608;
  *(_DWORD *)(*(this + 39) + 100) = 1056964608;
  *(_DWORD *)(*(this + 39) + 72) = -1064304640;
  *(_DWORD *)(*(this + 39) + 76) = 1065353216;
  *(_DWORD *)(*(this + 39) + 80) = 0;
  *(_DWORD *)(*(this + 38) + 4) &= ~0x40u;
  v11 = *(this + 39);
  result = *(_DWORD *)(v11 + 4) & 0xFFFFFFBF;
  *(_DWORD *)(v11 + 4) = result;
  return result;
}

