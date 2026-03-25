/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_high_scores_from_file @ 0x4175e0 */
/* selector: load_high_scores_from_file */

char __thiscall sub_4175E0(char *this, char *FileName)
{
  char *v2; // esi
  int v4; // eax
  unsigned int v5; // esi
  char *v6; // ebx
  int v7; // eax
  int v8; // eax

  v2 = FileName;
  LOBYTE(v4) = archive_or_file_exists(FileName, 1);
  if ( (_BYTE)v4 )
  {
    v5 = (unsigned int)load_file_bytes(v2, (#83 *)&FileName);
    v6 = &FileName[v5];
    for ( LOBYTE(v4) = (unsigned __int8)xor_decode_buffer_with_index((_BYTE *)v5, (int)FileName);
          v5 < (unsigned int)v6;
          v5 += *(_DWORD *)v5 )
    {
      v7 = *(_DWORD *)(v5 + 60);
      if ( v7 )
      {
        v8 = v7 - 1;
        if ( v8 )
        {
          v4 = v8 - 1;
          if ( !v4 )
            LOBYTE(v4) = deserialize_compact_high_score_record(this + 129728 * *(_DWORD *)(v5 + 64) + 2854024, v5);
        }
        else
        {
          LOBYTE(v4) = deserialize_compact_high_score_record(this + 129728 * *(_DWORD *)(v5 + 64) + 1427016, v5);
        }
      }
      else
      {
        LOBYTE(v4) = deserialize_compact_high_score_record(this + 129728 * *(_DWORD *)(v5 + 64) + 8, v5);
      }
    }
  }
  return v4;
}

