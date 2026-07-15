/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_high_scores_and_config @ 0x417940 */
/* selector: save_high_scores_and_config */

// Void `cRSubHighScore::MiniSave(int)`: serializes the owner’s active postal, survival, and time-trial cRSubSolution entries into ScoreA.dat, ScoreB.dat, and ScoreC.dat according to the save mask, then writes the shared SnailMail.cfg blob. All five Windows callers discard EAX; the final `save_config_file` result is incidental tail residue.
void __thiscall save_high_scores_and_config(SubHighScore *bank, unsigned __int8 save_mask)
{
  CompletionResultScreen *tracked_memory; // esi
  int v4; // eax
  FrontendWidget *v5; // ebp
  char *postal_records; // edi
  int v7; // eax
  FrontendWidget *v8; // ebp
  char *survival_records; // edi
  char *time_trial_route_records; // edi
  int v11; // eax
  FrontendWidget *v12; // ebp
  int v13; // ebx
  int v14; // [esp+10h] [ebp-4h]
  int v15; // [esp+10h] [ebp-4h]

  tracked_memory = (CompletionResultScreen *)allocate_tracked_memory(
                                               (int)&k_high_score_save_buffer_size,
                                               (int)aHighScoreTable);
  if ( (save_mask & 1) != 0 )
  {
    v4 = (int)tracked_memory;
    v5 = nullptr;
    postal_records = (char *)bank->postal_records;
    v14 = 11;
    do
    {
      if ( *(_DWORD *)postal_records == 1 )
      {
        v5 = (FrontendWidget *)((char *)v5 + serialize_compact_high_score_record(postal_records, v4));
        v4 = (int)v5 + (_DWORD)tracked_memory;
      }
      postal_records += 129728;
      --v14;
    }
    while ( v14 );
    xor_decode_buffer_with_index(tracked_memory, (int)v5);
    write_file_bytes(aScoreaDat, tracked_memory, v5);
  }
  if ( (save_mask & 2) != 0 )
  {
    v7 = (int)tracked_memory;
    v8 = nullptr;
    survival_records = (char *)bank->survival_records;
    v15 = 11;
    do
    {
      if ( *(_DWORD *)survival_records == 1 )
      {
        v8 = (FrontendWidget *)((char *)v8 + serialize_compact_high_score_record(survival_records, v7));
        v7 = (int)v8 + (_DWORD)tracked_memory;
      }
      survival_records += 129728;
      --v15;
    }
    while ( v15 );
    xor_decode_buffer_with_index(tracked_memory, (int)v8);
    write_file_bytes(aScorebDat, tracked_memory, v8);
  }
  if ( (save_mask & 8) != 0 )
  {
    time_trial_route_records = (char *)bank->time_trial_route_records;
    v11 = (int)tracked_memory;
    v12 = nullptr;
    v13 = 51;
    do
    {
      if ( *(_DWORD *)time_trial_route_records == 1 )
      {
        v12 = (FrontendWidget *)((char *)v12 + serialize_compact_high_score_record(time_trial_route_records, v11));
        v11 = (int)v12 + (_DWORD)tracked_memory;
      }
      time_trial_route_records += 129728;
      --v13;
    }
    while ( v13 );
    xor_decode_buffer_with_index(tracked_memory, (int)v12);
    write_file_bytes(aScorecDat, tracked_memory, v12);
  }
  free_tracked_memory((int)tracked_memory);
  save_config_file(aSnailmailCfg, (CompletionResultScreen *)&g_runtime_config, (FrontendWidget *)0xC4);
}
