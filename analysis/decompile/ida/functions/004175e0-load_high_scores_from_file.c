/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_high_scores_from_file @ 0x4175e0 */
/* selector: load_high_scores_from_file */

// Loads one encoded ScoreA/B/C high-score overlay into the embedded cRSubHighScore owner, decodes compact cRSubSolutionHeader records, and dispatches each expanded solution into the postal, survival, or per-route time-trial array. The function is side-effect-only; known callers ignore the incidental register return.
void __thiscall load_high_scores_from_file(SubHighScore *bank, char *file_name)
{
  char *v2; // esi
  struct CompactHighScoreRecord *compact; // esi
  struct CompactHighScoreRecord *v5; // ebx
  int32_t bank_selector; // eax
  int v7; // eax

  v2 = file_name;
  if ( archive_or_file_exists(file_name, 1u) )
  {
    compact = (struct CompactHighScoreRecord *)load_file_bytes(v2, (int *)&file_name);
    v5 = (struct CompactHighScoreRecord *)((char *)compact + (_DWORD)file_name);
    xor_decode_buffer_with_index((char *)compact, (int)file_name);
    for ( ; compact < v5; compact = (struct CompactHighScoreRecord *)((char *)compact + compact->byte_count) )
    {
      bank_selector = compact->bank_selector;
      if ( bank_selector )
      {
        v7 = bank_selector - 1;
        if ( v7 )
        {
          if ( v7 == 1 )
            deserialize_compact_high_score_record(&bank->time_trial_route_records[compact->entry_index], compact);
        }
        else
        {
          deserialize_compact_high_score_record(&bank->survival_records[compact->entry_index], compact);
        }
      }
      else
      {
        deserialize_compact_high_score_record(&bank->postal_records[compact->entry_index], compact);
      }
    }
  }
}
