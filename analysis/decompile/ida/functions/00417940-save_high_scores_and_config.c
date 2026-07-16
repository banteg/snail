/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_high_scores_and_config @ 0x417940 */
/* selector: save_high_scores_and_config */

// Void `cRSubHighScore::MiniSave(int)`: serializes the owner’s active postal, survival, and time-trial cRSubSolution entries into ScoreA.dat, ScoreB.dat, and ScoreC.dat according to the save mask, then writes the shared SnailMail.cfg blob. All five Windows callers discard EAX; the final `save_config_file` result is incidental tail residue.
void __thiscall save_high_scores_and_config(SubHighScore *bank, unsigned __int8 save_mask)
{
  char *tracked_memory; // esi
  CompactHighScoreRecord *v4; // eax
  int v5; // ebp
  SubSolution *postal_records; // edi
  CompactHighScoreRecord *v7; // eax
  int v8; // ebp
  SubSolution *survival_records; // edi
  SubSolution *time_trial_route_records; // edi
  CompactHighScoreRecord *v11; // eax
  int v12; // ebp
  int v13; // ebx
  int v14; // [esp+10h] [ebp-4h]
  int v15; // [esp+10h] [ebp-4h]

  tracked_memory = (char *)allocate_tracked_memory((int)&k_high_score_save_buffer_size, aHighScoreTable);
  if ( (save_mask & 1) != 0 )
  {
    v4 = (CompactHighScoreRecord *)tracked_memory;
    v5 = 0;
    postal_records = bank->postal_records;
    v14 = 11;
    do
    {
      if ( postal_records->active == 1 )
      {
        v5 += serialize_compact_high_score_record(postal_records, v4);
        v4 = (CompactHighScoreRecord *)&tracked_memory[v5];
      }
      ++postal_records;
      --v14;
    }
    while ( v14 );
    xor_decode_buffer_with_index(tracked_memory, v5);
    write_file_bytes(aScoreaDat, tracked_memory, v5);
  }
  if ( (save_mask & 2) != 0 )
  {
    v7 = (CompactHighScoreRecord *)tracked_memory;
    v8 = 0;
    survival_records = bank->survival_records;
    v15 = 11;
    do
    {
      if ( survival_records->active == 1 )
      {
        v8 += serialize_compact_high_score_record(survival_records, v7);
        v7 = (CompactHighScoreRecord *)&tracked_memory[v8];
      }
      ++survival_records;
      --v15;
    }
    while ( v15 );
    xor_decode_buffer_with_index(tracked_memory, v8);
    write_file_bytes(aScorebDat, tracked_memory, v8);
  }
  if ( (save_mask & 8) != 0 )
  {
    time_trial_route_records = bank->time_trial_route_records;
    v11 = (CompactHighScoreRecord *)tracked_memory;
    v12 = 0;
    v13 = 51;
    do
    {
      if ( time_trial_route_records->active == 1 )
      {
        v12 += serialize_compact_high_score_record(time_trial_route_records, v11);
        v11 = (CompactHighScoreRecord *)&tracked_memory[v12];
      }
      ++time_trial_route_records;
      --v13;
    }
    while ( v13 );
    xor_decode_buffer_with_index(tracked_memory, v12);
    write_file_bytes(aScorecDat, tracked_memory, v12);
  }
  free_tracked_memory(tracked_memory);
  save_config_file(aSnailmailCfg, &g_runtime_config, 196);
}
