/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_garbage_smoke_particle @ 0x43d5a0 */
/* selector: spawn_garbage_smoke_particle */

char __thiscall sub_43D5A0(_DWORD *this, float *a2, float *a3, int a4)
{
  int v4; // eax
  float *v6; // esi
  int v7; // eax
  double v8; // st7
  float *v9; // eax
  int v10; // eax
  float *v11; // ecx
  double v12; // st7
  float v13; // eax
  float v15; // [esp+4h] [ebp-10h] BYREF
  float v16; // [esp+8h] [ebp-Ch]
  float v17; // [esp+Ch] [ebp-8h]

  LOBYTE(v4) = byte_4DF934;
  if ( (byte_4DF934 & 0x10) != 0 )
  {
    v6 = (float *)allocate_sprite(unk_790F30, *(_DWORD *)(a4 + 896), 33, -1, -1);
    v7 = *((_DWORD *)v6 + 1);
    v6[26] = 0.0;
    BYTE1(v7) |= 8u;
    *((_DWORD *)v6 + 1) = v7;
    v8 = *(float *)(*(this + 35) + 56) * 0.033333335;
    v6[28] = 0.0;
    v6[27] = v8;
    v6[29] = *(float *)(*(this + 35) + 56) * 0.41666669;
    v9 = (float *)set_color_rgba(&v15, 1065353216, 1065353216, 1065353216, 1065353216);
    v6[11] = *v9;
    v6[12] = v9[1];
    v6[13] = v9[2];
    v10 = *((_DWORD *)v9 + 3);
    v6[24] = 0.30000001;
    v6[25] = 1.3;
    *((_DWORD *)v6 + 14) = v10;
    v11 = v6 + 21;
    v6 += 18;
    v15 = *a3 * 0.2;
    v16 = a3[1] * 0.2;
    v12 = a3[2] * 0.2;
    v13 = v16;
    *v11 = v15;
    v6[12] = 0.0;
    v11[1] = v13;
    v17 = v12;
    v11[2] = v17;
    *v6 = *a2;
    v6[1] = a2[1];
    v4 = *((_DWORD *)a2 + 2);
    *((_DWORD *)v6 + 2) = v4;
  }
  return v4;
}

