/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_subgame @ 0x437b10 */
/* selector: reset_subgame */

// Exact Windows implementation of authored `void cRSubGame::ReSet()`: rebinds the inline pickup, garbage, slug, and ring pools to their containing `cRSubGame`, restores or clears the replay score/timer snapshot, rearms the scan and camera latches, and empties the active garbage chain. Android preserves the same owner graph, replay-mode branch, timer handoff, and final latches despite platform-specific pool layouts. All five native callsites pass the active subgame receiver from `initialize_subgame`, matching Android `cRSubGame::Init()` ending in `ReSet(this)`.
void __thiscall reset_subgame(cRSubGame *game)
{
  int v2; // ecx
  cRSubGame **p_owner_game; // eax
  cRSubGame **v4; // eax
  int i; // ecx
  cRSubGame **v6; // eax
  int j; // ecx
  cRSubGame **p_rate_source; // eax
  int k; // ecx
  int32_t score_tail; // edx
  int32_t replay_start_cursor; // eax

  v2 = 8;
  p_owner_game = &game->health_pickups[0].owner_game;
  do
  {
    *(p_owner_game - 3) = nullptr;
    *p_owner_game = game;
    p_owner_game += 29;
    --v2;
  }
  while ( v2 != 0 );
  game->speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  game->speedup_pickup.owner_game = game;
  game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  game->jetpack_pickup.owner_game = game;
  v4 = &game->garbage_hazards.slots[0].owner_game;
  for ( i = 50; i != 0; --i )
  {
    *(v4 - 2) = nullptr;
    *v4 = game;
    *(v4 - 3) = nullptr;
    v4 += 49;
  }
  v6 = &game->slug_hazards.slots[0].owner_game;
  for ( j = 8; j != 0; --j )
  {
    *(v6 - 2) = nullptr;
    *v6 = game;
    v6 += 59;
  }
  p_rate_source = &game->ring_effects.slots[0].rate_source;
  for ( k = 2; k != 0; --k )
  {
    *(p_rate_source - 84) = nullptr;
    *p_rate_source = game;
    p_rate_source += 126;
  }
  if ( game->selected_level_record_active == 1 && game->level_mode == game->current_high_score_record.replay_mode_id )
  {
    score_tail = game->current_high_score_record.score_tail;
    replay_start_cursor = game->current_high_score_record.replay_start_cursor;
    game->player.total_score = game->current_high_score_record.score;
    game->player.score_tail = score_tail;
    qmemcpy(&game->player.stopwatch, &game->current_high_score_record.score_or_time, sizeof(game->player.stopwatch));
    game->player.replay_start_cursor = replay_start_cursor;
  }
  else
  {
    if ( game->subgame_rebuild_selector == 2 )
    {
      game->player.total_score = 0;
      clear_subgoldy_score_buckets(&game->player);
    }
    zero_timer_counters(&game->player.stopwatch);
    game->player.score_tail = 0;
    game->player.replay_start_cursor = 0;
  }
  game->player.last_ring_spawn_z = 0.0;
  game->scan_reset = 1;
  game->camera_snap_requested = 1;
  game->selected_level_record_active = 0;
  game->garbage_hazards.active_head = nullptr;
}
