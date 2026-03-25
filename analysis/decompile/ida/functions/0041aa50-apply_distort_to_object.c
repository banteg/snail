/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_distort_to_object @ 0x41aa50 */
/* selector: apply_distort_to_object */

void __thiscall sub_41AA50(float *this, int a2)
{
  char v4; // cl
  int v5; // ebx
  double v7; // st7
  char v8; // c0
  double v10; // st6
  char v11; // c0
  double v13; // st7
  char v14; // c0
  char v16; // c0
  int v17; // eax
  int v18; // ebp
  int v19; // edi
  int v20; // ebx
  double v22; // st7
  char v23; // c0
  double v24; // st7
  int v25; // edx
  int v26; // eax
  int v27; // ecx
  double v28; // st7
  double v29; // st7
  int v30; // edx
  int v31; // eax
  int v32; // ecx
  double v33; // st7
  float v34; // [esp+0h] [ebp-1Ch]
  float v35; // [esp+0h] [ebp-1Ch]
  float v36; // [esp+0h] [ebp-1Ch]
  float v37; // [esp+0h] [ebp-1Ch]
  float v38; // [esp+0h] [ebp-1Ch]
  float *v39; // [esp+14h] [ebp-8h]
  float v40; // [esp+14h] [ebp-8h]
  float v41; // [esp+18h] [ebp-4h]
  float v42; // [esp+18h] [ebp-4h]
  float v43; // [esp+20h] [ebp+4h]
  float v44; // [esp+20h] [ebp+4h]
  float v45; // [esp+20h] [ebp+4h]

  v4 = 0;
  v39 = this;
  v5 = *(_DWORD *)(a2 + 56);
  if ( *this == 0.0 )
    goto LABEL_18;
  v7 = *(float *)(a2 + 172);
  if ( v8 )
    v7 = -v7;
  v10 = *(float *)(a2 + 184);
  if ( v11 )
    v10 = -v10;
  if ( v7 >= v10 )
  {
    v13 = *(float *)(a2 + 172);
    if ( v16 )
LABEL_10:
      v13 = -v13;
  }
  else
  {
    v13 = *(float *)(a2 + 184);
    if ( v14 )
      goto LABEL_10;
  }
  v17 = *(_DWORD *)(a2 + 44);
  v18 = 0;
  v43 = v13;
  if ( v17 > 0 )
  {
    v19 = 0;
    v20 = v5 + 8;
    do
    {
      *(_DWORD *)(*(_DWORD *)(a2 + 60) + v19) = *(_DWORD *)(v20 - 8);
      v22 = *(float *)(v19 + *(_DWORD *)(a2 + 56) + 8);
      if ( v23 )
        v22 = -v22;
      v34 = v22 * 1.5707964 / v43 + 4.712389;
      ++v18;
      v19 += 12;
      v20 += 12;
      *(float *)(*(_DWORD *)(a2 + 60) + v19 - 8) = (sine(v34) + 1.0) * *v39 + *(float *)(v20 - 16);
      *(_DWORD *)(*(_DWORD *)(a2 + 60) + v19 - 4) = *(_DWORD *)(v20 - 12);
    }
    while ( v18 < *(_DWORD *)(a2 + 44) );
    this = v39;
  }
  v5 = *(_DWORD *)(a2 + 60);
  v4 = 1;
LABEL_18:
  if ( *(this + 1) != 0.0 )
  {
    v35 = *(this + 1) * 1.5707964;
    v40 = sine(v35) + 1.0;
    v36 = *(this + 1) * 1.5707964;
    v24 = sine(v36);
    v25 = 0;
    v41 = 1.0 - v24;
    v44 = *(float *)(a2 + 168);
    if ( *(int *)(a2 + 44) > 0 )
    {
      v26 = 0;
      v27 = v5 + 8;
      do
      {
        v28 = v40 * *(float *)(v27 - 8);
        ++v25;
        v26 += 12;
        v27 += 12;
        *(float *)(*(_DWORD *)(a2 + 60) + v26 - 12) = v28;
        *(float *)(*(_DWORD *)(a2 + 60) + v26 - 8) = (*(float *)(v27 - 16) - v44) * v41 + v44;
        *(_DWORD *)(*(_DWORD *)(a2 + 60) + v26 - 4) = *(_DWORD *)(v27 - 12);
      }
      while ( v25 < *(_DWORD *)(a2 + 44) );
    }
    v5 = *(_DWORD *)(a2 + 60);
    v4 = 1;
  }
  if ( *(this + 2) == 0.0 )
  {
    if ( !v4 )
      return;
  }
  else
  {
    v37 = *(this + 2) * 1.5707964;
    v45 = sine(v37) * 0.1 + 1.0;
    v38 = *(this + 2) * 1.5707964;
    v29 = sine(v38);
    v30 = 0;
    v42 = 1.0 - v29;
    if ( *(int *)(a2 + 44) > 0 )
    {
      v31 = 0;
      v32 = v5 + 8;
      do
      {
        v33 = v45 * *(float *)(v32 - 8);
        ++v30;
        v31 += 12;
        v32 += 12;
        *(float *)(*(_DWORD *)(a2 + 60) + v31 - 12) = v33;
        *(float *)(*(_DWORD *)(a2 + 60) + v31 - 8) = v45 * *(float *)(v32 - 16);
        *(float *)(*(_DWORD *)(a2 + 60) + v31 - 4) = v42 * *(float *)(v32 - 12);
      }
      while ( v30 < *(_DWORD *)(a2 + 44) );
    }
  }
  *(_DWORD *)(a2 + 56) = *(_DWORD *)(a2 + 60);
  calc_object_facequad_normals_simple((int *)a2);
}

