/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: project_position_onto_track_attachment @ 0x4444b0 */
/* selector: project_position_onto_track_attachment */

// Projects a world-space position onto an active track attachment template.
char *__thiscall sub_4444B0(void *this, float *a2, float *a3)
{
  char *result; // eax
  int v4; // edi
  int v5; // ebx
  float *v6; // eax
  int v7; // edx
  double v8; // st7
  double v9; // st7
  double v10; // st6
  double v11; // st6
  float v12; // [esp+Ch] [ebp-70h]
  float v13; // [esp+Ch] [ebp-70h]
  float v14; // [esp+10h] [ebp-6Ch]
  float v15; // [esp+10h] [ebp-6Ch]
  float v16; // [esp+14h] [ebp-68h]
  float v17; // [esp+1Ch] [ebp-60h]
  float v18; // [esp+20h] [ebp-5Ch]
  float v19; // [esp+24h] [ebp-58h]
  float v20; // [esp+28h] [ebp-54h]
  float v21; // [esp+30h] [ebp-4Ch]
  float v22; // [esp+34h] [ebp-48h]
  int v23[16]; // [esp+3Ch] [ebp-40h] BYREF

  result = (char *)byte_5CCAC8 + (_DWORD)this + 244 * (__int64)a2[2];
  *a3 = 0.0;
  if ( (*result & 0x40) != 0 )
  {
    v4 = *((_DWORD *)result + 41);
    v5 = *(_DWORD *)(v4 + 56);
    v6 = (float *)(*(_DWORD *)(v5 + 88) + 168 * ((__int64)a2[2] - get_track_cell_row_index((_DWORD *)v4)));
    if ( *(_DWORD *)(v5 + 56) == 42 )
    {
      compute_kind42_attachment_transform(v6[40], *a2, a2[1], (int)v23, a3);
      v7 = v23[13];
      *a2 = *(float *)&v23[12];
      *((_DWORD *)a2 + 1) = v7;
    }
    else
    {
      v8 = a2[1];
      v21 = v8 * v6[4];
      v22 = v8 * v6[5];
      v9 = v8 * v6[6];
      v10 = *a2 - v6[36];
      v12 = v10 * *v6;
      v14 = v10 * v6[1];
      v17 = v6[13] + *(float *)(v4 + 20);
      v18 = v6[14] + *(float *)(v4 + 24);
      v19 = v6[12] + *(float *)(v4 + 16) + v12;
      v20 = v17 + v14;
      v11 = v10 * v6[2] + v18;
      v13 = v19 + v21;
      *a2 = v13;
      v15 = v20 + v22;
      a2[1] = v15;
      v16 = v11 + v9;
      a2[2] = v16;
      return (char *)LODWORD(v13);
    }
  }
  return result;
}

