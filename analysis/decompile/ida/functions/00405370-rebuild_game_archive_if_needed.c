/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rebuild_game_archive_if_needed @ 0x405370 */
/* selector: rebuild_game_archive_if_needed */

void rebuild_game_archive_if_needed()
{
  _DWORD *v0; // ebx
  int v1; // ebp
  char *v2; // ebp
  bool v3; // cc
  unsigned int *v4; // ebx
  char *v5; // esi
  const char *v6; // edi
  int v7; // ebp
  __int16 v8; // ax
  int v9; // edx
  int v10; // esi
  int v11; // eax
  int v12; // edi
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // [esp+0h] [ebp-234h] BYREF
  int v17; // [esp+4h] [ebp-230h] BYREF
  _DWORD *v18; // [esp+8h] [ebp-22Ch]
  char *v19; // [esp+Ch] [ebp-228h]
  int v20; // [esp+10h] [ebp-224h] BYREF
  unsigned int *v21; // [esp+14h] [ebp-220h]
  int v22; // [esp+18h] [ebp-21Ch] BYREF
  int v23; // [esp+1Ch] [ebp-218h]
  int v24; // [esp+20h] [ebp-214h]
  signed int v25; // [esp+24h] [ebp-210h]
  int v26; // [esp+28h] [ebp-20Ch] BYREF
  char *v27; // [esp+2Ch] [ebp-208h]
  int v28; // [esp+30h] [ebp-204h] BYREF
  char v29[512]; // [esp+34h] [ebp-200h] BYREF

  if ( !file_exists(FileName) && file_exists(aSnailmailDam) )
  {
    v0 = (_DWORD *)malloc(40000000);
    v19 = (char *)v0;
    v21 = (unsigned int *)load_file_bytes_allocating(aSnailmailDam, (#83 *)&v26);
    toggle_archive_high_bit_in_place(v21, v26);
    qmemcpy(v0, v21, v21[2]);
    v1 = v0[2];
    v17 = 0;
    v2 = (char *)v0 + v1;
    v3 = (int)*v21 <= 0;
    v25 = 0;
    if ( !v3 )
    {
      v18 = v0 + 2;
      v4 = v21 + 3;
      v24 = v19 - (char *)v21;
      do
      {
        v5 = v19;
        v27 = &v19[*(v4 - 2)];
        v6 = v27;
        if ( classify_archive_entry_extension(v27, v29) == 1 )
        {
          save_file_bytes_with_optional_archive_scramble(a0Png, (char *)v21 + *(v4 - 1), *v4, 0);
          sub_42F0A0(a0Png, &v17, &v20, &v22, &v16, &v28, 0);
          *v18 = v2 - v5;
          v2[7] = 0;
          v2[6] = 0;
          v2[5] = 0;
          v2[4] = 0;
          v2[3] = 0;
          v2[1] = 0;
          *v2 = 0;
          v8 = v22;
          v2[17] = 8;
          *((_WORD *)v2 + 7) = v8;
          v2[2] = 2;
          v2[16] = 8 * v16;
          *((_WORD *)v2 + 6) = v20;
          *((_WORD *)v2 + 4) = 0;
          *((_WORD *)v2 + 5) = 0;
          v9 = v20;
          v10 = v16;
          v23 = 0;
          v11 = v22;
          if ( v20 > 0 )
          {
            do
            {
              v12 = 0;
              if ( v11 > 0 )
              {
                do
                {
                  v13 = v10 * (v23 + v9 * v12);
                  v14 = v10 * (v23 + v9 * (v11 - v12 - 1));
                  v2[v14 + 20] = *(_BYTE *)(v13 + v17);
                  v2[v14 + 19] = *(_BYTE *)(v13 + v17 + 1);
                  v2[v14 + 18] = *(_BYTE *)(v13 + v17 + 2);
                  v10 = v16;
                  if ( v16 == 4 )
                  {
                    v2[v14 + 21] = *(_BYTE *)(v13 + v17 + 3);
                    v10 = v16;
                  }
                  v11 = v22;
                  v9 = v20;
                  ++v12;
                }
                while ( v12 < v22 );
              }
              ++v23;
            }
            while ( v23 < v9 );
            v6 = v27;
          }
          v15 = v10 * v11 * v9 + 20;
          *(unsigned int *)((char *)v4 + v24) = v15;
          v2 += (int)&v2[v15] % 4 + v15;
          printf("extracting %s\n", v6);
        }
        else
        {
          qmemcpy(v2, (char *)v21 + *(v4 - 1), *v4);
          *v18 = v2 - v19;
          v7 = (int)&v2[*v4];
          *(unsigned int *)((char *)v4 + v24) = *v4;
          v2 = (char *)(v7 % 4 + v7);
        }
        v18 += 3;
        v4 += 3;
        ++v25;
      }
      while ( v25 < (int)*v21 );
      v0 = v19;
    }
    save_file_bytes_with_optional_archive_scramble(FileName, v0, v2 - (char *)v0, 1);
    delete_file_path(aSnailmailDam);
    delete_file_path(a0Png);
    free(v0);
  }
}

