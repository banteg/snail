/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: replace_object_list_texture_refs @ 0x430d90 */
/* selector: replace_object_list_texture_refs */

// Walks the global object list and replaces one texture reference with another across face quads and any already-built grouped-render texture tables.
int __thiscall sub_430D90(int *this, int a2, int a3)
{
  int result; // eax
  _DWORD *v5; // eax
  int v6; // esi
  int v7; // edx
  int v8; // ecx
  bool v9; // zf
  int *v10; // ecx
  bool v11; // cc
  int v12; // [esp+4h] [ebp-8h]
  int v13; // [esp+8h] [ebp-4h]

  result = 0;
  v12 = 0;
  if ( *this > 0 )
  {
    v13 = 0;
    do
    {
      v5 = (_DWORD *)(*(this + 2) + result);
      if ( v5[11] )
      {
        v6 = 0;
        if ( (int)v5[21] > 0 )
        {
          v7 = 0;
          do
          {
            v8 = v5[23];
            v9 = *(_DWORD *)(v7 + v8 + 12) == a3;
            v10 = (int *)(v7 + v8 + 12);
            if ( v9 )
              *v10 = a2;
            ++v6;
            v7 += 48;
          }
          while ( v6 < v5[21] );
        }
        replace_object_group_texture_refs(v5, a2, a3);
      }
      result = v13 + 220;
      v11 = ++v12 < *this;
      v13 += 220;
    }
    while ( v11 );
  }
  return result;
}

