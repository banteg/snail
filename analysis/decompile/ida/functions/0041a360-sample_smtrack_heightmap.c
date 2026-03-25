/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sample_smtrack_heightmap @ 0x41a360 */
/* selector: sample_smtrack_heightmap */

// Samples one source texture into the active SMTrack float-height grid by averaging the source RGB channels, applying the optional cubic curve, and scaling the result into the destination height lane.
void __cdecl sub_41A360(int a1, float a2, float a3, int a4, char a5)
{
  int v6; // esi
  double v7; // st7
  int v8; // ebp
  double i; // st7
  double j; // st6
  unsigned __int8 *v11; // eax
  double v12; // st5
  float v13; // [esp+Ch] [ebp-8h]
  float v14; // [esp+10h] [ebp-4h]
  float v15; // [esp+18h] [ebp+4h]
  int v16; // [esp+24h] [ebp+10h]

  v6 = *(_DWORD *)(a4 + 152);
  v7 = (double)*(int *)(a1 + 28);
  *(float *)&v16 = v7;
  v15 = (float)(int)(__int64)(v7 * *(float *)(a1 + 40) / *(float *)(a1 + 36));
  v8 = *(_DWORD *)(a1 + 56);
  v14 = (double)*(unsigned __int16 *)(v6 + 12) / (*(float *)&v16 + 1.0);
  v13 = (double)*(unsigned __int16 *)(v6 + 14) / (v15 + 1.0);
  for ( i = 0.0; i <= v15; i = i + 1.0 )
  {
    for ( j = 0.0; j <= *(float *)&v16; j = j + 1.0 )
    {
      v11 = (unsigned __int8 *)((*(unsigned __int8 *)(v6 + 16) >> 3)
                              * ((__int64)(j * v14)
                               + *(unsigned __int16 *)(v6 + 12)
                               * (*(unsigned __int16 *)(v6 + 14) - (unsigned int)(__int64)(i * v13) - 1))
                              + v6);
      v12 = ((double)v11[20] + (double)v11[19] + (double)v11[18]) * 0.0039215689 * 0.33333334;
      if ( a5 )
        v12 = v12 * (v12 * v12);
      v8 += 12;
      *(float *)(v8 - 8) = v12 * a3 + a2;
    }
  }
}

