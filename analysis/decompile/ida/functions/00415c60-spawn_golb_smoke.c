/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_smoke @ 0x415c60 */
/* selector: spawn_golb_smoke */

int __thiscall sub_415C60(int this, float *a2)
{
  float *v3; // esi
  int v4; // ecx
  double v5; // st7
  float *v6; // eax
  int v7; // eax
  float *v8; // ecx
  double v9; // st7
  float v10; // eax
  int result; // eax
  float v12; // [esp+8h] [ebp-10h] BYREF
  float v13; // [esp+Ch] [ebp-Ch]
  float v14; // [esp+10h] [ebp-8h]

  v3 = (float *)allocate_sprite(g_sprite_manager, *(_DWORD *)(*(_DWORD *)(this + 632) + 896), 128, -1, -1);
  v4 = *((_DWORD *)v3 + 1);
  v3[26] = 0.0;
  BYTE1(v4) |= 8u;
  *((_DWORD *)v3 + 1) = v4;
  v5 = *(float *)(*(_DWORD *)(this + 624) + 56) * 0.16666667;
  v3[28] = 0.0;
  v3[27] = v5;
  v3[29] = *(float *)(*(_DWORD *)(this + 624) + 56) * 0.41666669;
  v6 = (float *)set_color_rgba(&v12, 1065353216, 1065353216, 1065353216, 1065353216);
  v3[11] = *v6;
  v3[12] = v6[1];
  v3[13] = v6[2];
  v7 = *((_DWORD *)v6 + 3);
  v3[24] = 0.1;
  v3[25] = 0.5;
  *((_DWORD *)v3 + 14) = v7;
  v8 = v3 + 21;
  v3 += 18;
  v12 = *(float *)(this + 588) * 0.40000001;
  v13 = *(float *)(this + 592) * 0.40000001;
  v9 = *(float *)(this + 596) * 0.40000001;
  v10 = v13;
  *v8 = v12;
  v3[12] = 0.0;
  v8[1] = v10;
  v14 = v9;
  v8[2] = v14;
  *v3 = *a2;
  v3[1] = a2[1];
  result = *((_DWORD *)a2 + 2);
  *((_DWORD *)v3 + 2) = result;
  return result;
}

