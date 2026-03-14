/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_jetpack_visual @ 0x4431d0 */
/* selector: 0x4431d0 */

void __thiscall sub_4431D0(int this)
{
  int v2; // ecx
  double v3; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  _DWORD *v7; // ecx
  int v8; // edi
  int v9; // eax
  double v10; // st7
  float *v11; // eax
  double v12; // st7
  float *v13; // eax
  double v14; // st7
  double v15; // st7
  double v16; // st7
  float *v17; // eax
  double v18; // st6
  double v19; // st6
  double v20; // st6
  float v21; // eax
  int v22; // eax
  double v23; // st7
  float *v24; // eax
  int v25; // edx
  double v26; // st7
  float v27; // ecx
  double v28; // st7
  double v29; // st7
  int v30; // ecx
  int v31; // eax
  float *v32; // eax
  double v33; // st7
  int v34; // ecx
  double v35; // st7
  double v36; // st7
  float *v37; // eax
  float v38; // edx
  double v39; // st7
  int v40; // eax
  float v41; // ecx
  double v42; // st7
  float *v43; // eax
  double v44; // st7
  double v45; // st7
  int v46; // ecx
  float v47; // [esp+0h] [ebp-38h]
  float v48; // [esp+0h] [ebp-38h]
  float v49; // [esp+0h] [ebp-38h]
  float v50; // [esp+0h] [ebp-38h]
  float v51; // [esp+14h] [ebp-24h] BYREF
  float v52; // [esp+18h] [ebp-20h]
  float v53; // [esp+1Ch] [ebp-1Ch]
  float v54; // [esp+20h] [ebp-18h]
  float v55; // [esp+24h] [ebp-14h]
  float v56; // [esp+28h] [ebp-10h]
  float v57; // [esp+2Ch] [ebp-Ch]
  float v58; // [esp+30h] [ebp-8h]

  v2 = *(_DWORD *)(this + 60);
  if ( !*(_BYTE *)(v2 + 9) )
  {
    switch ( *(_DWORD *)(this + 56) )
    {
      case 1:
        if ( *(float *)(v2 + 3924196) - 10.0 > *(float *)(this + 24) )
        {
          kill_sprite(*(_DWORD *)(this + 84));
          *(_DWORD *)(this + 56) = 0;
        }
        v3 = *(float *)(this + 96) + *(float *)(this + 92);
        *(float *)(this + 92) = v3;
        if ( !(v5 | v6) )
          *(float *)(this + 92) = v3 - 1.0;
        v7 = (_DWORD *)(*(_DWORD *)(this + 84) + 72);
        *v7 = *(_DWORD *)(this + 16);
        v7[1] = *(_DWORD *)(this + 20);
        v7[2] = *(_DWORD *)(this + 24);
        v8 = *(_DWORD *)(this + 84);
        v47 = *(float *)(this + 92) * 6.2831855;
        *(float *)(v8 + 76) = sine(v47) * 0.30000001 + *(float *)(v8 + 76);
        *(_DWORD *)(*(_DWORD *)(this + 84) + 124) = *(_DWORD *)(*(_DWORD *)(this + 100) + 880);
        v9 = *(_DWORD *)(this + 100);
        if ( *(_BYTE *)(v9 + 900) == 1 )
          *(float *)(*(_DWORD *)(this + 84) + 124) = *(float *)(v9 + 928) + *(float *)(*(_DWORD *)(this + 84) + 124);
        return;
      case 4:
        v48 = *(float *)(this + 92) * 6.2831855;
        v10 = sine(v48);
        v11 = *(float **)(this + 60);
        *(_DWORD *)(this + 104) = 0;
        v11 += 982599;
        *(_DWORD *)(this + 108) = 1026206379;
        *(float *)(this + 20) = v10 * 0.30000001 + *(float *)(this + 20);
        v54 = *v11 - *(float *)(this + 16);
        v55 = v11[1] - *(float *)(this + 20);
        v12 = v11[2] - *(float *)(this + 24);
        v51 = v54;
        v52 = v55;
        v56 = v12;
        v53 = v56;
        vector_magnitude(&v51);
        v13 = *(float **)(this + 60);
        *(_DWORD *)(this + 56) = 5;
        *(float *)(this + 112) = v12;
        v14 = *(float *)(this + 16) - v13[982599];
        v13 += 982599;
        v54 = v14;
        v55 = *(float *)(this + 20) - v13[1];
        v15 = *(float *)(this + 24) - v13[2];
        *(float *)(this + 116) = v54;
        v56 = v15;
        *(float *)(this + 120) = v55;
        *(float *)(this + 124) = v56;
        normalize_vector((float *)(this + 116));
        goto LABEL_10;
      case 5:
LABEL_10:
        v16 = 1.0 - *(float *)(this + 104);
        v17 = (float *)(*(_DWORD *)(this + 60) + 3930396);
        v18 = v16 * *(float *)(this + 112);
        v57 = v18 * *(float *)(this + 116);
        v58 = v18 * *(float *)(this + 120);
        v19 = v18 * *(float *)(this + 124);
        v54 = v57 + *v17;
        v55 = v58 + v17[1];
        v20 = v19 + v17[2];
        v21 = v55;
        *(float *)(this + 16) = v54;
        *(float *)(this + 20) = v21;
        v22 = *(_DWORD *)(this + 84);
        v56 = v20;
        *(float *)(this + 24) = v56;
        *(float *)(v22 + 100) = v16 * 0.60000002 + 0.40000001;
        *(_DWORD *)(*(_DWORD *)(this + 84) + 96) = *(_DWORD *)(*(_DWORD *)(this + 84) + 100);
        v49 = *(float *)(this + 104) * 3.1415927;
        v23 = sine(v49) * 0.5;
        v24 = (float *)(*(_DWORD *)(this + 60) + 3924272);
        v25 = *(_DWORD *)(this + 84) + 72;
        v57 = v23 * *v24;
        v58 = v23 * v24[1];
        v26 = v23 * v24[2];
        v54 = v57 + *(float *)(this + 16);
        v55 = v58 + *(float *)(this + 20);
        v27 = v55;
        v28 = v26 + *(float *)(this + 24);
        *(float *)v25 = v54;
        *(float *)(v25 + 4) = v27;
        v56 = v28;
        *(float *)(v25 + 8) = v56;
        v29 = *(float *)(this + 108) + *(float *)(this + 104);
        *(float *)(this + 104) = v29;
        if ( v29 > 1.0 )
        {
          v30 = *(_DWORD *)(this + 84);
          *(_DWORD *)(this + 56) = 0;
          kill_sprite(v30);
        }
        return;
      case 6:
        *(_DWORD *)(this + 104) = 0;
        *(_DWORD *)(this + 108) = 1015580809;
        *(_DWORD *)(this + 56) = 7;
        *(float *)(this + 128) = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
        v31 = next_math_random_value();
        *(_DWORD *)(this + 136) = 0;
        *(float *)(this + 132) = ((double)v31 - 16384.0) * 0.000091552734 + 1.0;
        goto LABEL_13;
      case 7:
LABEL_13:
        v32 = *(float **)(this + 60);
        v54 = v32[4835843] - v32[982599];
        v55 = v32[4835844] - v32[982600];
        v33 = v32[4835845] - v32[982601];
        v51 = v54;
        v34 = *(_DWORD *)(this + 84);
        v52 = v55;
        v56 = v33;
        v35 = *(float *)(this + 104) * 0.60000002;
        v53 = v56;
        *(float *)(v34 + 100) = v35 + 0.40000001;
        *(_DWORD *)(*(_DWORD *)(this + 84) + 96) = *(_DWORD *)(*(_DWORD *)(this + 84) + 100);
        v36 = *(float *)(this + 104);
        v37 = (float *)(*(_DWORD *)(this + 60) + 3930396);
        v57 = v51 * v36;
        v58 = v52 * v36;
        v54 = v57 + *v37;
        v55 = v58 + v37[1];
        v38 = v55;
        v39 = v36 * v53 + v37[2];
        v40 = *(_DWORD *)(this + 84) + 72;
        v56 = v39;
        *(float *)v40 = v54;
        v41 = v56;
        *(float *)(v40 + 4) = v38;
        *(float *)(v40 + 8) = v41;
        v50 = *(float *)(this + 104) * 3.1415927;
        v42 = sine(v50);
        v43 = (float *)(*(_DWORD *)(this + 84) + 72);
        v57 = v42 * *(float *)(this + 128);
        v58 = v42 * *(float *)(this + 132);
        v44 = v42 * *(float *)(this + 136);
        *v43 = v57 + *v43;
        v43[1] = v58 + v43[1];
        v43[2] = v44 + v43[2];
        v45 = *(float *)(this + 108) + *(float *)(this + 104);
        *(float *)(this + 104) = v45;
        if ( v45 > 1.0 )
        {
          register_parcel_delivery((int *)(*(_DWORD *)(this + 60) + 19343320));
          v46 = *(_DWORD *)(this + 84);
          *(_DWORD *)(this + 56) = 0;
          kill_sprite(v46);
        }
        break;
      default:
        return;
    }
  }
}

