/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_snail_hotspots @ 0x445d50 */
/* selector: build_snail_hotspots */

int __thiscall sub_445D50(int this)
{
  _DWORD *v1; // ebp
  const char **v2; // ebx
  float *v3; // esi
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD *v7; // edi
  int v8; // eax
  int v9; // ecx
  double v10; // st7
  int v11; // eax
  int v12; // ecx
  float v13; // edx

  v1 = *(_DWORD **)(this + 5744);
  v2 = (const char **)off_4A4AA0;
  v3 = (float *)(this + 5844);
  do
  {
    *v3 = 0.0;
    *(v3 - 1) = 0.0;
    *(v3 - 2) = 0.0;
    v4 = get_or_create_texture_ref(&dword_4B7790, *v2, 0, 0);
    v5 = v1[21];
    v6 = 0;
    if ( v5 <= 0 )
    {
LABEL_6:
      sub_431CC0("Cannot find HotPoint Texture %s", *v2);
    }
    else
    {
      v7 = (_DWORD *)(v1[23] + 12);
      while ( *v7 != v4 )
      {
        ++v6;
        v7 += 12;
        if ( v6 >= v5 )
          goto LABEL_6;
      }
      v8 = *(unsigned __int16 *)(48 * v6 + v1[23] + 2);
      v9 = v1[14];
      v8 *= 3;
      v10 = *(v3 - 2) + *(float *)(v9 + 4 * v8);
      v11 = v9 + 4 * v8;
      *(v3 - 2) = v10;
      *(v3 - 1) = *(float *)(v11 + 4) + *(v3 - 1);
      *v3 = *(float *)(v11 + 8) + *v3;
      v12 = *((_DWORD *)v3 - 1);
      v13 = *v3;
      *(v3 - 2) = *(v3 - 2);
      *((_DWORD *)v3 - 1) = v12;
      *v3 = v13;
    }
    ++v2;
    v3 += 3;
  }
  while ( (int)v2 < (int)aXCameraintrota );
  *(float *)(this + 6056) = *(float *)(this + 6056) + 0.30000001;
  return this;
}
