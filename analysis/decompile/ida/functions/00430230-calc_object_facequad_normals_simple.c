/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_facequad_normals_simple @ 0x430230 */
/* selector: calc_object_facequad_normals_simple */

// Recomputes only the per-face quad-normal pairs for the current vertex positions without rebuilding the full accumulated vertex-normal table. Used by the distort path before the toon edge pass reuses the updated face data.
int __thiscall sub_430230(int *this)
{
  int result; // eax
  int v3; // ebp
  int v4; // ebx
  int v5; // ecx
  unsigned __int16 *v6; // eax
  float *v7; // edi
  float *v8; // edx
  double v9; // st7
  float *v10; // edi
  float *v11; // eax
  double v12; // st7
  float *v13; // eax
  int v14; // eax
  int v15; // edi
  float *v16; // edx
  int v17; // eax
  double v18; // st7
  int v19; // eax
  double v20; // st7
  float *v21; // ecx
  int v22; // [esp+8h] [ebp-58h]
  float v23; // [esp+Ch] [ebp-54h] BYREF
  float v24; // [esp+10h] [ebp-50h]
  float v25; // [esp+14h] [ebp-4Ch]
  float v26; // [esp+18h] [ebp-48h]
  float v27; // [esp+1Ch] [ebp-44h]
  float v28; // [esp+20h] [ebp-40h]
  float v29; // [esp+24h] [ebp-3Ch]
  float v30; // [esp+28h] [ebp-38h]
  float v31; // [esp+2Ch] [ebp-34h]
  float v32; // [esp+30h] [ebp-30h]
  float v33; // [esp+34h] [ebp-2Ch]
  float v34; // [esp+38h] [ebp-28h]
  float v35[3]; // [esp+3Ch] [ebp-24h] BYREF
  float v36[3]; // [esp+48h] [ebp-18h] BYREF
  float v37[3]; // [esp+54h] [ebp-Ch] BYREF

  request_object_facequad_normals(this);
  result = *(this + 21);
  v3 = 0;
  v22 = 0;
  if ( result > 0 )
  {
    v4 = 0;
    do
    {
      v5 = *(this + 14);
      v6 = (unsigned __int16 *)(v4 + *(this + 23));
      v7 = (float *)(v5 + 12 * v6[1]);
      v8 = (float *)(v5 + 12 * v6[2]);
      v26 = *v8 - *v7;
      v27 = v8[1] - v7[1];
      v9 = v8[2] - v7[2];
      v36[0] = v26;
      v36[1] = v27;
      v28 = v9;
      v36[2] = v28;
      v10 = (float *)(v5 + 12 * v6[1]);
      v11 = (float *)(v5 + 12 * v6[3]);
      v29 = *v11 - *v10;
      v30 = v11[1] - v10[1];
      v12 = v11[2] - v10[2];
      v23 = v29;
      v24 = v30;
      v31 = v12;
      v25 = v31;
      cross_vectors(v35, v36, &v23);
      normalize_vector(v35);
      v13 = (float *)(v3 + *(this + 24));
      *v13 = v35[0];
      v13[1] = v35[1];
      v13[2] = v35[2];
      v14 = v4 + *(this + 23);
      if ( *(char *)v14 >= 0 )
      {
        v15 = *(this + 14);
        v16 = (float *)(v15 + 12 * *(unsigned __int16 *)(v14 + 2));
        v17 = 3 * *(unsigned __int16 *)(v14 + 8);
        v18 = *(float *)(v15 + 4 * v17) - *v16;
        v19 = v15 + 4 * v17;
        v32 = v18;
        v33 = *(float *)(v19 + 4) - v16[1];
        v20 = *(float *)(v19 + 8) - v16[2];
        v23 = v32;
        v24 = v33;
        v34 = v20;
        v25 = v34;
        cross_vectors(v37, v36, &v23);
        normalize_vector(v37);
        v21 = (float *)(*(this + 24) + v3 + 12);
        *v21 = v37[0];
        v21[1] = v37[1];
        v21[2] = v37[2];
      }
      result = v22 + 1;
      v4 += 48;
      v3 += 24;
      ++v22;
    }
    while ( v22 < *(this + 21) );
  }
  return result;
}

