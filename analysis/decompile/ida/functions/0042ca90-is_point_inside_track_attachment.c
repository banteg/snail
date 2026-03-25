/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_point_inside_track_attachment @ 0x42ca90 */
/* selector: is_point_inside_track_attachment */

char __thiscall sub_42CA90(_DWORD *this, float a2, float a3, float a4, int a5, int a6, int a7, float *a8)
{
  int v9; // edi
  int i; // esi
  int v11; // ecx
  double v12; // st7
  float v14; // [esp+Ch] [ebp-30h] BYREF
  float v15; // [esp+10h] [ebp-2Ch]
  float v16; // [esp+14h] [ebp-28h]
  float v17; // [esp+18h] [ebp-24h]
  float v18; // [esp+1Ch] [ebp-20h]
  float v19; // [esp+20h] [ebp-1Ch]
  float v20; // [esp+24h] [ebp-18h]
  float v21; // [esp+28h] [ebp-14h]
  float v22; // [esp+2Ch] [ebp-10h]
  float v23; // [esp+34h] [ebp-8h]
  float v24; // [esp+38h] [ebp-4h]

  v9 = *(this + 17) - 1;
  v17 = a8[4];
  v18 = a8[5];
  v19 = a8[6];
  if ( v9 < 0 )
    return 0;
  for ( i = 168 * v9; ; i -= 168 )
  {
    v11 = *(this + 23);
    v12 = v17 + *(float *)(i + v11 + 48);
    v23 = v18 + *(float *)(i + v11 + 52);
    v24 = v19 + *(float *)(i + v11 + 56);
    v20 = a2 - v12;
    v14 = v20;
    v21 = a3 - v23;
    v15 = v21;
    v22 = a4 - v24;
    v16 = v22;
    rotate_vector_by_matrix(&v14, (float *)(i + v11 + 64));
    if ( (double)(*(this + 21) / -2) - 0.30000001 < v14
      && (double)(*(this + 21) / 2) + 0.30000001 > v14
      && v15 >= -0.30000001
      && v15 < 0.30000001
      && v16 > 0.0
      && v16 < (double)*(float *)(i + *(this + 23) + 140) )
    {
      break;
    }
    if ( --v9 < 0 )
      return 0;
  }
  return 1;
}

