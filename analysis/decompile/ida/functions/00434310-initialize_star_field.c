/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_star_field @ 0x434310 */
/* selector: initialize_star_field */

// Builds the live star-field streak sprites: allocates one sprite per entry, seeds camera-relative positions, randomizes direction and speed, tints them pale blue-white, and primes the per-streak length or fade fields.
int __thiscall sub_434310(_DWORD *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // ebx
  int v6; // edi
  float *v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  double v11; // st7
  float *v12; // eax
  double v13; // st7
  double v14; // st7
  int v15; // ecx
  double v16; // st7
  float *v17; // eax
  double v18; // st6
  double v19; // st7
  int v20; // eax
  _DWORD *v21; // eax
  _DWORD *v22; // edx
  int v23; // eax
  int v24; // eax
  _DWORD *v25; // edx
  _DWORD *v26; // eax
  _DWORD *v27; // eax
  _DWORD *v28; // edx
  int v30; // [esp+10h] [ebp-60h]
  float v31; // [esp+14h] [ebp-5Ch]
  float v32; // [esp+18h] [ebp-58h]
  float v33; // [esp+1Ch] [ebp-54h]
  float v34; // [esp+20h] [ebp-50h]
  float v35; // [esp+24h] [ebp-4Ch]
  float v36; // [esp+30h] [ebp-40h]
  float v37; // [esp+34h] [ebp-3Ch]
  float v38; // [esp+38h] [ebp-38h]
  float v39; // [esp+40h] [ebp-30h]
  float v40; // [esp+44h] [ebp-2Ch]
  float v41; // [esp+48h] [ebp-28h]
  float v42; // [esp+4Ch] [ebp-24h]
  float v43; // [esp+54h] [ebp-1Ch]
  float v44; // [esp+58h] [ebp-18h]
  int v45[4]; // [esp+60h] [ebp-10h] BYREF

  v2 = 0;
  if ( (int)*(this + 16) > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      *(_DWORD *)(v3 + *(this + 15) + 28) = allocate_sprite(unk_790F30, 2, 32, -1, -1);
      v3 += 44;
    }
    while ( v2 < *(this + 16) );
  }
  v4 = *(this + 16);
  v5 = 0;
  *(this + 17) = 1065353216;
  if ( v4 > 0 )
  {
    do
    {
      v6 = 44 * v5;
      *(_DWORD *)(44 * v5 + *(this + 15)) = 1;
      if ( v5 )
        *(float *)(v6 + *(this + 15) + 40) = ((double)next_math_random_value() - 16384.0) * 0.0000061035157 + 0.40000001;
      else
        *(_DWORD *)(*(this + 15) + 40) = 1053609165;
      v39 = *((float *)MEMORY[0x4DF904] + 438) * 50.0;
      v40 = *((float *)MEMORY[0x4DF904] + 439) * 50.0;
      v32 = *((float *)MEMORY[0x4DF904] + 437) * 50.0 + *((float *)MEMORY[0x4DF904] + 441);
      v33 = v39 + *((float *)MEMORY[0x4DF904] + 442);
      v7 = (float *)(v6 + *(this + 15) + 4);
      v34 = v40 + *((float *)MEMORY[0x4DF904] + 443);
      *v7 = v32;
      v7[1] = v33;
      v7[2] = v34;
      v31 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
      v30 = next_math_random_value();
      v8 = v6 + *(this + 15) + 16;
      v35 = ((double)v30 - 16384.0) * 0.000061035156;
      *(float *)v8 = v35;
      *(float *)(v8 + 4) = v31;
      *(_DWORD *)(v8 + 8) = 0;
      normalize_vector((float *)(v6 + *(this + 15) + 16));
      v9 = next_math_random_value();
      v10 = *(this + 15);
      v11 = (double)v9;
      v12 = (float *)(v6 + v10 + 16);
      v13 = v11 * 0.000018310548 + 0.30000001;
      *v12 = v13 * *v12;
      v12[1] = v13 * *(float *)(v6 + v10 + 20);
      v14 = v13 * *(float *)(v6 + v10 + 24);
      v12[2] = v14;
      *(_DWORD *)(v6 + *(this + 15) + 24) = 0;
      vector_magnitude((float *)(v6 + *(this + 15) + 16));
      *(float *)(v6 + *(this + 15) + 32) = v14;
      *(float *)(v6 + *(this + 15) + 36) = (double)next_math_random_value() * 0.0010681152;
      v15 = *(this + 15);
      v16 = *(float *)(v6 + v15 + 36);
      v17 = (float *)(v6 + v15 + 4);
      v41 = v16 * *(float *)(v6 + v15 + 16);
      v42 = v16 * *(float *)(v6 + v15 + 20);
      v18 = *(float *)(v6 + v15 + 32);
      v43 = v41 / v18;
      v44 = v42 / v18;
      v36 = v43 + *v17;
      v37 = v44 + *(float *)(v6 + v15 + 8);
      v19 = v16 * *(float *)(v6 + v15 + 24) / v18 + *(float *)(v6 + v15 + 12);
      *v17 = v36;
      v17[1] = v37;
      v38 = v19;
      v17[2] = v38;
      v20 = *(_DWORD *)(v6 + *(this + 15) + 28);
      *(_DWORD *)(v20 + 4) |= 0x402u;
      *(_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 104) = 0;
      *(_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 108) = 0;
      *(_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 120) = 0;
      v21 = set_color_rgba(v45, 1061997773, 1061997773, 1065353216, 1053609165);
      v22 = (_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 44);
      *v22 = *v21;
      v22[1] = v21[1];
      v22[2] = v21[2];
      v22[3] = v21[3];
      *(_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 96) = 1061997773;
      v23 = *(_DWORD *)(v6 + *(this + 15) + 28);
      *(_DWORD *)(v23 + 100) = *(_DWORD *)(v23 + 96);
      *(float *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 136) = (*(float *)(v6 + *(this + 15) + 32) + 1.0) * 4.0;
      v24 = v6 + *(this + 15);
      v25 = (_DWORD *)(v24 + 16);
      v26 = (_DWORD *)(*(_DWORD *)(v24 + 28) + 84);
      *v26 = *v25;
      v26[1] = v25[1];
      v26[2] = v25[2];
      v27 = (_DWORD *)(v6 + *(this + 15));
      v28 = (_DWORD *)(v27[7] + 72);
      ++v5;
      *v28 = v27[1];
      v28[1] = v27[2];
      v28[2] = v27[3];
      *(_DWORD *)(*(_DWORD *)(v6 + *(this + 15) + 28) + 140) = 0;
    }
    while ( v5 < *(this + 16) );
  }
  return (*(int (__thiscall **)(_DWORD *))*this)(this);
}

