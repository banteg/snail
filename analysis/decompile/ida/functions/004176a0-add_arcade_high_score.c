/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_arcade_high_score @ 0x4176a0 */
/* selector: add_arcade_high_score */

// Void `SubHighScore` member that attempts to insert one completed postal or arcade run into the ordered top-10 bank, then arms the high-score entry screen when the run places. Its sole `complete_subgame` caller consumes no result; the no-place rank and inserted-path root pointer left in EAX are unrelated residues. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddArcade(int)`.
void __thiscall add_arcade_high_score(SubHighScore *bank, SubSolution *record, int level_arg)
{
  int32_t v4; // eax
  int32_t *i; // ecx
  int v6; // ebx
  SubSolution *v7; // edx
  SubSolution *v8; // edi
  char *v9; // edx

  v4 = 0;
  record->route_or_rank_index = level_arg;
  record->high_score_mode_tag = 0;
  qmemcpy(&bank->current_result_record, record, sizeof(bank->current_result_record));
  for ( i = &bank->postal_records[0].score; record->score <= *i; i += 32432 )
  {
    if ( ++v4 >= 10 )
      return;
  }
  v6 = 10;
  v7 = &bank->postal_records[10];
  do
  {
    v8 = v7--;
    qmemcpy(v8, v7, sizeof(SubSolution));
    v7[1].route_or_rank_index = v6--;
  }
  while ( v6 > v4 );
  v9 = (char *)bank + 129728 * v4;
  qmemcpy(v9 + 8, record, 0x1FAC0u);
  *((_DWORD *)v9 + 18) = v4;
  g_game_base->players[0].frontend_state = 20;
  g_game_base->players[0].high_score_entry_pending = 1;
  g_game_base->players[0].selected_high_score_rank = v4;
  g_game_base->players[0].selected_high_score_mode = 0;
}
