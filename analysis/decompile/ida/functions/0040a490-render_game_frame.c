/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_game_frame @ 0x40a490 */
/* selector: render_game_frame */

int __thiscall sub_40A490(int *this)
{
  int *v1; // edi
  int v2; // esi
  int v3; // eax
  int result; // eax
  int v5; // ebx
  _BYTE *v6; // eax
  int v7; // ecx
  int *v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ebp
  int v13; // eax
  int *v14; // ebx
  int *v15; // eax
  int v16; // ecx
  float v17; // edx
  int v18; // ebx
  int *v19; // ebp
  int v20; // eax
  float v21; // edx
  float *v22; // esi
  float v23; // ecx
  float v24; // eax
  float v25; // ecx
  float v26; // edx
  float v27; // eax
  float v28; // ecx
  int v29; // esi
  int *v30; // edi
  int v31; // eax
  int *v32; // ecx
  int v33; // eax
  float v34; // eax
  float v35; // edx
  float v36; // eax
  _DWORD *v37; // ecx
  float v38; // eax
  float v39; // edx
  float v40; // eax
  int v41; // ebx
  int v42; // ecx
  int v43; // eax
  const void *v44; // esi
  double v45; // st7
  double v46; // st7
  int v47; // esi
  int v48; // ecx
  int v49; // edx
  int *v50; // edi
  float v51; // ecx
  int v52; // ecx
  int *v53; // ebx
  int v54; // esi
  int v55; // ecx
  int v56; // ecx
  int *v57; // ebx
  int v58; // eax
  int *v59; // edi
  int v60; // eax
  int v61; // esi
  float v62; // eax
  float v63; // ecx
  float v64; // edx
  _DWORD *v65; // eax
  int *v66; // eax
  float v67; // eax
  float v68; // ecx
  float v69; // edx
  bool v70; // zf
  float v71[16]; // [esp-40h] [ebp-D0h] BYREF
  char v72; // [esp+0h] [ebp-90h]
  int *v73; // [esp+10h] [ebp-80h]
  int v74; // [esp+14h] [ebp-7Ch]
  int *v75; // [esp+18h] [ebp-78h]
  float v76; // [esp+1Ch] [ebp-74h]
  int v77; // [esp+20h] [ebp-70h]
  char *v78; // [esp+24h] [ebp-6Ch]
  int v79; // [esp+28h] [ebp-68h]
  float *v80; // [esp+2Ch] [ebp-64h]
  float v81; // [esp+30h] [ebp-60h] BYREF
  int v82; // [esp+34h] [ebp-5Ch]
  float v83; // [esp+38h] [ebp-58h]
  _DWORD v84[4]; // [esp+3Ch] [ebp-54h] BYREF
  int v85; // [esp+4Ch] [ebp-44h] BYREF
  _DWORD v86[12]; // [esp+50h] [ebp-40h] BYREF
  int v87; // [esp+80h] [ebp-10h]
  int v88; // [esp+84h] [ebp-Ch]
  int v89; // [esp+88h] [ebp-8h]

  v1 = this;
  v2 = 0;
  v75 = this;
  v3 = *(this + 347);
  if ( v3 > 0 )
  {
    result = v3 - 1;
    *(this + 347) = result;
    return result;
  }
  sub_414650();
  v77 = 0;
  set_matrix_identity(v86);
  v5 = 0;
  memset(v84, 255, sizeof(v84));
  v76 = 0.0;
  v6 = v1 + 367;
  v85 = -1;
  v7 = 5;
  do
  {
    if ( (*v6 & 1) != 0 )
      ++v5;
    v6 += 40;
    --v7;
  }
  while ( v7 );
  v8 = v1 + 366;
  v9 = v1[377] & 0xFFFFFF;
  v76 = *(float *)&v5;
  v10 = 0;
  v1[377] = v9 | 0x2000000;
  v74 = 0;
  v73 = v1 + 366;
  do
  {
    if ( (v8[1] & 1) != 0 )
    {
      if ( v2 )
      {
        v11 = 0;
        if ( v2 > 0 )
        {
          v12 = *v8;
          v13 = 0;
          do
          {
            v14 = &v84[v13];
            if ( v12 > v1[10 * v84[v13] + 366] )
            {
              if ( v13 <= 3 )
              {
                v15 = &v85;
                v16 = 4 - v11;
                do
                {
                  *v15 = *(v15 - 1);
                  --v15;
                  --v16;
                }
                while ( v16 );
              }
              ++v2;
              *v14 = v74;
              v11 = v2;
              v13 = v2;
            }
            ++v11;
            ++v13;
          }
          while ( v11 < v2 );
          v8 = v73;
          v5 = LODWORD(v76);
          v10 = v74;
        }
      }
      else
      {
        v84[0] = v10;
        v2 = 1;
      }
    }
    ++v10;
    v8 += 10;
    v74 = v10;
    v73 = v8;
  }
  while ( v10 < 5 );
  v73 = nullptr;
  v74 = 0;
  if ( v5 > 0 )
  {
    v79 = v5;
    v76 = COERCE_FLOAT(v84);
    do
    {
      v17 = v76;
      v18 = *(_DWORD *)LODWORD(v76);
      v19 = &v1[10 * *(_DWORD *)LODWORD(v76)];
      if ( (v19[367] & 1) != 0 )
      {
        v20 = v19[373];
        LOBYTE(v17) = *((_BYTE *)v19 + 1496);
        v71[15] = 0.0;
        v71[14] = v17;
        LODWORD(v21) = v20 + 56;
        v22 = (float *)&v1[10 * v18 + 370];
        LODWORD(v23) = v20 + 128;
        v24 = *(float *)(v20 + 192);
        v71[13] = v23;
        v25 = *((float *)v19 + 371);
        v71[12] = v21;
        v26 = *v22;
        v71[11] = v24;
        v27 = *((float *)v19 + 369);
        v71[10] = v25;
        v28 = *((float *)v19 + 368);
        v80 = v22;
        sub_411FA0(
          (int)v22,
          v28,
          v27,
          v26,
          v71[10],
          SLODWORD(v71[11]),
          v71[12],
          SLODWORD(v71[13]),
          SLODWORD(v71[14]),
          0,
          v72);
        if ( (v19[367] & 2) == 0 )
        {
          v29 = v1[363];
          v73 = nullptr;
          if ( v29 )
          {
            v30 = (int *)&MEMORY[0x4DFB10];
            do
            {
              if ( (*(_BYTE *)(v29 + 4) & 0x10) != 0 )
              {
                LODWORD(v71[15]) = aDebugRender;
                sub_449C00();
              }
              v31 = *(_DWORD *)(v29 + 4);
              if ( (v31 & 2) != 0 && (v31 & 0x20) != 0 && (v31 & v19[367] & 0xFF000000) != 0 )
              {
                if ( (v31 & 0x80u) != 0 )
                {
                  v32 = v73;
                  *v30++ = v29;
                  v73 = (int *)((char *)v32 + 1);
                }
                v33 = *(_DWORD *)(v29 + 4);
                ++v74;
                if ( (v33 & 0x800) != 0 )
                  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v29 + 36) + 188) + 12) = *(_DWORD *)(*(_DWORD *)(v29 + 120) + 4);
                if ( (*(_DWORD *)(v29 + 4) & 0x400) != 0 )
                {
                  LOBYTE(v34) = is_bod_after_sprites((char *)v29);
                  v35 = *(float *)(v29 + 32);
                  v71[15] = v34;
                  v36 = *(float *)(v29 + 28);
                  LODWORD(v71[14]) = v29 + 40;
                  v71[13] = v35;
                  v71[12] = v36;
                  v37 = (_DWORD *)(v29 + 56);
                }
                else
                {
                  v87 = *(_DWORD *)(v29 + 16);
                  v88 = *(_DWORD *)(v29 + 20);
                  v89 = *(_DWORD *)(v29 + 24);
                  LOBYTE(v38) = is_bod_after_sprites((char *)v29);
                  v39 = *(float *)(v29 + 32);
                  v71[15] = v38;
                  v40 = *(float *)(v29 + 28);
                  LODWORD(v71[14]) = v29 + 40;
                  v71[13] = v39;
                  v71[12] = v40;
                  v37 = v86;
                }
                submit_sprite_draw_batches(
                  *(_DWORD *)(v29 + 36),
                  v37,
                  SLODWORD(v71[12]),
                  v71[13],
                  (_DWORD *)LODWORD(v71[14]),
                  SLOBYTE(v71[15]));
              }
              v29 = *(_DWORD *)(v29 + 12);
            }
            while ( v29 );
            v1 = v75;
          }
        }
        v41 = unk_814C94[v18];
        v78 = (char *)&MEMORY[0x4E5510];
        sub_413540();
        if ( v41 )
        {
          while ( 1 )
          {
            v42 = v19[367];
            ++v77;
            v43 = *(_DWORD *)(v41 + 4);
            if ( (v43 & v42 & 0xFF000000) != 0 )
              break;
            report_errorf(aLooseSpriteSce);
LABEL_63:
            v41 = *(_DWORD *)(v41 + 12);
            if ( !v41 )
              goto LABEL_64;
          }
          if ( (v43 & 1) == 0 || (v43 & 0x40) == 0 || (v43 & 0x200) != 0 )
            goto LABEL_63;
          v44 = (const void *)(v19[373] + 128);
          v81 = *(float *)(v41 + 72);
          v82 = *(_DWORD *)(v41 + 76);
          v83 = *(float *)(v41 + 80);
          qmemcpy(v71, v44, sizeof(v71));
          multiply_vector_by_matrix(
            &v81,
            v71[0],
            v71[1],
            v71[2],
            SLODWORD(v71[3]),
            v71[4],
            v71[5],
            v71[6],
            SLODWORD(v71[7]),
            v71[8],
            v71[9],
            v71[10],
            SLODWORD(v71[11]),
            v71[12],
            v71[13],
            v71[14],
            SLODWORD(v71[15]));
          v81 = -v81;
          v45 = -v83;
          v83 = v45;
          v46 = -v45 * 4.1967211 + *(float *)(v41 + 152);
          v47 = (__int64)v46;
          if ( v47 >= 256 )
          {
            v47 = 255;
            goto LABEL_50;
          }
          if ( (int)(__int64)v46 >= 0 )
          {
LABEL_50:
            v48 = MEMORY[0x4F7050][v47];
            v49 = (int)v78;
            v78 += 24;
            if ( v48 )
            {
              v50 = nullptr;
              while ( v46 < *(float *)(v48 + 16) )
              {
                v50 = (int *)v48;
                v48 = *(_DWORD *)v48;
                if ( !v48 )
                {
                  *v50 = v49;
                  goto LABEL_59;
                }
              }
              if ( v50 )
              {
                *v50 = v49;
                *(_DWORD *)v49 = v48;
              }
              else
              {
                *(_DWORD *)v49 = v48;
                MEMORY[0x4F7050][v47] = v49;
              }
            }
            else
            {
              MEMORY[0x4F7050][v47] = v49;
LABEL_59:
              *(_DWORD *)v49 = 0;
            }
            v51 = v81;
            *(float *)(v49 + 16) = v46;
            *(float *)(v49 + 4) = v51;
            v52 = v82;
            *(_DWORD *)(v49 + 20) = v41;
            *(_DWORD *)(v49 + 8) = v52;
            *(float *)(v49 + 12) = v83;
            *(_DWORD *)(v41 + 20) = v47;
            *(float *)(v41 + 24) = v46;
          }
          v1 = v75;
          goto LABEL_63;
        }
LABEL_64:
        v53 = (int *)&MEMORY[0x4F744C];
        do
        {
          v54 = *v53;
          if ( *v53 )
          {
            do
            {
              v55 = *(_DWORD *)(v54 + 20);
              if ( (*(_BYTE *)(v55 + 4) & 2) != 0 )
                update_sprite_facing_angle(v55, (float *)(v19[373] + 128));
              draw_sprite_quad(v54 + 4, *(float *)(v54 + 20));
              v54 = *(_DWORD *)v54;
            }
            while ( v54 );
            *v53 = 0;
          }
          --v53;
        }
        while ( (int)v53 >= (int)MEMORY[0x4F7050] );
        sub_413650();
        sub_411E10();
        draw_font_text_queue(v19[367]);
        sub_411DE0();
        if ( (v19[367] & 2) == 0 && v73 )
        {
          LOBYTE(v56) = *((_BYTE *)v19 + 1496);
          sub_411FA0(
            v54,
            *((float *)v19 + 368),
            *((float *)v19 + 369),
            *v80,
            *((float *)v19 + 371),
            *(_DWORD *)(v19[373] + 192),
            COERCE_FLOAT(v19[373] + 56),
            v19[373] + 128,
            v56,
            1,
            v72);
          v57 = v73;
          v58 = (int)v73 + v74;
          v59 = (int *)(4 * (_DWORD)v73 + 5110544);
          v73 = nullptr;
          v74 = v58;
          do
          {
            v60 = *--v59;
            if ( (*(_DWORD *)(v60 + 4) & 0x400) != 0 )
            {
              v61 = v60;
              LOBYTE(v62) = is_bod_after_sprites((char *)v60);
              v63 = *(float *)(v61 + 32);
              v64 = *(float *)(v61 + 28);
              v71[15] = v62;
              LODWORD(v71[14]) = v61 + 40;
              v71[13] = v63;
              v71[12] = v64;
              v65 = (_DWORD *)(v61 + 56);
            }
            else
            {
              v66 = (int *)(v60 + 16);
              v61 = *v59;
              v87 = *v66;
              v88 = v66[1];
              v89 = v66[2];
              LOBYTE(v67) = is_bod_after_sprites((char *)v61);
              v68 = *(float *)(v61 + 32);
              v69 = *(float *)(v61 + 28);
              v71[15] = v67;
              LODWORD(v71[14]) = v61 + 40;
              v71[13] = v68;
              v71[12] = v69;
              v65 = v86;
            }
            submit_sprite_draw_batches(
              *(_DWORD *)(v61 + 36),
              v65,
              SLODWORD(v71[12]),
              v71[13],
              (_DWORD *)LODWORD(v71[14]),
              SLOBYTE(v71[15]));
            v57 = (int *)((char *)v57 - 1);
          }
          while ( v57 );
          v1 = v75;
        }
      }
      v10 = LODWORD(v76) + 4;
      v70 = v79 == 1;
      LODWORD(v76) += 4;
      --v79;
    }
    while ( !v70 );
  }
  return noop_runtime_ai(v10);
}

