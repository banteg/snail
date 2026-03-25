/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_texture_groups @ 0x4303f0 */
/* selector: calc_object_texture_groups */

_BYTE *__thiscall sub_4303F0(int this)
{
  int i; // ebp
  _BYTE *result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edx
  int v7; // ecx
  _DWORD *v8; // eax

  for ( i = 0; i < 2; ++i )
  {
    result = *(_BYTE **)(this + 92);
    v4 = 0;
    v5 = 0;
    v6 = *((_DWORD *)result + 3);
    if ( *(int *)(this + 84) > 0 )
    {
      v7 = 0;
      do
      {
        if ( (*(_BYTE *)(this + 17) & 4) != 0 )
        {
          result[v7] |= 2u;
          v8 = *(_DWORD **)(*(_DWORD *)(this + 92) + v7 + 12);
          *v8 |= 0x20u;
        }
        result = *(_BYTE **)(this + 92);
        if ( *(_DWORD *)&result[v7 + 12] != v6 || (result[v7] & 0x10) != 0 )
        {
          if ( i == 1 )
            *(_DWORD *)(*(_DWORD *)(this + 108) + 4 * v4) = v5;
          result = *(_BYTE **)(this + 92);
          ++v4;
          v6 = *(_DWORD *)&result[v7 + 12];
        }
        ++v5;
        v7 += 48;
      }
      while ( v5 < *(_DWORD *)(this + 84) );
    }
    if ( i == 1 )
    {
      result = *(_BYTE **)(this + 108);
      *(_DWORD *)&result[4 * v4] = v5;
    }
    else if ( !i )
    {
      result = request_object_texture_groups((_DWORD *)this, v4 + 1);
    }
  }
  return result;
}

