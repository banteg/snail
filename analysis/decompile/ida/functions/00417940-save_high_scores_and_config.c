/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_high_scores_and_config @ 0x417940 */
/* selector: save_high_scores_and_config */

char *__thiscall save_high_scores_and_config(char *this, char a2)
{
  _BYTE *v3; // esi
  int v4; // eax
  int v5; // ebp
  char *v6; // edi
  int v7; // eax
  int v8; // ebp
  char *v9; // edi
  char *v10; // edi
  int v11; // eax
  int v12; // ebp
  int v13; // ebx
  int v15; // [esp+10h] [ebp-4h]
  int v16; // [esp+10h] [ebp-4h]

  v3 = allocate_tracked_memory((int)&unk_4C4B40, (int)aHighScoreTable);
  if ( (a2 & 1) != 0 )
  {
    v4 = (int)v3;
    v5 = 0;
    v6 = this + 8;
    v15 = 11;
    do
    {
      if ( *(_DWORD *)v6 == 1 )
      {
        v5 += serialize_compact_high_score_record(v6, v4);
        v4 = (int)&v3[v5];
      }
      v6 += 129728;
      --v15;
    }
    while ( v15 );
    xor_decode_buffer_with_index(v3, v5);
    write_file_bytes(aScoreaDat, v3, v5);
  }
  if ( (a2 & 2) != 0 )
  {
    v7 = (int)v3;
    v8 = 0;
    v9 = this + 1427016;
    v16 = 11;
    do
    {
      if ( *(_DWORD *)v9 == 1 )
      {
        v8 += serialize_compact_high_score_record(v9, v7);
        v7 = (int)&v3[v8];
      }
      v9 += 129728;
      --v16;
    }
    while ( v16 );
    xor_decode_buffer_with_index(v3, v8);
    write_file_bytes(aScorebDat, v3, v8);
  }
  if ( (a2 & 8) != 0 )
  {
    v10 = this + 2854024;
    v11 = (int)v3;
    v12 = 0;
    v13 = 51;
    do
    {
      if ( *(_DWORD *)v10 == 1 )
      {
        v12 += serialize_compact_high_score_record(v10, v11);
        v11 = (int)&v3[v12];
      }
      v10 += 129728;
      --v13;
    }
    while ( v13 );
    xor_decode_buffer_with_index(v3, v12);
    write_file_bytes(aScorecDat, v3, v12);
  }
  free_tracked_memory((int)v3);
  return (char *)save_config_file(aSnailmailCfg, &unk_4DF918, 196);
}

