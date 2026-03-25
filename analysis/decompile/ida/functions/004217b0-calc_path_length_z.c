/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_path_length_z @ 0x4217b0 */
/* selector: calc_path_length_z */

int __thiscall sub_4217B0(char *this, float a2, float *a3, float *a4)
{
  int v5; // ecx
  _DWORD *v6; // edx
  int v7; // esi
  double v8; // st7
  int v9; // ecx
  double v10; // st6
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // ecx
  _DWORD *v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // esi
  double v19; // st7
  int v20; // edx
  double v21; // st6
  int v22; // eax
  float *v23; // edx
  double v24; // st7
  double v25; // st6
  double v26; // st6
  double v27; // st6
  int v28; // eax
  int *v29; // edx
  double v31; // st7
  float *v32; // esi
  float *v33; // edx
  int *v34; // ecx
  double v35; // st7
  double v36; // st6
  int v37; // ecx
  double v38; // st7
  float *v39; // esi
  float *v40; // ecx
  double v41; // st7
  double v42; // st7
  double v43; // st6
  double v44; // st7
  float *v45; // eax
  _DWORD *v46; // eax
  _DWORD *v47; // eax
  _DWORD *v48; // eax
  _DWORD *v49; // edi
  double v50; // st7
  int v51; // edi
  int v52; // eax
  _DWORD *v53; // edx
  float v54; // [esp+0h] [ebp-114h]
  float v55; // [esp+Ch] [ebp-108h]
  float v56; // [esp+20h] [ebp-F4h]
  float v57; // [esp+24h] [ebp-F0h]
  int v58; // [esp+28h] [ebp-ECh] BYREF
  float v59; // [esp+2Ch] [ebp-E8h]
  float v60; // [esp+30h] [ebp-E4h]
  float v61; // [esp+34h] [ebp-E0h]
  float v62; // [esp+38h] [ebp-DCh]
  float v63; // [esp+3Ch] [ebp-D8h]
  float v64; // [esp+40h] [ebp-D4h]
  float v65; // [esp+44h] [ebp-D0h]
  float v66; // [esp+48h] [ebp-CCh]
  float v67; // [esp+4Ch] [ebp-C8h]
  float v68; // [esp+50h] [ebp-C4h]
  int v69; // [esp+54h] [ebp-C0h] BYREF
  float v70; // [esp+58h] [ebp-BCh]
  float v71; // [esp+5Ch] [ebp-B8h]
  int v72; // [esp+64h] [ebp-B0h]
  int v73; // [esp+68h] [ebp-ACh]
  int v74; // [esp+6Ch] [ebp-A8h]
  int v75; // [esp+74h] [ebp-A0h]
  int v76; // [esp+78h] [ebp-9Ch]
  int v77; // [esp+7Ch] [ebp-98h]
  int v78; // [esp+84h] [ebp-90h]
  int v79; // [esp+88h] [ebp-8Ch]
  int v80[16]; // [esp+94h] [ebp-80h] BYREF
  int v81[16]; // [esp+D4h] [ebp-40h] BYREF

  v5 = *((_DWORD *)this + 3);
  v6 = *((_DWORD **)this + 1);
  v7 = v6[23];
  v8 = a2 * *(float *)(v7 + 168 * v5 + 140);
  if ( v8 + *((float *)this + 4) <= *(float *)(v7 + 168 * v5 + 140) )
  {
LABEL_4:
    v11 = *((_DWORD *)this + 3);
    v57 = v8 + *((float *)this + 4);
    *((float *)this + 4) = v57;
    v12 = v6[17] - 1;
    v13 = 168 * v11;
    v14 = 168 * v11 + v6[22];
    if ( v11 == v12 )
      v59 = *(float *)(v14 + 144);
    else
      v59 = v57 / *(float *)(168 * v11 + v6[23] + 140) * (*(float *)(v14 + 312) - *(float *)(v14 + 144))
          + *(float *)(v14 + 144);
    if ( v11 == v12 )
      v56 = *(float *)(v14 + 156);
    else
      v56 = v57 / *(float *)(v13 + v6[23] + 140) * (*(float *)(v14 + 324) - *(float *)(v14 + 156))
          + *(float *)(v14 + 156);
    if ( v11 == v12 )
      v58 = *(int *)(v14 + 160);
    else
      *(float *)&v58 = v57 / *(float *)(v13 + v6[23] + 140) * (*(float *)(v14 + 328) - *(float *)(v14 + 160))
                     + *(float *)(v14 + 160);
    if ( v6[14] == 42 )
    {
      v32 = a3;
      v54 = *a3 - v59;
      compute_kind42_attachment_transform(*(float *)&v58, v54, 0.49000001, (int)&v69, (float *)&v58);
      v33 = a4;
      v34 = (int *)(this + 24);
      v35 = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 92) + 168 * *((_DWORD *)this + 3) + 136)
          * *((float *)this + 4)
          + *(float *)(*((_DWORD *)this + 2) + 24)
          + *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 92) + 168 * *((_DWORD *)this + 3) + 56);
      *(float *)&v69 = *(float *)&v69 * v56;
      v70 = v70 * v56;
      v71 = v71 * v56;
      v36 = a4[1] + *((float *)this + 5);
      *((_DWORD *)this + 6) = v78;
      *((_DWORD *)this + 7) = v79;
      *((float *)this + 5) = v36;
      *((float *)this + 8) = v35;
    }
    else
    {
      v37 = v6[23];
      v38 = v57 * *(float *)(v13 + v37 + 128);
      v39 = (float *)(v13 + v37);
      v40 = *((float **)this + 2);
      v60 = v38 * v56 + v39[12] + v40[4];
      v61 = v57 * v39[33] * v56 + v39[13] + v40[5];
      v62 = v57 * v39[34] + v39[14] + v40[6];
      if ( v11 == v12 )
      {
        set_matrix_identity(&v69);
      }
      else
      {
        qmemcpy(v81, v39, sizeof(v81));
        qmemcpy(v80, (const void *)(v6[23] + 168 * (v11 + 1)), sizeof(v80));
        memset(&v81[12], 0, 12);
        memset(&v80[12], 0, 12);
        v55 = v57 / *(float *)(v13 + v6[23] + 140);
        linear_interpolate_matrix((float *)&v69, (float *)v81, (float *)v80, v55);
      }
      v33 = a4;
      v32 = a3;
      v34 = (int *)(this + 24);
      *(float *)&v69 = *(float *)&v69 * v56;
      v70 = v70 * v56;
      v71 = v71 * v56;
      *((float *)this + 5) = a4[1] + *((float *)this + 5);
      v41 = *a3 - v59;
      v66 = v41 * *(float *)&v69;
      v67 = v70 * v41;
      v42 = v41 * v71;
      v63 = v66 + v60;
      v43 = v67 + v61;
      *((float *)this + 6) = v63;
      v64 = v43;
      v44 = v42 + v62;
      *((float *)this + 7) = v64;
      v65 = v44;
      *((float *)this + 8) = v65;
    }
    v45 = (float *)(*((_DWORD *)this + 9) + 452);
    *v45 = *(float *)&v69;
    v45[1] = v70;
    v45[2] = v71;
    v46 = (_DWORD *)(*((_DWORD *)this + 9) + 468);
    *v46 = v72;
    v46[1] = v73;
    v46[2] = v74;
    v47 = (_DWORD *)(*((_DWORD *)this + 9) + 484);
    *v47 = v75;
    v47[1] = v76;
    v47[2] = v77;
    v48 = *((_DWORD **)this + 9);
    v49 = v48 + 150;
    v48 += 147;
    *v48 = *v49;
    v48[1] = v49[1];
    v48[2] = v49[2];
    v50 = *v32 - v59;
    if ( v50 < 0.0 )
      v50 = -v50;
    v51 = *((_DWORD *)this + 1);
    if ( v50 <= (double)*(int *)(v51 + 84) * 0.5 + 0.30000001 )
    {
      if ( *(_DWORD *)(v51 + 56) != 42 )
        *v32 = *v32 + *v33;
      return 0;
    }
    else
    {
      v52 = *v34;
      v53 = (_DWORD *)(*((_DWORD *)this + 9) + 500);
      *this = 0;
      *v53 = v52;
      v53[1] = v34[1];
      v53[2] = v34[2];
      return *(_DWORD *)(*((_DWORD *)this + 1) + 64) == 0;
    }
  }
  else
  {
    while ( 1 )
    {
      v9 = *((_DWORD *)this + 3);
      v10 = *(float *)(v7 + 168 * v9 + 140) - *((float *)this + 4);
      *((_DWORD *)this + 4) = 0;
      *((_DWORD *)this + 3) = v9 + 1;
      v8 = v8 - v10;
      if ( v9 + 1 == v6[17] )
        break;
      v7 = v6[23];
      if ( v8 <= *(float *)(v7 + 168 * (v9 + 1) + 140) )
        goto LABEL_4;
    }
    *this = 0;
    a4[2] = a2 * *(float *)(v6[23] + 168 * v6[17] - 28);
    v15 = (_DWORD *)(*((_DWORD *)this + 9) + 500);
    *v15 = *((_DWORD *)this + 6);
    v15[1] = *((_DWORD *)this + 7);
    v15[2] = *((_DWORD *)this + 8);
    v16 = *((_DWORD *)this + 1);
    if ( *(_DWORD *)(v16 + 56) == 31 )
    {
      a4[1] = a4[2] * 0.69999999;
      v58 = *(int *)a3;
      v17 = *((_DWORD *)this + 1);
      v18 = *(_DWORD *)(v17 + 68);
      v19 = v8 + *(float *)(v17 + 80);
      v20 = *(_DWORD *)(v17 + 92);
      v21 = v19 * *(float *)(v20 + 168 * v18 - 136);
      v22 = v20 + 168 * v18;
      v23 = (float *)(*((_DWORD *)this + 2) + 16);
      v63 = v21;
      v64 = v19 * *(float *)(v22 - 132);
      v24 = v19 * *(float *)(v22 - 128);
      v25 = *v23 + *(float *)(v22 - 120);
      v67 = *(float *)(v22 - 116) + v23[1];
      v68 = *(float *)(v22 - 112) + v23[2];
      v60 = v25 + v63;
      v26 = v67 + v64;
      *a3 = v60;
      v61 = v26;
      v27 = v68 + v24;
      a3[1] = v61;
      v62 = v27;
      a3[2] = v62;
      v28 = v58;
      *a3 = *(float *)&v58;
      v29 = (int *)(*((_DWORD *)this + 9) + 500);
      *v29 = v28;
      v29[1] = *((_DWORD *)a3 + 1);
      v29[2] = *((_DWORD *)a3 + 2);
    }
    else
    {
      v31 = v8
          + *(float *)(*(_DWORD *)(v16 + 92) + 168 * *(_DWORD *)(v16 + 68) - 112)
          + *(float *)(*((_DWORD *)this + 2) + 24)
          + *(float *)(v16 + 80);
      a3[2] = v31;
      *(float *)(*((_DWORD *)this + 9) + 508) = v31;
    }
    return 3;
  }
}

