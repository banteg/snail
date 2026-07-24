/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_subgame @ 0x437b10 */
/* selector: reset_subgame */

void __thiscall reset_subgame(SubgameRuntime *game)
{
  int v2; // ecx
  SubgameRuntime **p_owner_game; // eax
  SubgameRuntime **v4; // eax
  int v5; // ecx
  SubgameRuntime **v6; // eax
  int v7; // ecx
  SubgameRuntime **p_rate_source; // eax
  int v9; // ecx
  int32_t score_tail; // edx
  int32_t source_tail; // eax

  v2 = 8;
  p_owner_game = &game->health_pickups[0].owner_game;
  do
  {
    *(p_owner_game - 3) = nullptr;
    *p_owner_game = game;
    p_owner_game += 29;
    --v2;
  }
  while ( v2 );
  game->speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  game->speedup_pickup.owner_game = game;
  game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  game->jetpack_pickup.owner_game = game;
  v4 = &game->garbage_hazards.slots[0].owner_game;
  v5 = 50;
  do
  {
    *(v4 - 2) = nullptr;
    *v4 = game;
    *(v4 - 3) = nullptr;
    v4 += 49;
    --v5;
  }
  while ( v5 );
  v6 = &game->slug_hazards.slots[0].owner_game;
  v7 = 8;
  do
  {
    *(v6 - 2) = nullptr;
    *v6 = game;
    v6 += 59;
    --v7;
  }
  while ( v7 );
  p_rate_source = &game->ring_effects.slots[0].rate_source;
  v9 = 2;
  do
  {
    *(p_rate_source - 84) = nullptr;
    *p_rate_source = game;
    p_rate_source += 126;
    --v9;
  }
  while ( v9 );
  if ( game->selected_level_record_active == 1 && game->level_mode == game->current_high_score_record.replay_mode_id )
  {
    score_tail = game->current_high_score_record.score_tail;
    source_tail = game->current_high_score_record.source_tail;
    game->player.total_score = game->current_high_score_record.score;
    game->player.score_tail = score_tail;
    qmemcpy(&game->player.stopwatch, &game->current_high_score_record.score_or_time, sizeof(game->player.stopwatch));
    game->player.startup_track_index = source_tail;
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
    game->player.startup_track_index = 0;
  }
  game->player.last_ring_spawn_z = 0.0;
  game->scan_reset = 1;
  game->camera_snap_requested = 1;
  game->selected_level_record_active = 0;
  game->garbage_hazards.active_head = nullptr;
}
