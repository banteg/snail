/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: deserialize_compact_high_score_record @ 0x440020 */
/* selector: deserialize_compact_high_score_record */

// Validates one compact ScoreA/B/C cRSubSolutionHeader checksum, copies its scalar fields, name, and replay samples into the expanded cRSubSolution entry, and marks the entry active. Android preserves this owner method as `cRSubSolution::Load(cRSubSolutionHeader*)`.
unsigned __int8 __thiscall deserialize_compact_high_score_record(SubSolution *record, CompactHighScoreRecord *compact)
{
  int32_t replay_sample_count; // edx
  int32_t v5; // eax
  uint8_t *replay_payload; // ecx
  ReplayRunRecord *run_records; // edx
  int32_t v8; // ecx
  int32_t v9; // eax
  uint8_t *v10; // edx
  int16_t *p_delta_z; // ecx
  int32_t v12; // ecx
  int32_t v13; // eax
  uint8_t *v14; // ebp
  uint16_t *p_flags; // ecx

  if ( compact->checksum == ((compact->score * compact->score) ^ 0xDEADBABE) )
  {
    record->replay_sample_count = compact->replay_sample_count;
    record->replay_level_index = compact->replay_level_index;
    record->replay_mode_id = compact->replay_mode_id;
    record->replay_speed_scalar.bits = compact->replay_speed_scalar.bits;
    record->challenge_difficulty_scalar.bits = compact->challenge_difficulty_scalar.bits;
    rstrcpy_checked_ascii(record->player_name, compact->player_name);
    record->score = compact->score;
    qmemcpy(&record->score_or_time, &compact->score_or_time, 0x1Cu);
    record->challenge_speed_value = compact->challenge_speed_value;
    record->challenge_difficulty_value = compact->challenge_difficulty_value;
    record->garbage_frequency.bits = compact->garbage_frequency.bits;
    record->salt_frequency.bits = compact->salt_frequency.bits;
    record->source_tail = compact->source_tail;
    record->runtime_build_seed = compact->runtime_build_seed;
    record->unknown_1fab8 = compact->unknown_80;
    record->unknown_1fabc = compact->unknown_84;
    record->runtime_build_flags = compact->runtime_build_flags;
    record->high_score_mode_tag = compact->bank_selector;
    replay_sample_count = record->replay_sample_count;
    record->route_or_rank_index = compact->entry_index;
    v5 = 0;
    record->replay_cursor = compact->replay_cursor;
    replay_payload = compact->replay_payload;
    if ( replay_sample_count > 0 )
    {
      run_records = record->run_records;
      do
      {
        ++v5;
        run_records->lateral_x = *(_WORD *)replay_payload;
        replay_payload += 2;
        ++run_records;
      }
      while ( v5 < record->replay_sample_count );
    }
    v8 = record->replay_sample_count;
    v9 = 0;
    v10 = &compact->replay_payload[2 * v8];
    if ( v8 > 0 )
    {
      p_delta_z = &record->run_records[0].delta_z;
      do
      {
        ++v9;
        *p_delta_z = *(_WORD *)v10;
        p_delta_z += 3;
        v10 += 2;
      }
      while ( v9 < record->replay_sample_count );
    }
    v12 = record->replay_sample_count;
    v13 = 0;
    v14 = &compact->replay_payload[4 * v12];
    if ( v12 > 0 )
    {
      p_flags = &record->run_records[0].flags;
      do
      {
        *p_flags = v14[v13++];
        p_flags += 3;
      }
      while ( v13 < record->replay_sample_count );
    }
    record->active = 1;
    return 1;
  }
  else
  {
    record->active = 0;
    return 0;
  }
}
