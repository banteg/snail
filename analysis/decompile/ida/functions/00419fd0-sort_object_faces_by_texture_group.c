/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sort_object_faces_by_texture_group @ 0x419fd0 */
/* selector: sort_object_faces_by_texture_group */

// Sorts one built object's 0x30-byte face records by the texture-group key at `face + 0xc` so `calc_object_texture_groups` can collapse contiguous runs.
int __cdecl sub_419FD0(int a1)
{
  int v1; // esi
  int v2; // ebp
  int result; // eax
  int v4; // ecx
  int v5; // ebx
  char *v6; // edx
  char *v7; // eax
  char *v8; // edi
  int v9; // [esp+8h] [ebp-40h]
  int v10; // [esp+Ch] [ebp-3Ch]
  int v11; // [esp+10h] [ebp-38h]
  int v12; // [esp+14h] [ebp-34h]
  _BYTE v13[48]; // [esp+18h] [ebp-30h] BYREF

  v1 = a1;
  v2 = 0;
  v10 = 0;
  result = *(_DWORD *)(a1 + 84);
  v4 = *(_DWORD *)(a1 + 92);
  v12 = v4;
  if ( result > 0 )
  {
    do
    {
      v5 = v2 + 1;
      v11 = *(_DWORD *)(48 * v2 + v4 + 12);
      if ( v2 + 1 < result )
      {
        v6 = (char *)(v4 + 48 * v5);
        v9 = v2 + 1;
        v7 = v6;
        do
        {
          if ( *((_DWORD *)v6 + 3) == v11 )
          {
            ++v2;
            if ( v5 == v9 )
            {
              v7 += 48;
              ++v9;
            }
            else
            {
              qmemcpy(v13, v7, sizeof(v13));
              v8 = v7;
              v7 += 48;
              qmemcpy(v8, v6, 0x30u);
              qmemcpy(v6, v13, 0x30u);
              ++v9;
              v1 = a1;
              ++v10;
              v4 = v12;
            }
          }
          ++v5;
          v6 += 48;
        }
        while ( v5 < *(_DWORD *)(v1 + 84) );
      }
      result = *(_DWORD *)(v1 + 84);
      ++v2;
    }
    while ( v2 < result );
  }
  return result;
}

