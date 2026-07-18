/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: run_frame_update @ 0x40a2a0 */
/* selector: run_frame_update */

// Runs one cRGame::AI frame: advances root fade/audio/cheat/voice state, seeds the fixed-step accumulator and input-sampling gate, draws the captured cursor from player zero's saved cursor position, updates the root BOD list and both cRPlayer callbacks, advances every sprite bucket, resets the subgame contact registry, and returns the root quit request.
int __thiscall run_frame_update(GameRoot *game)
{
  double v2; // st7
  int v3; // ebx
  int32_t v4; // edx
  tColour *v5; // eax
  BodNode *first; // edi
  struct BodNode *list_next; // esi
  uint32_t list_flags; // eax
  uint32_t v9; // eax
  Sprite **v10; // edi
  Sprite *v11; // ecx
  Sprite *next; // esi
  double fixed_update_accumulator; // st7
  float x; // [esp+0h] [ebp-38h]
  float y; // [esp+4h] [ebp-34h]
  int v17; // [esp+24h] [ebp-14h]
  Color4f color; // [esp+28h] [ebp-10h] BYREF

  update_frontend_transition_overlay((float *)&game->fade.state);
  noop_runtime_ai();
  update_cheat(&g_cheat_state);
  update_voice_manager(&g_voice_manager);
  v2 = game->fixed_update_accumulator + 1.0;
  v3 = 0;
  v4 = game->frame_counter + 1;
  game->frontend_quit_requested = 0;
  game->fixed_update_accumulator = v2;
  game->fixed_update_count = 1;
  game->frame_counter = v4;
  game->input_sampling_gate = 1;
  v17 = 0;
  if ( is_mouse_captured(&game->players[0].mouse_cursor) )
  {
    if ( game->players[0].mouse_cursor.suppress_next_draw )
    {
      game->players[0].mouse_cursor.suppress_next_draw = 0;
    }
    else
    {
      v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      y = game->players[0].mouse_cursor.saved_y - 7.0;
      x = game->players[0].mouse_cursor.saved_x - 8.0;
      queue_axis_aligned_textured_quad(22, x, y, 64.0, 64.0, 0x1000000u, v5, 7);
    }
  }
  if ( game->fixed_update_accumulator <= 1.0 )
    return game->frontend_quit_requested;
  do
  {
    game->fixed_update_accumulator = game->fixed_update_accumulator - 1.0;
    draw_frontend_overlay_color_lerp((char *)&game->players[0].frontend_overlay);
    first = game->active_bod_list.first;
    if ( first )
    {
      while ( 1 )
      {
        if ( (first->list_flags & 0x10) != 0 )
          report_errorf(aDebugBodAi);
        list_next = first->list_next;
        if ( list_next )
        {
          list_flags = list_next->list_flags;
          LOBYTE(list_flags) = list_flags | 0x40;
          list_next->list_flags = list_flags;
        }
        (*(void (__thiscall **)(BodNode *))first->vtable)(first);
        first = list_next;
        ++v17;
        if ( !list_next )
          break;
        v9 = list_next->list_flags;
        LOBYTE(v9) = v9 & 0xBF;
        list_next->list_flags = v9;
      }
    }
    (*(void (__thiscall **)(GamePlayer *))game->players[0].body.bod.bod.vtable)(game->players);
    if ( game->subgame.level_mode == 6 )
      (*(void (__thiscall **)(GamePlayer *))game->players[1].body.bod.bod.vtable)(&game->players[1]);
    v10 = g_sprite_active_heads;
    do
    {
      v11 = *v10;
      if ( *v10 )
      {
        do
        {
          next = v11->next;
          update_sprite(v11);
          ++v3;
          v11 = next;
        }
        while ( next );
      }
      ++v10;
    }
    while ( (int)v10 < (int)&g_sprite_free_head );
    initialize_enemy_manager(&game->subgame.enemy_manager.count);
    fixed_update_accumulator = game->fixed_update_accumulator;
    game->input_sampling_gate = 0;
  }
  while ( fixed_update_accumulator > 1.0 );
  return game->frontend_quit_requested;
}
