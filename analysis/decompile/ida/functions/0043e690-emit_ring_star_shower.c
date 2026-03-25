/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: emit_ring_star_shower @ 0x43e690 */
/* selector: emit_ring_star_shower */

char __thiscall sub_43E690(float *this, int a2)
{
  int v2; // eax
  float *v4; // esi
  int v5; // eax
  double v6; // st7
  float *v7; // eax
  float v9; // [esp+0h] [ebp-24h]
  float v10; // [esp+0h] [ebp-24h]
  float v11; // [esp+Ch] [ebp-18h]
  float v12; // [esp+10h] [ebp-14h]
  float v13; // [esp+18h] [ebp-Ch]

  LOBYTE(v2) = byte_4DF934;
  if ( (byte_4DF934 & 0x10) != 0 )
  {
    v4 = (float *)allocate_sprite(unk_790F30, *(_DWORD *)(a2 + 896), *(_DWORD *)(*((_DWORD *)this + 1) + 492), -1, -1);
    v5 = *((_DWORD *)v4 + 1);
    v4[26] = 0.0;
    BYTE1(v5) |= 8u;
    v4[27] = 0.1111111;
    *((_DWORD *)v4 + 1) = v5;
    v4[24] = 0.40000001;
    v4[25] = 0.2;
    v9 = *(this + 5) + 1.0471976;
    v13 = sine(v9) * *(this + 7);
    v10 = *(this + 5) + 1.0471976;
    v11 = v13 * 0.30000001;
    v6 = cosine(v10) * *(this + 7) * 0.30000001;
    v4[21] = v11;
    v12 = v6;
    v4[22] = v12;
    v4[23] = 0.0;
    v7 = (float *)(*(_DWORD *)this + 72);
    v4[18] = *v7;
    v4[19] = v7[1];
    v2 = *((_DWORD *)v7 + 2);
    v4[30] = 0.0;
    *((_DWORD *)v4 + 20) = v2;
  }
  return v2;
}

