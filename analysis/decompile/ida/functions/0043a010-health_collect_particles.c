/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: health_collect_particles @ 0x43a010 */
/* selector: health_collect_particles */

char __thiscall sub_43A010(int this, int a2)
{
  char result; // al
  char *v4; // esi
  _DWORD *v5; // eax
  float *v6; // edi
  int v7; // eax
  _DWORD *v8; // edx
  float v9; // ebp
  bool v10; // cc
  int v11; // [esp+4h] [ebp-34h]
  float v12; // [esp+8h] [ebp-30h]
  float v13; // [esp+8h] [ebp-30h]
  float v14; // [esp+Ch] [ebp-2Ch]
  float v15; // [esp+10h] [ebp-28h]
  float v16; // [esp+20h] [ebp-18h]
  float v17; // [esp+24h] [ebp-14h]
  _DWORD v18[4]; // [esp+28h] [ebp-10h] BYREF

  result = byte_4DF934;
  if ( (byte_4DF934 & 0x10) != 0 )
  {
    v11 = 0;
    do
    {
      v4 = (char *)allocate_sprite(g_sprite_manager, *(_DWORD *)(this + 896), 128, -1, -1);
      *((_DWORD *)v4 + 1) |= 0x800u;
      *((_DWORD *)v4 + 26) = 0;
      *((_DWORD *)v4 + 27) = 1026206379;
      *((_DWORD *)v4 + 30) = -1185827049;
      v5 = set_color_rgba(v18, 1065353216, 1061158912, 1061158912, 1065353216);
      *((_DWORD *)v4 + 11) = *v5;
      v6 = (float *)(v4 + 72);
      *((_DWORD *)v4 + 12) = v5[1];
      *((_DWORD *)v4 + 13) = v5[2];
      v7 = v5[3];
      *((_DWORD *)v4 + 24) = 1036831949;
      *((_DWORD *)v4 + 25) = 1056964608;
      *((_DWORD *)v4 + 14) = v7;
      v8 = (_DWORD *)(*(_DWORD *)(a2 + 100) + 72);
      v12 = (double)v11 * 0.78539819;
      v9 = v12;
      *((_DWORD *)v4 + 18) = *v8;
      *((_DWORD *)v4 + 19) = v8[1];
      *((_DWORD *)v4 + 20) = v8[2];
      v14 = *(float *)(this + 1048) * 0.40000001;
      v13 = cosine(v12) * 0.015;
      v4 += 84;
      v15 = sine(v9) * 0.015;
      *(float *)v4 = v15;
      *((float *)v4 + 1) = v13;
      *((float *)v4 + 2) = v14;
      v16 = *(float *)(this + 1044) * 3.0;
      v17 = *(float *)(this + 1048) * 3.0;
      *v6 = *(float *)(this + 1040) * 3.0 + *v6;
      v6[1] = v16 + v6[1];
      result = v11 + 1;
      v10 = ++v11 < 8;
      v6[2] = v17 + v6[2];
    }
    while ( v10 );
  }
  return result;
}

