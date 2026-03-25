/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_render_caches @ 0x433220 */
/* selector: build_track_render_caches */

// Builds the Floor, Slide, Warn, Ramp, and Fringe track render caches after runtime track normalization.
int __thiscall sub_433220(int ArgList, float a2, int a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // edi
  int v8; // esi
  _DWORD *v9; // eax
  int v10; // ecx
  int v11; // ebp
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v19; // ebp
  int v20; // eax
  int v21; // ebp
  int v22; // eax
  int *v23; // eax
  int v24; // ecx
  unsigned int *v25; // edi
  int v26; // ebp
  int v27; // eax
  unsigned int v28; // eax
  char *v29; // esi
  char *v30; // edi
  char *v31; // edi
  char *v32; // esi
  char v33; // cl
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // esi
  int v38; // edx
  int *v39; // eax
  int v40; // esi
  int v41; // edi
  int v42; // ebp
  int v43; // edx
  int v44; // esi
  int result; // eax
  int v46; // [esp+18h] [ebp-64h]
  int v47; // [esp+1Ch] [ebp-60h]
  int v48; // [esp+30h] [ebp-4Ch]
  int v49; // [esp+34h] [ebp-48h] BYREF
  int v50; // [esp+38h] [ebp-44h]
  int v51; // [esp+3Ch] [ebp-40h]
  int v52; // [esp+40h] [ebp-3Ch]
  int v53; // [esp+44h] [ebp-38h]
  char *v54; // [esp+48h] [ebp-34h] BYREF
  void *v55; // [esp+4Ch] [ebp-30h] BYREF
  int v56; // [esp+50h] [ebp-2Ch]
  int v57; // [esp+54h] [ebp-28h] BYREF
  int v58; // [esp+58h] [ebp-24h] BYREF
  int v59; // [esp+5Ch] [ebp-20h] BYREF
  int v60; // [esp+60h] [ebp-1Ch] BYREF
  int v61; // [esp+64h] [ebp-18h] BYREF
  int v62; // [esp+68h] [ebp-14h] BYREF
  int v63; // [esp+6Ch] [ebp-10h] BYREF
  int v64; // [esp+70h] [ebp-Ch] BYREF
  int v65; // [esp+74h] [ebp-8h] BYREF
  int v66; // [esp+78h] [ebp-4h] BYREF

  Iostream_init::Iostream_init((#93 *)&v49);
  pack_color_rgba_u8((_BYTE *)ArgList, &a2);
  v49 = -1;
  noop_runtime_ai(ArgList);
  v6 = 0;
  v48 = 0;
  if ( *(int *)(*(_DWORD *)(ArgList + 84) + 84) <= 0 )
    goto LABEL_37;
  v7 = 0;
  while ( 2 )
  {
    v53 = v6 % 24;
    if ( v6 % 24 )
    {
      v8 = v51;
    }
    else
    {
      v8 = v6 / 24;
      v51 = v6 / 24;
      v62 = 0;
      v63 = 0;
      v64 = 0;
      v65 = 0;
      v66 = 0;
      v9 = (_DWORD *)(ArgList + 300 * (v6 / 24) + 144);
      v57 = 0;
      v58 = 0;
      *(float *)(ArgList + 42988) = (double)(v6 / 24) * 24.0;
      v59 = 0;
      v60 = 0;
      v61 = 0;
      v10 = 5;
      do
      {
        *v9 = *(_DWORD *)(ArgList + 42988);
        v9 += 15;
        --v10;
      }
      while ( v10 );
    }
    v52 = 8;
    do
    {
      v11 = v7 + 3930892;
      v50 = 4;
      do
      {
        v12 = *(_DWORD *)(ArgList + 84);
        v13 = *(_DWORD *)(v12 + v11);
        if ( v13 )
        {
          sub_433960(
            (float *)ArgList,
            v48,
            *(_DWORD *)(v13 + 36),
            (float *)(v7 + v12 + 3930840),
            *(_DWORD *)(ArgList + 60),
            &v61,
            *(_DWORD *)(ArgList + 80),
            &v66,
            *(_DWORD *)(ArgList + 20),
            *(_DWORD *)(ArgList + 40),
            *(_DWORD *)ArgList,
            0);
          **(_DWORD **)(*(_DWORD *)(ArgList + 300 * v8 + 364) + 208) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(ArgList + 84) + v11) + 36)
                                                                                             + 92)
                                                                                 + 12);
          *(_DWORD *)(*(_DWORD *)(ArgList + 84) + v11) = 0;
        }
        v11 += 4;
        --v50;
      }
      while ( v50 );
      v14 = *(_DWORD *)(ArgList + 84);
      v15 = v7 + v14;
      if ( (*(_DWORD *)(v7 + v14 + 3930888) & 0x20) != 0 && (*(_DWORD *)(v7 + v14 + 3930888) & 0x4000) == 0x4000 )
      {
        sub_433960(
          (float *)ArgList,
          v48,
          *(_DWORD *)(v15 + 3930860),
          (float *)(v15 + 3930840),
          *(_DWORD *)(ArgList + 52),
          &v59,
          *(_DWORD *)(ArgList + 72),
          &v64,
          *(_DWORD *)(ArgList + 12),
          *(_DWORD *)(ArgList + 32),
          v49,
          1);
        v16 = *(_DWORD *)(*(_DWORD *)(v7 + *(_DWORD *)(ArgList + 84) + 3930860) + 92);
        v17 = *(_DWORD *)(ArgList + 300 * v8 + 244);
        goto LABEL_28;
      }
      if ( is_slide_cache_tile_family((_BYTE *)(v15 + 3930824)) )
      {
        v18 = *(_DWORD *)(ArgList + 84);
        v19 = *(_DWORD *)(v7 + v18 + 3930888);
        v20 = v7 + v18;
        if ( (v19 & 0x4000) == 0x4000 )
        {
          v46 = v49;
          if ( (v19 & 0x40) == 0x40 )
            goto LABEL_20;
LABEL_24:
          sub_433960(
            (float *)ArgList,
            v48,
            *(_DWORD *)(v20 + 3930860),
            (float *)(v20 + 3930840),
            *(_DWORD *)(ArgList + 44),
            &v57,
            *(_DWORD *)(ArgList + 64),
            &v62,
            *(_DWORD *)(ArgList + 4),
            *(_DWORD *)(ArgList + 24),
            v46,
            1);
          v16 = *(_DWORD *)(*(_DWORD *)(v7 + *(_DWORD *)(ArgList + 84) + 3930860) + 92);
          v17 = *(_DWORD *)(ArgList + 300 * v8 + 124);
          goto LABEL_28;
        }
      }
      if ( is_floor_cache_tile_family((_BYTE *)(v7 + *(_DWORD *)(ArgList + 84) + 3930824)) )
      {
        v20 = v7 + *(_DWORD *)(ArgList + 84);
        v21 = *(_DWORD *)(v20 + 3930888);
        if ( (v21 & 0x4000) == 0x4000 )
        {
          v46 = v49;
          if ( (v21 & 0x40) == 0x40 )
            goto LABEL_24;
LABEL_20:
          sub_433960(
            (float *)ArgList,
            v48,
            *(_DWORD *)(v20 + 3930860),
            (float *)(v20 + 3930840),
            *(_DWORD *)(ArgList + 48),
            &v58,
            *(_DWORD *)(ArgList + 68),
            &v63,
            *(_DWORD *)(ArgList + 8),
            *(_DWORD *)(ArgList + 28),
            v46,
            1);
          v16 = *(_DWORD *)(*(_DWORD *)(v7 + *(_DWORD *)(ArgList + 84) + 3930860) + 92);
          v17 = *(_DWORD *)(ArgList + 300 * v8 + 184);
LABEL_28:
          **(_DWORD **)(v17 + 208) = *(_DWORD *)(v16 + 12);
          v23 = (int *)(v7 + *(_DWORD *)(ArgList + 84) + 3930888);
          v24 = *v23;
          BYTE1(v24) = BYTE1(*v23) & 0xBF;
          *v23 = v24;
          goto LABEL_29;
        }
      }
      if ( is_ramp_cache_tile_family((_BYTE *)(v7 + *(_DWORD *)(ArgList + 84) + 3930824)) )
      {
        v22 = v7 + *(_DWORD *)(ArgList + 84);
        if ( (*(_DWORD *)(v22 + 3930888) & 0x4000) == 0x4000 )
        {
          sub_433960(
            (float *)ArgList,
            v48,
            *(_DWORD *)(v22 + 3930860),
            (float *)(v22 + 3930840),
            *(_DWORD *)(ArgList + 56),
            &v60,
            *(_DWORD *)(ArgList + 76),
            &v65,
            *(_DWORD *)(ArgList + 16),
            *(_DWORD *)(ArgList + 36),
            v49,
            0);
          v16 = *(_DWORD *)(*(_DWORD *)(v7 + *(_DWORD *)(ArgList + 84) + 3930860) + 92);
          v17 = *(_DWORD *)(ArgList + 300 * v8 + 304);
          goto LABEL_28;
        }
      }
LABEL_29:
      v7 += 84;
      --v52;
    }
    while ( v52 );
    v56 = v7;
    if ( v53 == 23 || v48 == *(_DWORD *)(*(_DWORD *)(ArgList + 84) + 84) - 1 )
    {
      v25 = (unsigned int *)(ArgList + 4);
      v50 = ArgList + 4;
      v52 = 0;
      v26 = ArgList + 300 * v8 + 124;
      while ( 1 )
      {
        v27 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v26 + 192) + 8);
        (*(void (__stdcall **)(int, _DWORD, unsigned int, char **, _DWORD))(*(_DWORD *)v27 + 44))(
          v27,
          0,
          24 * *v25,
          &v54,
          0);
        (*(void (__stdcall **)(_DWORD, _DWORD, unsigned int, void **, _DWORD))(***(_DWORD ***)(*(_DWORD *)v26 + 200) + 44))(
          **(_DWORD **)(*(_DWORD *)v26 + 200),
          0,
          2 * v25[5],
          &v55,
          0);
        v28 = *v25;
        v29 = (char *)v25[10];
        v30 = v54;
        v28 *= 24;
        qmemcpy(v54, v29, 4 * (v28 >> 2));
        v32 = &v29[4 * (v28 >> 2)];
        v31 = &v30[4 * (v28 >> 2)];
        v33 = v28;
        v34 = v50;
        qmemcpy(v31, v32, v33 & 3);
        qmemcpy(v55, *(const void **)(v34 + 60), 2 * *(_DWORD *)(v34 + 20));
        v47 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v26 + 192) + 8);
        (*(void (__stdcall **)(int))(*(_DWORD *)v47 + 48))(v47);
        (*(void (__stdcall **)(_DWORD))(***(_DWORD ***)(*(_DWORD *)v26 + 200) + 48))(**(_DWORD **)(*(_DWORD *)v26 + 200));
        v35 = v52;
        v36 = *(_DWORD *)v26;
        v37 = v50;
        v26 += 60;
        *(_DWORD *)(v36 + 196) = *(int *)((char *)&v57 + v52);
        v38 = *(int *)((char *)&v62 + v35) / 3;
        v39 = *(int **)(*(_DWORD *)(v26 - 60) + 212);
        v50 = v37 + 4;
        *v39 = v38;
        *(_DWORD *)(*(_DWORD *)(v26 - 60) + 44) = *(int *)((char *)&v57 + v35);
        v52 = v35 + 4;
        if ( v35 + 4 >= 20 )
          break;
        v25 = (unsigned int *)v50;
      }
      v7 = v56;
    }
    if ( ++v48 < *(_DWORD *)(*(_DWORD *)(ArgList + 84) + 84) )
    {
      v6 = v48;
      continue;
    }
    break;
  }
LABEL_37:
  v40 = 0;
  *(_DWORD *)(ArgList + 42992) = 0;
  *(_DWORD *)(ArgList + 42996) = 0;
  v52 = 0;
  do
  {
    v41 = 0;
    v42 = 0;
    v43 = *(_DWORD *)(*(_DWORD *)(ArgList + 84) + 84) / 24;
    if ( v43 > 0 )
    {
      v44 = ArgList + 60 * v40 + 124;
      do
      {
        if ( *(_DWORD *)(*(_DWORD *)v44 + 44) > v41 )
          v41 = *(_DWORD *)(*(_DWORD *)v44 + 44);
        if ( 4 * **(_DWORD **)(*(_DWORD *)v44 + 212) > v42 )
          v42 = 4 * **(_DWORD **)(*(_DWORD *)v44 + 212);
        v44 += 300;
        --v43;
      }
      while ( v43 );
      v40 = v52;
    }
    result = sub_449C00();
    v52 = ++v40;
  }
  while ( v40 < 5 );
  return result;
}

