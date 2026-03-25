/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_animation @ 0x430a70 */
/* selector: request_object_animation */

int __thiscall sub_430A70(int *this, int a2, _DWORD *a3, float a4, __int16 a5)
{
  int v5; // eax
  int v8; // edx
  _DWORD *v9; // ecx
  int v10; // ebp
  _BYTE *v11; // eax
  int result; // eax
  int v13; // edi
  int v14; // ecx
  _DWORD *v15; // ebx
  double X; // st7
  int v17; // edx
  int v18; // eax
  int v19; // edx
  _DWORD *v20; // ecx
  _DWORD *v21; // eax
  float *v22; // ecx
  int v23; // eax
  double v24; // st7
  double v25; // st6
  float *v26; // eax
  float *v27; // eax
  int v28; // eax
  float v29; // [esp+18h] [ebp-38h]
  float i; // [esp+18h] [ebp-38h]
  int v31; // [esp+1Ch] [ebp-34h]
  int v32; // [esp+20h] [ebp-30h]
  _DWORD *v33; // [esp+24h] [ebp-2Ch]
  float v34; // [esp+28h] [ebp-28h]
  float v35; // [esp+2Ch] [ebp-24h]
  float v36; // [esp+30h] [ebp-20h]
  float v37; // [esp+34h] [ebp-1Ch]
  float v38; // [esp+3Ch] [ebp-14h]
  float v39; // [esp+40h] [ebp-10h]
  float v40; // [esp+48h] [ebp-8h]
  float v41; // [esp+4Ch] [ebp-4h]
  int v42; // [esp+58h] [ebp+8h]
  int v43; // [esp+5Ch] [ebp+Ch]
  int v44; // [esp+60h] [ebp+10h]

  v5 = 0;
  if ( a2 <= 0 )
  {
LABEL_5:
    *(this + 4) |= 0x200000u;
    v10 = (__int64)(1.0 / a4);
    v31 = v10;
    v11 = allocate_tracked_memory(20, (int)aObjectAnimatio);
    *(this + 47) = (int)v11;
    *((_DWORD *)v11 + 1) = v10;
    *(_WORD *)*(this + 47) = a5;
    *(_DWORD *)(*(this + 47) + 12) = 0;
    *(float *)(*(this + 47) + 16) = a4;
    v42 = 0;
    *(_DWORD *)(*(this + 47) + 8) = allocate_tracked_memory(4 * v10, (int)aObjectAnimatio_0);
    v44 = a3[31];
    if ( a2 == 1 )
      v43 = a3[31];
    else
      v43 = a3[63];
    v13 = 0;
    if ( v10 > 0 )
    {
      v34 = (float)v10;
      v14 = (int)&a3[32 * a2 - 1];
      v15 = a3 + 9;
      v33 = (_DWORD *)v14;
      do
      {
        *(_DWORD *)(*(_DWORD *)(*(this + 47) + 8) + 4 * v13) = allocate_tracked_memory(8, (int)aObjectAnimatio_1);
        **(_DWORD **)(*(_DWORD *)(*(this + 47) + 8) + 4 * v13) = allocate_tracked_memory(
                                                                   12 * *(this + 11),
                                                                   (int)aObjectAnimatio_2);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(this + 47) + 8) + 4 * v13) + 4) = allocate_tracked_memory(
                                                                                  24 * *(this + 21),
                                                                                  (int)aObjectAnimatio_3);
        X = (double)(v13 * *v33) / v34;
        v29 = X;
        if ( (int)(__int64)floor(X) >= v43 && v42 < a2 - 1 )
        {
          v17 = v15[54];
          v18 = v15[86];
          v15 += 32;
          ++v42;
          v44 = v17;
          v43 = v18;
        }
        v19 = 0;
        v32 = 0;
        for ( i = (v29 - (double)v44) / (double)(v43 - v44); v32 < *(this + 11); ++v32 )
        {
          if ( a2 == 1 )
          {
            v20 = (_DWORD *)(v19 + *(_DWORD *)(*v15 + 56));
            v21 = (_DWORD *)(v19 + **(_DWORD **)(*(_DWORD *)(*(this + 47) + 8) + 4 * v13));
            *v21 = *v20;
            v21[1] = v20[1];
            v10 = v31;
            v21[2] = v20[2];
          }
          else
          {
            v22 = (float *)(v19 + *(_DWORD *)(v15[32] + 56));
            v23 = *(_DWORD *)(*v15 + 56);
            v24 = *v22 - *(float *)(v23 + v19);
            v25 = v22[1] - *(float *)(v23 + v19 + 4);
            v26 = (float *)(v19 + v23);
            v38 = v25;
            v39 = v22[2] - v26[2];
            v40 = v38 * i;
            v41 = v39 * i;
            v35 = v24 * i + *v26;
            v36 = v40 + v26[1];
            v37 = v41 + v26[2];
            v27 = (float *)(v19 + **(_DWORD **)(*(_DWORD *)(*(this + 47) + 8) + 4 * v13));
            *v27 = v35;
            v27[1] = v36;
            v27[2] = v37;
          }
          v19 += 12;
        }
        v28 = *(this + 47);
        *(this + 14) = **(_DWORD **)(*(_DWORD *)(v28 + 8) + 4 * v13);
        *(this + 24) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 4 * v13) + 4);
        calc_object_facequad_normals(this);
        ++v13;
      }
      while ( v13 < v10 );
    }
    result = *(this + 47);
    *(_DWORD *)(result + 12) = 0;
  }
  else
  {
    v8 = *(this + 11);
    v9 = a3 + 9;
    while ( *(_DWORD *)(*v9 + 44) == v8 )
    {
      ++v5;
      v9 += 32;
      if ( v5 >= a2 )
        goto LABEL_5;
    }
    return report_errorf("Anim tween Vertices don't match Frame %i", a3[32 * v5 + 31]);
  }
  return result;
}

