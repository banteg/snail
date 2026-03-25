/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_attachment_follow_state @ 0x420cb0 */
/* selector: update_track_attachment_follow_state */

// Advances one live attachment-follow session along the current template, updates segment, progress, and local height, writes the interpolated output transform back into the follow struct, and returns a small mode code consumed by `update_subgoldy`. Windows `cdb` confirmed `ARCADE007` produces mid-follow samples with local height `-0.49f`, and the case-1 or case-3 return path feeds one direct fall-state handoff inside `update_subgoldy`. Raw BN plus IDA also show the nearby `voice 4` call guarded by `sample_index + 1 == template->sample_count << 1`, which conflicts with the same helper's `sample_index == template->sample_count` termination under the current typed counters, so that milestone lane remains unresolved rather than ported.
int __thiscall sub_420CB0(char *this, float a2, float *a3, int a4)
{
  int v5; // ecx
  int v6; // esi
  int v7; // edx
  double v8; // st7
  float *v9; // edx
  double v10; // st7
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // esi
  int v15; // esi
  int v16; // eax
  int v17; // esi
  int v18; // ebx
  _DWORD *v19; // edx
  int v20; // edi
  int v21; // eax
  float *v22; // ecx
  double v23; // st7
  int v24; // edx
  int v25; // ecx
  double v26; // st7
  int v27; // esi
  double v28; // st6
  int v29; // ecx
  double v30; // st5
  int v31; // eax
  float *v32; // ecx
  double v33; // st6
  double v34; // st5
  double v35; // st5
  double v36; // st5
  float *v38; // ebx
  int v39; // eax
  int v40; // eax
  float *v41; // esi
  _DWORD *v42; // edi
  int v43; // ecx
  double v44; // st7
  double v45; // st6
  int v46; // eax
  char *v47; // edx
  _DWORD *v48; // ecx
  char *v49; // eax
  int v50; // ecx
  double v51; // st7
  float *v52; // esi
  float *v53; // ecx
  double v54; // st7
  double v55; // st7
  double v56; // st6
  double v57; // st6
  double v58; // st5
  char *v59; // eax
  _DWORD *v60; // edx
  char *v61; // ecx
  int v62; // edx
  int v63; // ecx
  int v64; // edx
  float v65; // eax
  bool v66; // zf
  int v67; // ecx
  int v68; // ecx
  int v69; // eax
  double v70; // st7
  int v71; // eax
  double v72; // st7
  double v73; // st7
  int v74; // ecx
  double v75; // st7
  float v76; // [esp+0h] [ebp-1A0h]
  float v77; // [esp+Ch] [ebp-194h]
  float v78; // [esp+20h] [ebp-180h]
  float v79; // [esp+20h] [ebp-180h]
  int v80; // [esp+24h] [ebp-17Ch] BYREF
  int v81; // [esp+28h] [ebp-178h]
  float v82; // [esp+2Ch] [ebp-174h]
  float v83; // [esp+30h] [ebp-170h]
  float v84; // [esp+34h] [ebp-16Ch]
  float v85; // [esp+38h] [ebp-168h]
  int v86[16]; // [esp+3Ch] [ebp-164h] BYREF
  float v87; // [esp+7Ch] [ebp-124h]
  float v88; // [esp+80h] [ebp-120h]
  float v89; // [esp+84h] [ebp-11Ch]
  float v90; // [esp+88h] [ebp-118h]
  float v91; // [esp+8Ch] [ebp-114h]
  float v92; // [esp+94h] [ebp-10Ch]
  float v93; // [esp+98h] [ebp-108h]
  int v94[16]; // [esp+A0h] [ebp-100h] BYREF
  int v95[16]; // [esp+E0h] [ebp-C0h] BYREF
  int v96[16]; // [esp+120h] [ebp-80h] BYREF
  int v97[16]; // [esp+160h] [ebp-40h] BYREF

  v5 = *((_DWORD *)this + 3);
  v6 = *((_DWORD *)this + 1);
  v7 = *(_DWORD *)(v6 + 92);
  v8 = a2 * *(float *)(v7 + 168 * v5 + 140);
  v9 = (float *)(v7 + 168 * v5 + 140);
  v78 = v8;
  if ( v8 + *((float *)this + 4) <= *v9 )
  {
LABEL_11:
    v18 = *((_DWORD *)this + 3);
    *(float *)&v80 = v78 + *((float *)this + 4);
    *((float *)this + 4) = *(float *)&v80;
    v19 = *((_DWORD **)this + 1);
    v20 = v19[17] - 1;
    v21 = 168 * v18;
    v22 = (float *)(168 * v18 + v19[22]);
    if ( v18 == v20 )
      v85 = v22[36];
    else
      v85 = *(float *)&v80 / *(float *)(v19[23] + 168 * v18 + 140) * (v22[78] - v22[36]) + v22[36];
    if ( v18 == v20 )
      v79 = v22[39];
    else
      v79 = *(float *)&v80 / *(float *)(v19[23] + v21 + 140) * (v22[81] - v22[39]) + v22[39];
    if ( v18 == v20 )
      v81 = *((int *)v22 + 40);
    else
      *(float *)&v81 = *(float *)&v80 / *(float *)(v19[23] + v21 + 140) * (v22[82] - v22[40]) + v22[40];
    if ( v19[14] == 42 )
    {
      v38 = a3;
      v76 = *a3 - v85;
      compute_kind42_attachment_transform(*(float *)&v81, v76, 0.49000001, (int)v86, (float *)&v80);
      v39 = *((_DWORD *)this + 3);
      if ( !v39 || v39 == *(_DWORD *)(*((_DWORD *)this + 1) + 68) - 1 )
      {
        set_matrix_identity(v94);
        v94[12] = v86[12];
        v40 = *((_DWORD *)this + 3);
        v94[13] = v86[13];
        v94[14] = v86[14];
        qmemcpy(v97, v86, sizeof(v97));
        if ( v40 )
          *(float *)&v81 = 1.0 - *((float *)this + 4);
        else
          v81 = *((int *)this + 4);
        linear_interpolate_matrix((float *)v86, (float *)v94, (float *)v97, *(float *)&v81);
      }
      v41 = (float *)(this + 44);
      v42 = (_DWORD *)(a4 + 4);
      v43 = v86[13];
      v44 = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 92) + 168 * *((_DWORD *)this + 3) + 136)
          * *((float *)this + 4)
          + *(float *)(*((_DWORD *)this + 2) + 24)
          + *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 92) + 168 * *((_DWORD *)this + 3) + 56);
      *(float *)v86 = *(float *)v86 * v79;
      *(float *)&v86[1] = *(float *)&v86[1] * v79;
      *(float *)&v86[2] = *(float *)&v86[2] * v79;
      v45 = *(float *)(a4 + 4) + *((float *)this + 5);
      *((_DWORD *)this + 11) = v86[12];
      v46 = v86[0];
      *((_DWORD *)this + 12) = v43;
      *((float *)this + 5) = v45;
      *((float *)this + 13) = v44;
      v47 = (char *)MEMORY[0x4DF904] + 4390324;
      *((_DWORD *)MEMORY[0x4DF904] + 1097581) = v46;
      *((_DWORD *)v47 + 1) = v86[1];
      *((_DWORD *)v47 + 2) = v86[2];
      v48 = (_DWORD *)((char *)&loc_42FDC4 + (_DWORD)MEMORY[0x4DF904]);
      *v48 = v86[4];
      v48[1] = v86[5];
      v48[2] = v86[6];
      v49 = (char *)MEMORY[0x4DF904] + 4390356;
      *((_DWORD *)MEMORY[0x4DF904] + 1097589) = v86[8];
      *((_DWORD *)v49 + 1) = v86[9];
      *((_DWORD *)v49 + 2) = v86[10];
    }
    else
    {
      v50 = v19[23];
      v51 = *(float *)&v80 * *(float *)(v50 + v21 + 128);
      v52 = (float *)(v50 + v21);
      v53 = *((float **)this + 2);
      v82 = v51 * v79 + v53[4] + v52[12];
      v83 = *(float *)&v80 * v52[33] * v79 + v53[5] + v52[13];
      v84 = *(float *)&v80 * v52[34] + v53[6] + v52[14];
      if ( v18 == v20 )
      {
        set_matrix_identity(v86);
      }
      else
      {
        qmemcpy(v95, v52, sizeof(v95));
        qmemcpy(v96, (const void *)(v19[23] + 168 * (v18 + 1)), sizeof(v96));
        memset(&v95[12], 0, 12);
        memset(&v96[12], 0, 12);
        v77 = *(float *)&v80 / *(float *)(v19[23] + v21 + 140);
        linear_interpolate_matrix((float *)v86, (float *)v95, (float *)v96, v77);
      }
      v41 = (float *)(this + 44);
      v38 = a3;
      v42 = (_DWORD *)(a4 + 4);
      *(float *)v86 = *(float *)v86 * v79;
      *(float *)&v86[1] = *(float *)&v86[1] * v79;
      *(float *)&v86[2] = *(float *)&v86[2] * v79;
      v54 = *(float *)(a4 + 4) + *((float *)this + 5);
      *((float *)this + 5) = v54;
      v92 = *(float *)&v86[4] * v54;
      v93 = *(float *)&v86[5] * v54;
      v55 = v54 * *(float *)&v86[6];
      v56 = *a3 - v85;
      v87 = v56 * *(float *)v86;
      v88 = *(float *)&v86[1] * v56;
      v90 = v87 + v82;
      v91 = v88 + v83;
      v57 = v56 * *(float *)&v86[2] + v84;
      v82 = v90 + v92;
      v58 = v91 + v93;
      *((float *)this + 11) = v82;
      v83 = v58;
      *((float *)this + 12) = v83;
      v84 = v57 + v55;
      *((float *)this + 13) = v84;
      v59 = (char *)MEMORY[0x4DF904] + 4390324;
      *((_DWORD *)MEMORY[0x4DF904] + 1097581) = v86[0];
      *((_DWORD *)v59 + 1) = v86[1];
      *((_DWORD *)v59 + 2) = v86[2];
      v60 = (_DWORD *)((char *)&loc_42FDC4 + (_DWORD)MEMORY[0x4DF904]);
      *v60 = v86[4];
      v60[1] = v86[5];
      v60[2] = v86[6];
      v61 = (char *)MEMORY[0x4DF904] + 4390356;
      *((_DWORD *)MEMORY[0x4DF904] + 1097589) = v86[8];
      *((_DWORD *)v61 + 1) = v86[9];
      *((_DWORD *)v61 + 2) = v86[10];
    }
    v62 = v86[5];
    *((_DWORD *)this + 8) = v86[4];
    v63 = v86[6];
    *((_DWORD *)this + 9) = v62;
    v64 = *((_DWORD *)this + 1);
    *((_DWORD *)this + 10) = v63;
    v65 = *((float *)this + 3);
    v66 = LODWORD(v65) == *(_DWORD *)(v64 + 68) - 1;
    *(float *)&v81 = v65;
    if ( v66 )
    {
      v67 = 168 * LODWORD(v65);
      *((_DWORD *)this + 7) = *(_DWORD *)(*(_DWORD *)(v64 + 88) + 168 * LODWORD(v65) + 152);
      *((_DWORD *)this + 6) = *(_DWORD *)(*(_DWORD *)(v64 + 88) + 168 * LODWORD(v65) + 148);
    }
    else
    {
      v68 = 7 * LODWORD(v65);
      v69 = *(_DWORD *)(v64 + 88);
      v67 = 24 * v68;
      v70 = *(float *)(v69 + v67 + 320) - *(float *)(v69 + v67 + 152);
      if ( v70 <= 3.1415927 )
      {
        if ( v70 < -3.1415927 )
          v70 = v70 + 6.2831855;
      }
      else
      {
        v70 = v70 - 6.2831855;
      }
      *((float *)this + 7) = *((float *)this + 4) / *(float *)(*(_DWORD *)(v64 + 92) + v67 + 140) * v70
                           + *(float *)(v69 + v67 + 152);
      v71 = *(_DWORD *)(v64 + 88);
      v72 = *(float *)(v71 + v67 + 316) - *(float *)(v71 + v67 + 148);
      if ( v72 <= 3.1415927 )
      {
        if ( v72 < -3.1415927 )
          v72 = v72 + 6.2831855;
      }
      else
      {
        v72 = v72 - 6.2831855;
      }
      v38 = a3;
      *((float *)this + 6) = *((float *)this + 4) / *(float *)(*(_DWORD *)(v64 + 92) + v67 + 140) * v72
                           + *(float *)(v71 + v67 + 148);
    }
    v73 = *((float *)this + 4) / *(float *)(*(_DWORD *)(v64 + 92) + v67 + 140);
    v74 = *((_DWORD *)this + 14);
    *((float *)this + 7) = (v73 + (double)v81) * *(float *)(v64 + 152) / (double)*(int *)(v64 + 68);
    if ( *(_DWORD *)(v74 + 10076) == 1 )
      goto LABEL_62;
    v75 = *v38 - v85;
    if ( v75 < 0.0 )
      v75 = -v75;
    if ( v75 <= (double)*(int *)(v64 + 84) * 0.5 + 0.30000001 || *((float *)this + 5) > 0.0 )
    {
LABEL_62:
      if ( *((float *)this + 5) < 0.0 )
      {
        *((_DWORD *)this + 5) = 0;
        *v42 = 0;
      }
      return 0;
    }
    else
    {
      *v38 = *v41;
      v38[1] = v41[1];
      v38[2] = v41[2];
      *(float *)(*((_DWORD *)this + 14) + 880) = *(float *)(*((_DWORD *)this + 1) + 152)
                                               + *(float *)(*((_DWORD *)this + 14) + 880);
      if ( *v38 >= -4.0 )
      {
        if ( *v38 <= 4.0 )
          *v38 = *v38;
        else
          *v38 = 4.0;
        return *(_DWORD *)(*((_DWORD *)this + 1) + 64) == 0;
      }
      else
      {
        *v38 = -4.0;
        return *(_DWORD *)(*((_DWORD *)this + 1) + 64) == 0;
      }
    }
  }
  else
  {
    while ( 1 )
    {
      v10 = *v9 - *((float *)this + 4);
      v11 = v5 + 1;
      *((_DWORD *)this + 4) = 0;
      *((_DWORD *)this + 3) = v11;
      v78 = v78 - v10;
      if ( v11 == 2 * *(_DWORD *)(v6 + 68) )
        play_voice_manager((int)unk_751498, 4, 1u, -1);
      v12 = *((_DWORD *)this + 1);
      if ( *(_BYTE *)(v12 + 156) )
      {
        v13 = *(_DWORD *)(v12 + 68);
        v14 = *((_DWORD *)this + 3);
        if ( v14 == v13 - 1 )
        {
          v15 = *(_DWORD *)(*(int *)((char *)&unk_641184
                                   + (_DWORD)MEMORY[0x4DF904]
                                   + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                          + 56);
          *(_DWORD *)(*(int *)((char *)&unk_641184
                             + (_DWORD)MEMORY[0x4DF904]
                             + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                    + 36) = *(_DWORD *)(v15 + 164);
          *(_DWORD *)(*(int *)((char *)&unk_641184
                             + (_DWORD)MEMORY[0x4DF904]
                             + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                    + 52) = 1065353216;
        }
        else if ( v14 == 3 * v13 / 7 )
        {
          v16 = get_track_cell_row_index(*((_DWORD **)this + 2));
          *(_DWORD *)(*(int *)((char *)&unk_641184 + (_DWORD)MEMORY[0x4DF904] + 244 * v16) + 4) |= 0x80u;
          v17 = *(_DWORD *)(*(int *)((char *)&unk_641184
                                   + (_DWORD)MEMORY[0x4DF904]
                                   + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                          + 56);
          *(_DWORD *)(*(int *)((char *)&unk_641184
                             + (_DWORD)MEMORY[0x4DF904]
                             + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                    + 36) = *(_DWORD *)(v17 + 160);
          *(_DWORD *)(*(int *)((char *)&unk_641184
                             + (_DWORD)MEMORY[0x4DF904]
                             + 244 * get_track_cell_row_index(*((_DWORD **)this + 2)))
                    + 52) = 1058642330;
        }
      }
      v6 = *((_DWORD *)this + 1);
      v5 = *((_DWORD *)this + 3);
      if ( v5 == *(_DWORD *)(v6 + 68) )
        break;
      v9 = (float *)(*(_DWORD *)(v6 + 92) + 168 * v5 + 140);
      if ( v78 + *((float *)this + 4) <= *v9 )
        goto LABEL_11;
    }
    *this = 0;
    if ( v78 >= 1.0 )
      v78 = 0.99900001;
    v23 = a2 * *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 92) + 168 * *(_DWORD *)(*((_DWORD *)this + 1) + 68) - 28);
    *(float *)(a4 + 8) = v23;
    if ( v23 > 1.0 )
      *(_DWORD *)(a4 + 8) = 1065353216;
    v24 = *((_DWORD *)this + 1);
    if ( *(_DWORD *)(v24 + 56) == 31 )
    {
      *(float *)(a4 + 4) = *(float *)(a4 + 8) * 0.69999999;
      v25 = *((_DWORD *)this + 1);
      v26 = *a3;
      v27 = *(_DWORD *)(v25 + 68);
      v28 = v78 + *(float *)(v25 + 80);
      v29 = *(_DWORD *)(v25 + 92);
      v30 = v28 * *(float *)(v29 + 168 * v27 - 136);
      v31 = v29 + 168 * v27;
      v32 = (float *)(*((_DWORD *)this + 2) + 16);
      v90 = v30;
      v91 = v28 * *(float *)(v31 - 132);
      v33 = v28 * *(float *)(v31 - 128);
      v34 = *v32 + *(float *)(v31 - 120);
      v88 = *(float *)(v31 - 116) + v32[1];
      v89 = *(float *)(v31 - 112) + v32[2];
      v82 = v34 + v90;
      v35 = v88 + v91;
      *a3 = v82;
      v83 = v35;
      v36 = v89 + v33;
      a3[1] = v83;
      v84 = v36;
      a3[2] = v84;
      *a3 = v26;
      *(float *)(*((_DWORD *)this + 14) + 736) = *((float *)MEMORY[0x4DF904] + 119188) * 0.013888888;
      *(_DWORD *)(*((_DWORD *)this + 14) + 732) = *(_DWORD *)(*((_DWORD *)this + 14) + 736);
      play_voice_manager((int)unk_751498, 15, 0, -1);
    }
    else
    {
      a3[2] = *(float *)(*(_DWORD *)(v24 + 92) + 168 * *(_DWORD *)(v24 + 68) - 112)
            + *(float *)(*((_DWORD *)this + 2) + 24)
            + *(float *)(v24 + 80)
            + v78;
    }
    *(float *)(*((_DWORD *)this + 14) + 880) = *(float *)(*((_DWORD *)this + 1) + 152)
                                             + *(float *)(*((_DWORD *)this + 14) + 880);
    return 3;
  }
}

