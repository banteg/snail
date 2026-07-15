/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_survival_high_score @ 0x417780 */
/* selector: add_survival_high_score */

// Void `SubHighScore` member that attempts to insert one completed challenge or survival run into the ordered top-10 bank, mirrors the pending entry into the challenge bank overlay, and arms the high-score entry screen when the run places. Its sole `complete_subgame` caller consumes no result; the no-place rank and inserted-path root pointer left in EAX are unrelated residues. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddSurvival()`.
void __thiscall add_survival_high_score(SubHighScore *bank, SubSolution *record)
{
  int32_t v3; // eax
  int32_t *i; // ecx
  int v5; // ebx
  SubSolution *v6; // ebp
  SubSolution *v7; // edi
  SubSolution **v8; // ebx

  v3 = 0;
  record->high_score_mode_tag = 1;
  record->route_or_rank_index = 0;
  record->replay_cursor = 0;
  qmemcpy(&bank->current_result_record, record, sizeof(bank->current_result_record));
  qmemcpy(&bank->survival_pending_record, record, sizeof(bank->survival_pending_record));
  for ( i = &bank->survival_records[0].score; record->score <= *i; i += 32432 )
  {
    if ( ++v3 >= 10 )
      return;
  }
  v5 = 10;
  v6 = &bank->survival_records[10];
  do
  {
    v7 = v6--;
    qmemcpy(v7, v6, sizeof(SubSolution));
    v6[1].route_or_rank_index = v5--;
  }
  while ( v5 > v3 );
  v8 = &bank->active_record_bank + 32432 * v3;
  qmemcpy(v8 + 356754, record, 0x1FAC0u);
  v8[356769] = (SubSolution *)1;
  v8[356770] = (SubSolution *)v3;
  g_game_base->players[0].frontend_state = 20;
  g_game_base->players[0].high_score_entry_pending = 1;
  if ( v3 != -1 )
  {
    record->high_score_mode_tag = 1;
    v8[356769] = (SubSolution *)1;
    *(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] = bank->survival_records;
    g_game_base->players[0].selected_high_score_rank = v3;
    g_game_base->players[0].selected_high_score_mode = 1;
  }
}
