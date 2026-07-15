/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_high_scores_from_file @ 0x4175e0 */
/* selector: load_high_scores_from_file */

// Loads one encoded ScoreA/B/C high-score overlay into the embedded cRSubHighScore owner, decodes compact cRSubSolutionHeader records, and dispatches each expanded solution into the postal, survival, or per-route time-trial array. The function is side-effect-only; known callers ignore the incidental register return.
void __thiscall load_high_scores_from_file(SubHighScore *bank, char *file_name)
{
  char *v2; // esi
  unsigned int file_bytes; // esi
  char *v5; // ebx
  int v6; // eax
  int v7; // eax

  v2 = file_name;
  if ( archive_or_file_exists(file_name, 1) )
  {
    file_bytes = (unsigned int)load_file_bytes(v2, (CompletionResultScreen *)&file_name);
    v5 = &file_name[file_bytes];
    xor_decode_buffer_with_index((_BYTE *)file_bytes, (int)file_name);
    for ( ; file_bytes < (unsigned int)v5; file_bytes += *(_DWORD *)file_bytes )
    {
      v6 = *(_DWORD *)(file_bytes + 60);
      if ( v6 )
      {
        v7 = v6 - 1;
        if ( v7 )
        {
          if ( v7 == 1 )
            deserialize_compact_high_score_record(
              (char *)&bank->time_trial_route_records[*(_DWORD *)(file_bytes + 64)],
              file_bytes);
        }
        else
        {
          deserialize_compact_high_score_record(
            (char *)&bank->survival_records[*(_DWORD *)(file_bytes + 64)],
            file_bytes);
        }
      }
      else
      {
        deserialize_compact_high_score_record((char *)&bank->postal_records[*(_DWORD *)(file_bytes + 64)], file_bytes);
      }
    }
  }
}
