/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: complete_subgame @ 0x438700 */
/* selector: complete_subgame */

// Snapshots the just-finished run into the working high-score/replay record, including the normalized garbage and salt frequencies, increments the per-run completion counter, and dispatches the mode-specific high-score handoff. Cross-port Android and iOS symbols match this helper to `cRSubGame::Complete(bool)`.
void __thiscall complete_subgame(SubgameRuntime *runtime, unsigned __int8 completed)
{
  int32_t v3; // ecx
  int32_t score_tail; // eax
  float challenge_difficulty_scalar; // esi
  int32_t completion_bonus_x_source; // ecx
  RuntimeRateOrLevelArg v7; // eax
  float garbage_frequency; // esi
  int32_t level_mode; // eax
  float salt_frequency; // esi
  int32_t startup_track_index; // ecx
  int v12; // eax

  display_score_stats(&runtime->player);
  runtime->current_high_score_record.run_records[runtime->replay_update_cursor].flags |= 8u;
  v3 = runtime->replay_update_cursor + 1;
  ++runtime->current_high_score_record.replay_sample_count;
  runtime->replay_update_cursor = v3;
  if ( (g_cheat_state & 1) == 0 )
  {
    score_tail = runtime->player.score_tail;
    runtime->current_high_score_record.score = runtime->player.total_score;
    qmemcpy(
      &runtime->current_high_score_record.score_or_time,
      &runtime->player.stopwatch,
      sizeof(runtime->current_high_score_record.score_or_time));
    challenge_difficulty_scalar = runtime->challenge_difficulty_scalar;
    completion_bonus_x_source = runtime->completion_bonus_x_source;
    runtime->current_high_score_record.score_tail = score_tail;
    runtime->current_high_score_record.challenge_difficulty_value = runtime->completion_bonus_y_source;
    LODWORD(v7.base_rate) = runtime->rate_or_level_arg;
    runtime->current_high_score_record.challenge_difficulty_scalar = challenge_difficulty_scalar;
    garbage_frequency = runtime->garbage_frequency;
    runtime->current_high_score_record.replay_speed_scalar = v7.base_rate;
    level_mode = runtime->level_mode;
    runtime->current_high_score_record.garbage_frequency = garbage_frequency;
    salt_frequency = runtime->salt_frequency;
    runtime->current_high_score_record.challenge_speed_value = completion_bonus_x_source;
    startup_track_index = runtime->player.startup_track_index;
    runtime->current_high_score_record.salt_frequency = salt_frequency;
    runtime->current_high_score_record.active = 1;
    runtime->current_high_score_record.source_tail = startup_track_index;
    runtime->current_high_score_record.replay_mode_id = level_mode;
    if ( (level_mode != 1 || startup_track_index) && !runtime->selected_level_record_active && completed == 1 )
    {
      if ( level_mode )
      {
        v12 = level_mode - 1;
        if ( v12 )
        {
          if ( v12 == 3 )
            add_time_trial_high_score(
              (SubHighScore *)((char *)&g_high_score_bank + (_DWORD)runtime),
              &runtime->current_high_score_record,
              runtime->level_mode_arg,
              runtime->player.completion_handoff_active);
        }
        else
        {
          add_survival_high_score(
            (SubHighScore *)((char *)&g_high_score_bank + (_DWORD)runtime),
            &runtime->current_high_score_record);
        }
      }
      else
      {
        add_arcade_high_score(
          (SubHighScore *)((char *)&g_high_score_bank + (_DWORD)runtime),
          &runtime->current_high_score_record,
          runtime->level_mode_arg);
      }
    }
  }
}
