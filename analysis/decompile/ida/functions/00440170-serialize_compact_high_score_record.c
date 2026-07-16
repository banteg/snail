/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: serialize_compact_high_score_record @ 0x440170 */
/* selector: serialize_compact_high_score_record */

// Compacts one active cRSubSolution into the ScoreA/B/C on-disk record format, including checksum, name, and variable replay payload arrays. Android preserves this owner method as `cRSubSolution::Save(unsigned char*)`.
int __thiscall serialize_compact_high_score_record(SubSolution *record, CompactHighScoreRecord *compact)
{
  int32_t replay_sample_count; // eax
  int32_t v4; // eax
  uint8_t *replay_payload; // edx
  ReplayRunRecord *run_records; // ecx
  int32_t v7; // ecx
  int32_t v8; // eax
  uint8_t *v9; // edx
  int16_t *p_delta_z; // ecx
  int32_t v11; // ecx
  int32_t v12; // eax
  uint8_t *v13; // edi
  uint16_t *p_flags; // esi
  uint8_t v15; // cl
  int result; // eax

  replay_sample_count = record->replay_sample_count;
  record->active = 1;
  compact->replay_sample_count = replay_sample_count;
  compact->replay_level_index = record->replay_level_index;
  compact->replay_mode_id = record->replay_mode_id;
  compact->replay_speed_scalar.bits = record->replay_speed_scalar.bits;
  compact->challenge_difficulty_scalar.bits = record->challenge_difficulty_scalar.bits;
  rstrcpy_checked_ascii(compact->player_name, record->player_name);
  qmemcpy(&compact->score_or_time, &record->score_or_time, 0x1Cu);
  compact->challenge_speed_value = record->challenge_speed_value;
  compact->challenge_difficulty_value = record->challenge_difficulty_value;
  compact->garbage_frequency.bits = record->garbage_frequency.bits;
  compact->salt_frequency.bits = record->salt_frequency.bits;
  compact->source_tail = record->source_tail;
  compact->score = record->score;
  compact->checksum = (record->score * record->score) ^ 0xDEADBABE;
  compact->runtime_build_seed = record->runtime_build_seed;
  compact->unknown_80 = record->unknown_1fab8;
  compact->unknown_84 = record->unknown_1fabc;
  compact->runtime_build_flags = record->runtime_build_flags;
  compact->bank_selector = record->high_score_mode_tag;
  compact->entry_index = record->route_or_rank_index;
  compact->replay_cursor = record->replay_cursor;
  v4 = 0;
  replay_payload = compact->replay_payload;
  if ( record->replay_sample_count > 0 )
  {
    run_records = record->run_records;
    do
    {
      ++v4;
      *(_WORD *)replay_payload = run_records->lateral_x;
      ++run_records;
      replay_payload += 2;
    }
    while ( v4 < record->replay_sample_count );
  }
  v7 = record->replay_sample_count;
  v8 = 0;
  v9 = &compact->replay_payload[2 * v7];
  if ( v7 > 0 )
  {
    p_delta_z = &record->run_records[0].delta_z;
    do
    {
      ++v8;
      *(_WORD *)v9 = *p_delta_z;
      p_delta_z += 3;
      v9 += 2;
    }
    while ( v8 < record->replay_sample_count );
  }
  v11 = record->replay_sample_count;
  v12 = 0;
  v13 = &compact->replay_payload[4 * v11];
  if ( v11 > 0 )
  {
    p_flags = &record->run_records[0].flags;
    do
    {
      v15 = *(_BYTE *)p_flags;
      p_flags += 3;
      v13[v12++] = v15;
    }
    while ( v12 < record->replay_sample_count );
  }
  result = 5 * record->replay_sample_count + 136;
  compact->byte_count = result;
  return result;
}
