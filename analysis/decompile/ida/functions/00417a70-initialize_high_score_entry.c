/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_entry @ 0x417a70 */
/* selector: initialize_high_score_entry */

// Resets one embedded cRSubSolution replay/high-score entry, seeds its score-mode metadata, copies the current player name, and clears all 21,600 run samples. Cross-port symbols identify this exact owner method as `cRSubSolution::ReSet(int,int,float,int,int,int)`.
void __thiscall initialize_high_score_entry(
        SubSolution *record,
        int runtime_build_seed,
        int replay_level_index,
        int replay_speed_scalar_bits,
        unsigned int runtime_build_flags,
        int high_score_mode_tag,
        int route_or_rank_index)
{
  int16_t *p_delta_z; // eax
  int v9; // ecx

  record->runtime_build_seed = runtime_build_seed;
  record->replay_sample_count = 0;
  record->score = 0;
  zero_timer_counters((Time *)&record->score_or_time);
  record->replay_level_index = replay_level_index;
  LODWORD(record->replay_speed_scalar) = replay_speed_scalar_bits;
  rstrcpy_checked_ascii(record->player_name, g_game_base->players[0].player_name);
  record->high_score_mode_tag = high_score_mode_tag;
  record->route_or_rank_index = route_or_rank_index;
  record->active = 0;
  record->runtime_build_flags = runtime_build_flags;
  record->replay_cursor = 0;
  p_delta_z = &record->run_records[0].delta_z;
  v9 = 21600;
  do
  {
    *(p_delta_z - 1) = 0;
    *p_delta_z = 0;
    p_delta_z[1] = 0;
    p_delta_z += 3;
    --v9;
  }
  while ( v9 );
}
