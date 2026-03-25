/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_facequad_normals @ 0x42fcb0 */
/* selector: calc_object_facequad_normals */

int __thiscall sub_42FCB0(int *this)
{
  _BYTE *v2; // ebx
  int v3; // edi
  int v4; // ecx
  unsigned __int16 *v5; // eax
  float *v6; // ebp
  float *v7; // edx
  double v8; // st7
  float *v9; // ebp
  double v10; // st7
  int v11; // ecx
  double v12; // st7
  float *v13; // eax
  int v14; // eax
  int v15; // ecx
  float *v16; // ebp
  float *v17; // edx
  double v18; // st7
  float *v19; // ebp
  double v20; // st7
  int v21; // ecx
  double v22; // st7
  float *v23; // edx
  int v24; // ecx
  int v25; // eax
  double v26; // st7
  float *v27; // eax
  int v28; // eax
  double v29; // st7
  float *v30; // eax
  int v31; // eax
  double v32; // st7
  float *v33; // eax
  int v34; // ecx
  int v35; // eax
  double v36; // st7
  float *v37; // eax
  unsigned __int16 v38; // dx
  unsigned __int16 v39; // dx
  int v40; // eax
  double v41; // st7
  float *v42; // eax
  int v43; // eax
  double v44; // st7
  float *v45; // eax
  int v46; // eax
  double v47; // st7
  float *v48; // eax
  int v49; // ecx
  int v50; // eax
  double v51; // st7
  float *v52; // eax
  unsigned __int16 v53; // dx
  int v54; // eax
  unsigned __int16 v55; // dx
  int v56; // ecx
  unsigned __int16 *v57; // eax
  bool v58; // cc
  float *v59; // ebp
  double v60; // st7
  float *v61; // eax
  float *v62; // eax
  double v63; // st7
  float v64; // edx
  int v66; // [esp+10h] [ebp-68h]
  int v67; // [esp+10h] [ebp-68h]
  int v68; // [esp+14h] [ebp-64h]
  float v69; // [esp+18h] [ebp-60h] BYREF
  float v70; // [esp+1Ch] [ebp-5Ch]
  float v71; // [esp+20h] [ebp-58h]
  float v72; // [esp+24h] [ebp-54h] BYREF
  float v73; // [esp+28h] [ebp-50h]
  float v74; // [esp+2Ch] [ebp-4Ch]
  float v75; // [esp+30h] [ebp-48h] BYREF
  float v76; // [esp+34h] [ebp-44h]
  float v77; // [esp+38h] [ebp-40h]
  float v78; // [esp+3Ch] [ebp-3Ch] BYREF
  float v79; // [esp+40h] [ebp-38h]
  float v80; // [esp+44h] [ebp-34h]
  float v81; // [esp+48h] [ebp-30h]
  float v82; // [esp+4Ch] [ebp-2Ch]
  float v83; // [esp+50h] [ebp-28h]
  float v84; // [esp+54h] [ebp-24h]
  float v85; // [esp+58h] [ebp-20h]
  float v86; // [esp+5Ch] [ebp-1Ch]
  float v87; // [esp+60h] [ebp-18h]
  float v88; // [esp+64h] [ebp-14h]
  float v89; // [esp+68h] [ebp-10h]
  float v90; // [esp+6Ch] [ebp-Ch]
  float v91; // [esp+70h] [ebp-8h]
  float v92; // [esp+74h] [ebp-4h]

  request_object_facequad_normals(this);
  v2 = allocate_tracked_memory(4 * *(this + 11), (int)aNormalTally);
  memset(v2, 0, 4 * *(this + 11));
  v3 = 0;
  v66 = 0;
  if ( *(this + 21) > 0 )
  {
    v68 = 0;
    do
    {
      v4 = *(this + 14);
      v5 = (unsigned __int16 *)(v3 + *(this + 23));
      v6 = (float *)(v4 + 12 * v5[1]);
      v7 = (float *)(v4 + 12 * v5[2]);
      v81 = *v7 - *v6;
      v82 = v7[1] - v6[1];
      v8 = v7[2] - v6[2];
      v78 = v81;
      v79 = v82;
      v83 = v8;
      v80 = v83;
      v9 = (float *)(v4 + 12 * v5[1]);
      LOWORD(v7) = v5[3];
      v10 = *(float *)(v4 + 12 * (unsigned __int16)v7) - *v9;
      v11 = v4 + 12 * (unsigned __int16)v7;
      v84 = v10;
      v85 = *(float *)(v11 + 4) - v9[1];
      v12 = *(float *)(v11 + 8) - v9[2];
      v75 = v84;
      v76 = v85;
      v86 = v12;
      v77 = v86;
      cross_vectors(&v72, &v78, &v75);
      normalize_vector(&v72);
      v13 = (float *)(v68 + *(this + 24));
      *v13 = v72;
      v13[1] = v73;
      v13[2] = v74;
      v14 = *(this + 23) + v3;
      if ( *(char *)v14 >= 0 )
      {
        v15 = *(this + 14);
        v16 = (float *)(v15 + 12 * *(unsigned __int16 *)(v14 + 2));
        v17 = (float *)(v15 + 12 * *(unsigned __int16 *)(v14 + 6));
        v87 = *v17 - *v16;
        v88 = v17[1] - v16[1];
        v18 = v17[2] - v16[2];
        v78 = v87;
        v79 = v88;
        v89 = v18;
        v80 = v89;
        v19 = (float *)(v15 + 12 * *(unsigned __int16 *)(v14 + 2));
        LOWORD(v17) = *(_WORD *)(v14 + 8);
        v20 = *(float *)(v15 + 12 * (unsigned __int16)v17) - *v19;
        v21 = v15 + 12 * (unsigned __int16)v17;
        v90 = v20;
        v91 = *(float *)(v21 + 4) - v19[1];
        v22 = *(float *)(v21 + 8) - v19[2];
        v75 = v90;
        v76 = v91;
        v92 = v22;
        v77 = v92;
        cross_vectors(&v69, &v78, &v75);
        normalize_vector(&v69);
        v23 = (float *)(*(this + 24) + v68 + 12);
        *v23 = v69;
        v23[1] = v70;
        v23[2] = v71;
      }
      v24 = v3 + *(this + 23);
      if ( *(char *)v24 >= 0 )
      {
        v25 = *(this + 17);
        v26 = v69 + *(float *)(v25 + 12 * *(unsigned __int16 *)(v24 + 2));
        v27 = (float *)(v25 + 12 * *(unsigned __int16 *)(v24 + 2));
        *v27 = v26;
        v27[1] = v70 + v27[1];
        v27[2] = v71 + v27[2];
        v28 = *(this + 17);
        v29 = v69 + *(float *)(v28 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 4));
        v30 = (float *)(v28 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 4));
        *v30 = v29;
        v30[1] = v70 + v30[1];
        v30[2] = v71 + v30[2];
        v31 = *(this + 17);
        v32 = v69 + *(float *)(v31 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 6));
        v33 = (float *)(v31 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 6));
        *v33 = v32;
        v33[1] = v70 + v33[1];
        v33[2] = v71 + v33[2];
        v34 = *(this + 23);
        v35 = *(this + 17);
        v36 = v69 + *(float *)(v35 + 12 * *(unsigned __int16 *)(v34 + v3 + 8));
        v37 = (float *)(v35 + 12 * *(unsigned __int16 *)(v34 + v3 + 8));
        *v37 = v36;
        v37[1] = v70 + v37[1];
        v37[2] = v71 + v37[2];
        v38 = *(_WORD *)(*(this + 23) + v3 + 2);
        *(float *)&v2[4 * v38] = *(float *)&v2[4 * v38] + 1.0;
        LOWORD(v34) = *(_WORD *)(*(this + 23) + v3 + 4);
        *(float *)&v2[4 * (unsigned __int16)v34] = *(float *)&v2[4 * (unsigned __int16)v34] + 1.0;
        LOWORD(v37) = *(_WORD *)(*(this + 23) + v3 + 6);
        *(float *)&v2[4 * (unsigned __int16)v37] = *(float *)&v2[4 * (unsigned __int16)v37] + 1.0;
        v39 = *(_WORD *)(*(this + 23) + v3 + 8);
        *(float *)&v2[4 * v39] = *(float *)&v2[4 * v39] + 1.0;
      }
      v40 = *(this + 17);
      v41 = v72 + *(float *)(v40 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 2));
      v42 = (float *)(v40 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 2));
      *v42 = v41;
      v42[1] = v73 + v42[1];
      v42[2] = v74 + v42[2];
      v43 = *(this + 17);
      v44 = v72 + *(float *)(v43 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 4));
      v45 = (float *)(v43 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 4));
      *v45 = v44;
      v45[1] = v73 + v45[1];
      v45[2] = v74 + v45[2];
      v46 = *(this + 17);
      v47 = v72 + *(float *)(v46 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 6));
      v48 = (float *)(v46 + 12 * *(unsigned __int16 *)(*(this + 23) + v3 + 6));
      *v48 = v47;
      v48[1] = v73 + v48[1];
      v48[2] = v74 + v48[2];
      v49 = *(this + 23);
      v50 = *(this + 17);
      v51 = v72 + *(float *)(v50 + 12 * *(unsigned __int16 *)(v49 + v3 + 8));
      v52 = (float *)(v50 + 12 * *(unsigned __int16 *)(v49 + v3 + 8));
      *v52 = v51;
      v52[1] = v73 + v52[1];
      v52[2] = v74 + v52[2];
      v53 = *(_WORD *)(*(this + 23) + v3 + 2);
      *(float *)&v2[4 * v53] = *(float *)&v2[4 * v53] + 2.0999999;
      LOWORD(v49) = *(_WORD *)(*(this + 23) + v3 + 4);
      *(float *)&v2[4 * (unsigned __int16)v49] = *(float *)&v2[4 * (unsigned __int16)v49] + 2.0999999;
      v54 = *(unsigned __int16 *)(*(this + 23) + v3 + 6);
      *(float *)&v2[4 * v54] = *(float *)&v2[4 * v54] + 2.0999999;
      v55 = *(_WORD *)(*(this + 23) + v3 + 8);
      *(float *)&v2[4 * v55] = *(float *)&v2[4 * v55] + 2.0999999;
      v56 = *(this + 11);
      v57 = (unsigned __int16 *)(v3 + *(this + 23));
      if ( v57[1] > v56 || v57[2] > v56 || v57[3] > v56 || v57[4] > v56 )
        report_errorf(aInvalidFaceVer);
      v3 += 48;
      v58 = ++v66 < *(this + 21);
      v68 += 24;
    }
    while ( v58 );
    v3 = 0;
  }
  v67 = 0;
  if ( *(this + 11) > 0 )
  {
    v59 = (float *)v2;
    do
    {
      v60 = *v59;
      v61 = (float *)(*(this + 17) + v3);
      *v61 = *v61 / v60;
      v61[1] = v61[1] / v60;
      v61[2] = v61[2] / v60;
      normalize_vector((float *)(*(this + 17) + v3));
      ++v59;
      v62 = (float *)(v3 + *(this + 17));
      v3 += 12;
      v90 = *v62 * -1.0;
      v91 = v62[1] * -1.0;
      v63 = v62[2] * -1.0;
      v64 = v91;
      *v62 = v90;
      v62[1] = v64;
      v92 = v63;
      v62[2] = v92;
      ++v67;
    }
    while ( v67 < *(this + 11) );
  }
  return free_tracked_memory((int)v2);
}

