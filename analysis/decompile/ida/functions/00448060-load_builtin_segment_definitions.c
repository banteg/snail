/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_builtin_segment_definitions @ 0x448060 */
/* selector: load_builtin_segment_definitions */

// Copies the shipped built-in segment definitions from the static table at `0x4a63d0` into the secondary SubTracks owner, including names like `Start`, `Finish`, and `Filler` plus their eight authored row strings and metadata lanes. Symbol-preserving iOS builds name the corresponding overload `cRSubTracks::Init(cRSubSegmentRaw**)`.
_BYTE *__thiscall load_builtin_segment_definitions(int *this, int a2)
{
  _BYTE *result; // eax
  _BYTE *v4; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  char v9; // dl
  int v10; // ebp
  int v11; // esi
  int v12; // [esp+8h] [ebp+4h]

  *this = 0;
  *(this + 431665) = 1000;
  result = *(_BYTE **)a2;
  if ( **(_BYTE **)(*(_DWORD *)a2 + 40) )
  {
    do
    {
      v4 = *(_BYTE **)(*(_DWORD *)(a2 + 4 * *this) + 40);
      v5 = 0;
      if ( *v4 )
      {
        do
          ++v5;
        while ( v4[v5] );
      }
      v12 = 0;
      v6 = 40;
      *(this + 4232 * *this + 2) = v5;
      **(_DWORD **)(a2 + 4 * *this) = v5;
      do
      {
        v7 = *this;
        v8 = 0;
        v9 = **(_BYTE **)(*(_DWORD *)(a2 + 4 * *this) + v6);
        do
        {
          v10 = v8 + v12 + 16928 * v7;
          ++v8;
          *((_BYTE *)this + v10 + 24) = v9;
          v7 = *this;
          v9 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(a2 + 4 * *this) + v6) + v8);
        }
        while ( v9 );
        v6 += 4;
        v12 += 256;
      }
      while ( v6 < 72 );
      *(this + 4232 * v7 + 5) = *(_DWORD *)(*(_DWORD *)(a2 + 4 * v7) + 32);
      *(this + 4232 * *this + 4) = *(_DWORD *)(*(_DWORD *)(a2 + 4 * *this) + 28);
      v11 = *this + 1;
      *this = v11;
      result = *(_BYTE **)(*(_DWORD *)(a2 + 4 * v11) + 40);
    }
    while ( *result );
  }
  return result;
}
