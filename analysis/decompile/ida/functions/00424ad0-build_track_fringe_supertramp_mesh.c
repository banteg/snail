/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_supertramp_mesh @ 0x424ad0 */
/* selector: build_track_fringe_supertramp_mesh */

int __thiscall sub_424AD0(_DWORD *this, _BYTE *a2)
{
  _DWORD *v3; // eax
  int *v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // ebx
  int v8; // ebp
  float *v9; // edi
  float *v10; // ecx
  float *v11; // edx
  float *v12; // ecx
  float *v13; // eax
  double v14; // st7
  double v15; // st7
  float v16; // edx
  float *v17; // ecx
  float *v18; // eax
  double v19; // st7
  double v20; // st7
  float v21; // edx
  __int16 v22; // bp
  int v23; // edi
  int v24; // eax
  __int16 v25; // dx
  __int16 v26; // bp
  float *v27; // eax
  double v28; // st7
  float *v29; // ecx
  double v30; // st7
  float v31; // eax
  float *v32; // eax
  double v33; // st7
  double v34; // st6
  double v35; // st7
  float v36; // edx
  int v37; // eax
  _DWORD *v38; // edx
  _DWORD *v39; // eax
  _DWORD *v40; // edi
  _DWORD *v41; // ecx
  int result; // eax
  int v43; // [esp+10h] [ebp-5Ch]
  int v44; // [esp+14h] [ebp-58h]
  float v45; // [esp+18h] [ebp-54h] BYREF
  float v46; // [esp+1Ch] [ebp-50h]
  float v47; // [esp+20h] [ebp-4Ch]
  float v48; // [esp+24h] [ebp-48h]
  float v49; // [esp+28h] [ebp-44h]
  float v50; // [esp+2Ch] [ebp-40h]
  float v51; // [esp+30h] [ebp-3Ch]
  float v52; // [esp+34h] [ebp-38h]
  float v53; // [esp+38h] [ebp-34h]
  float v54; // [esp+3Ch] [ebp-30h]
  float v55; // [esp+40h] [ebp-2Ch]
  float v56; // [esp+44h] [ebp-28h]
  float v57; // [esp+48h] [ebp-24h]
  float v58; // [esp+4Ch] [ebp-20h]
  float v59; // [esp+50h] [ebp-1Ch]
  float v60; // [esp+58h] [ebp-14h]
  float v61; // [esp+5Ch] [ebp-10h]
  float v62; // [esp+64h] [ebp-8h]
  float v63; // [esp+68h] [ebp-4h]

  v3 = add_object_to_list(unk_4B7648);
  set_bod_object(this + 24, (int)v3);
  v4 = (int *)*(this + 33);
  v5 = v4[4];
  v4[5] = 5;
  v4[4] = v5 | 0x100000;
  request_object_vertices(v4, 4 * *(this + 17) + 6);
  request_object_facequads(v4, 2 * *(this + 17) + 1);
  v6 = v4[14];
  v7 = v4[23];
  v8 = 0;
  v44 = v6;
  if ( (int)*(this + 17) >= 0 )
  {
    v9 = (float *)(v6 + 20);
    do
    {
      v10 = v9 - 5;
      v11 = (float *)(*(_DWORD *)(*(this + 9) + 56) + 12 * (v8 * (*(this + 21) + 1) + 1));
      *v10 = *v11;
      v10[1] = v11[1];
      v10[2] = v11[2];
      v12 = v9 - 2;
      v13 = (float *)(*(_DWORD *)(*(this + 9) + 56) + 12 * v8 * (*(this + 21) + 1));
      *v12 = *v13;
      v12[1] = v13[1];
      *v9 = v13[2];
      v48 = *(v9 - 2) - *(v9 - 5);
      v49 = *(v9 - 1) - *(v9 - 4);
      v14 = *v9 - *(v9 - 3);
      v45 = v48;
      v46 = v49;
      v50 = v14;
      v47 = v50;
      normalize_vector(&v45);
      v60 = v46 * 0.40000001;
      v61 = v47 * 0.40000001;
      v51 = v45 * 0.40000001 + *(v9 - 2);
      v52 = v60 + *(v9 - 1);
      v15 = v61 + *v9;
      v16 = v52;
      *(v9 - 5) = v51;
      *(v9 - 4) = v16;
      v53 = v15;
      *(v9 - 3) = v53;
      v17 = (float *)(*(_DWORD *)(*(this + 9) + 56) + 12 * (*(this + 21) + v8 * (*(this + 21) + 1)) - 12);
      v9[1] = *v17;
      v9[2] = v17[1];
      v9[3] = v17[2];
      v18 = (float *)(*(_DWORD *)(*(this + 9) + 56) + 12 * (*(this + 21) + v8 * (*(this + 21) + 1)));
      v9[4] = *v18;
      v9[5] = v18[1];
      v9[6] = v18[2];
      v54 = v9[4] - v9[1];
      v55 = v9[5] - v9[2];
      v19 = v9[6] - v9[3];
      v45 = v54;
      v46 = v55;
      v56 = v19;
      v47 = v56;
      normalize_vector(&v45);
      ++v8;
      v9 += 12;
      v62 = v46 * 0.40000001;
      v63 = v47 * 0.40000001;
      v57 = v45 * 0.40000001 + *(v9 - 8);
      v58 = v62 + *(v9 - 7);
      v20 = v63 + *(v9 - 6);
      v21 = v58;
      *(v9 - 11) = v57;
      *(v9 - 10) = v21;
      v59 = v20;
      *(v9 - 9) = v59;
    }
    while ( v8 <= *(this + 17) );
    v6 = v44;
  }
  v22 = 0;
  v43 = 0;
  if ( (int)*(this + 17) > 0 )
  {
    v23 = v7 + 2;
    while ( 1 )
    {
      v24 = get_or_create_texture_ref(&texture_list, a2, 0, 0);
      v25 = 4 * v22 + 4;
      *(_DWORD *)(v23 + 10) = v24;
      v26 = 4 * v22;
      *(_WORD *)v23 = v25;
      *(_WORD *)(v23 + 2) = v26 + 5;
      *(_WORD *)(v23 + 4) = v26 + 1;
      *(_WORD *)(v23 + 6) = v26;
      *(_DWORD *)(v23 + 38) = 1056964608;
      *(_DWORD *)(v23 + 42) = 1065353216;
      *(_DWORD *)(v23 + 14) = 1056964608;
      *(_DWORD *)(v23 + 18) = 1065353216;
      *(_DWORD *)(v23 + 22) = 1056964608;
      *(_DWORD *)(v23 + 26) = 0;
      *(_DWORD *)(v23 + 30) = 1056964608;
      *(_DWORD *)(v23 + 34) = 0;
      *(_DWORD *)(v23 + 58) = get_or_create_texture_ref(&texture_list, a2, 0, 0);
      *(_WORD *)(v23 + 48) = v26 + 7;
      *(_WORD *)(v23 + 50) = v26 + 6;
      *(_WORD *)(v23 + 52) = v26 + 2;
      *(_WORD *)(v23 + 54) = v26 + 3;
      *(_DWORD *)(v23 + 86) = 1056964608;
      *(_DWORD *)(v23 + 90) = 0;
      *(_DWORD *)(v23 + 62) = 1056964608;
      *(_DWORD *)(v23 + 66) = 0;
      *(_DWORD *)(v23 + 70) = 1056964608;
      *(_DWORD *)(v23 + 74) = 1065353216;
      *(_DWORD *)(v23 + 78) = 1056964608;
      *(_DWORD *)(v23 + 82) = 1065353216;
      v23 += 96;
      if ( ++v43 >= *(this + 17) )
        break;
      v22 = v43;
    }
    v6 = v44;
  }
  v27 = (float *)(v6 + 48 * *(this + 17));
  v28 = *v27 - *(v27 - 12);
  v29 = (float *)(v6 + 16 * (3 * *(this + 17) + 3));
  v62 = v27[1] - *(v27 - 11);
  v63 = v27[2] - *(v27 - 10);
  v60 = v62 * 0.40000001;
  v61 = v63 * 0.40000001;
  v57 = v28 * 0.40000001 + *v27;
  v58 = v60 + v27[1];
  v30 = v61 + v27[2];
  v31 = v58;
  *v29 = v57;
  v29[1] = v31;
  v59 = v30;
  v29[2] = v59;
  v32 = (float *)(v6 + 48 * *(this + 17));
  v33 = v32[6] - *(v32 - 6);
  v34 = v32[7] - *(v32 - 5);
  v32 += 15;
  v62 = v34;
  v63 = *(v32 - 7) - *(v32 - 19);
  v60 = v62 * 0.40000001;
  v61 = v63 * 0.40000001;
  v57 = v33 * 0.40000001 + *(v32 - 9);
  v58 = v60 + *(v32 - 8);
  v35 = v61 + *(v32 - 7);
  v36 = v58;
  *v32 = v57;
  v32[1] = v36;
  v59 = v35;
  v32[2] = v59;
  v37 = *(this + 17);
  v38 = (_DWORD *)(v6 + 16 * (3 * v37 + 3));
  v39 = (_DWORD *)(v6 + 48 * v37);
  *v39 = *v38;
  v39[1] = v38[1];
  v39[2] = v38[2];
  v40 = (_DWORD *)(48 * *(this + 17) + v6);
  v41 = v40 + 15;
  v40 += 6;
  *v40 = *v41;
  v40[1] = v41[1];
  v40[2] = v41[2];
  *(_DWORD *)(96 * *(this + 17) + v7 + 12) = get_or_create_texture_ref(&texture_list, a2, 0, 0);
  *(_WORD *)(96 * *(this + 17) + v7 + 2) = 4 * *((_WORD *)this + 34) + 1;
  *(_WORD *)(96 * *(this + 17) + v7 + 4) = 4 * *((_WORD *)this + 34) + 3;
  *(_WORD *)(96 * *(this + 17) + v7 + 6) = 4 * *((_WORD *)this + 34) + 5;
  *(_WORD *)(96 * *(this + 17) + v7 + 8) = 4 * (*((_WORD *)this + 34) + 1);
  *(_DWORD *)(96 * *(this + 17) + v7 + 16) = 1056964608;
  *(_DWORD *)(96 * *(this + 17) + v7 + 20) = 0;
  *(_DWORD *)(96 * *(this + 17) + v7 + 24) = 1056964608;
  *(_DWORD *)(96 * *(this + 17) + v7 + 28) = 0;
  *(_DWORD *)(96 * *(this + 17) + v7 + 32) = 1056964608;
  *(_DWORD *)(96 * *(this + 17) + v7 + 36) = 1065353216;
  result = 96 * *(this + 17);
  *(_DWORD *)(result + v7 + 40) = 1056964608;
  *(_DWORD *)(96 * *(this + 17) + v7 + 44) = 1065353216;
  return result;
}

