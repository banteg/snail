/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_subgame @ 0x437b10 */
/* selector: reset_subgame */

void __thiscall reset_subgame(SubgameRuntime *game)
{
  int v2; // ecx
  SubgameRuntime **health_owner; // eax
  SubgameRuntime **garbage_game; // eax
  int v5; // ecx
  SubgameRuntime **slug_owner; // eax
  int v7; // ecx
  RingEffectRateSource **ring_rate; // eax
  int v9; // ecx
  int v10; // edx
  int saved_tail_b; // eax
  _DWORD *game_words; // scratch view for unresolved score/timer fields

  game_words = (_DWORD *)game;

  v2 = 8;
  health_owner = &game->health_pickups[0].owner_game;
  do
  {
    *(health_owner - 3) = 0; // health_pickups[i].state
    *health_owner = game; // health_pickups[i].owner_game
    health_owner += 29;
    --v2;
  }
  while ( v2 );
  game->speedup_pickup.state = 0;
  game->speedup_pickup.owner_game = game;
  game->jetpack_pickup.state = 0;
  game->jetpack_pickup.owner_game = game;
  garbage_game = &game->garbage_hazards.slots[0].game;
  v5 = 50;
  do
  {
    *(garbage_game - 2) = 0; // garbage_hazards.slots[i].state
    *garbage_game = game; // garbage_hazards.slots[i].game
    *(garbage_game - 3) = 0; // garbage_hazards.slots[i].next_active
    garbage_game += 49;
    --v5;
  }
  while ( v5 );
  slug_owner = &game->slug_slots[0].owner_game;
  v7 = 8;
  do
  {
    *(slug_owner - 2) = 0; // slug_slots[i].state
    *slug_owner = game; // slug_slots[i].owner_game
    slug_owner += 59;
    --v7;
  }
  while ( v7 );
  ring_rate = &game->ring_effects.slots[0].rate_source;
  v9 = 2;
  do
  {
    *(ring_rate - 84) = 0; // ring_effects.slots[i].state
    *ring_rate = (RingEffectRateSource *)game; // ring_effects.slots[i].rate_source
    ring_rate += 126;
    --v9;
  }
  while ( v9 );
  if ( *((_BYTE *)game_words + 16721360) == 1 && game_words[16] == game_words[4147919] )
  {
    v10 = game_words[4147916];
    saved_tail_b = game_words[4147917];
    game_words[978578] = game_words[4147909];
    game_words[978585] = v10;
    qmemcpy(game_words + 978579, game_words + 4147910, 0x18u);
    game_words[978586] = saved_tail_b;
  }
  else
  {
    if ( game_words[4834290] == 2 )
    {
      game_words[978578] = 0;
      clear_subgoldy_score_buckets((int)(game_words + 978393));
    }
    zero_timer_counters(game_words + 978579);
    game_words[978585] = 0;
    game_words[978586] = 0;
  }
  game_words[978616] = 0;
  *(_BYTE *)game_words = 1;
  *((_BYTE *)game_words + 1) = 1;
  *((_BYTE *)game_words + 16721360) = 0;
  game->garbage_hazards.active_head = 0;
}
