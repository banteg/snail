/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_jet_particles @ 0x43a5b0 */
/* selector: initialize_jet_particles */

int __thiscall sub_43A5B0(char *this)
{
  char *v1; // esi
  int v2; // ebx
  _DWORD *v3; // eax
  int v4; // edx
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  int result; // eax
  int v9; // [esp+10h] [ebp-14h]
  int v10[4]; // [esp+14h] [ebp-10h] BYREF

  v1 = this + 32;
  v9 = 15;
  do
  {
    v2 = 2;
    do
    {
      v3 = allocate_sprite(unk_790F30, 1, 158, -1, -1);
      *(_DWORD *)v1 = v3;
      v4 = v3[1];
      BYTE1(v4) |= 8u;
      v3[1] = v4;
      *(_DWORD *)(*(_DWORD *)v1 + 104) = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 108) = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 112) = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 116) = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 100) = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 96) = 0;
      v5 = (_DWORD *)(*(_DWORD *)v1 + 84);
      v5[2] = 0;
      v5[1] = 0;
      *v5 = 0;
      *(_DWORD *)(*(_DWORD *)v1 + 120) = 0;
      v6 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065336439);
      v7 = (_DWORD *)(*(_DWORD *)v1 + 44);
      v1 += 16;
      --v2;
      *v7 = *v6;
      v7[1] = v6[1];
      v7[2] = v6[2];
      v7[3] = v6[3];
      *((_DWORD *)v1 - 3) = 0;
      *(_DWORD *)(*((_DWORD *)v1 - 4) + 40) = 0;
      *((_DWORD *)v1 - 2) = 0;
      *((_DWORD *)v1 - 1) = 1042983595;
    }
    while ( v2 );
    result = --v9;
  }
  while ( v9 );
  return result;
}

