/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_slug_hazard @ 0x43dc80 */
/* selector: spawn_slug_hazard */

// Exact allocator for one live `Slug`: scans the eight owned 0xec-byte records, installs the borrowed owner Player, scales `(0, 0, -0.2)` by the subgame rate, links the inherited body before the embedded Player tail, and arms the spaced engagement-voice gate. Android and iOS identify the owning caller as `cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)`. The Windows result shape remains intentionally unresolved: its sole caller discards EAX, but a void probe removes two native instructions.
int32_t __thiscall spawn_slug_hazard(SubgameRuntime *game, TrackRowCell *cell, Player *owner_player)
{
  int32_t result; // eax
  struct SlugStateStrideCursor *slug_state_cursor; // ecx
  struct SlugSlotCursor *slug_slot_cursor; // esi
  double v7; // st7
  double v8; // st7
  Slug *p_slug; // eax
  BodList *p_active_bod_list; // edx
  Player *p_player; // ecx
  uint32_t list_flags; // ecx
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx
  Vec3 *p_position; // eax
  uint32_t v16; // eax
  float v17; // [esp+8h] [ebp-8h]
  float z; // [esp+Ch] [ebp-4h]
  float v19; // [esp+Ch] [ebp-4h]

  result = 0;
  for ( slug_state_cursor = (struct SlugStateStrideCursor *)&game->slug_hazards.slots[0].state;
        slug_state_cursor->state;
        ++slug_state_cursor )
  {
    if ( ++result >= 8 )
      return result;
  }
  slug_slot_cursor = (struct SlugSlotCursor *)((char *)game + 236 * result);
  slug_slot_cursor->slug.state = SUB_SLUG_STATE_ACTIVE;
  slug_slot_cursor->slug.owner_player = owner_player;
  set_matrix_identity(&slug_slot_cursor->slug.body.transform);
  v7 = cell->anchor_position.y + 1.7;
  z = cell->anchor_position.z;
  slug_slot_cursor->slug.body.transform.position.x = cell->anchor_position.x;
  v17 = v7;
  slug_slot_cursor->slug.body.transform.position.y = v17;
  slug_slot_cursor->slug.body.transform.position.z = z;
  project_position_onto_track_attachment(
    game,
    (Vec3 *)&slug_slot_cursor->slug.body.transform.position,
    &slug_slot_cursor->slug.attachment_facing_angle);
  v8 = game->subgame_rate * -0.2;
  slug_slot_cursor->slug.velocity.x = 0.0;
  slug_slot_cursor->slug.velocity.y = 0.0;
  p_slug = &slug_slot_cursor->slug;
  v19 = v8;
  slug_slot_cursor->slug.velocity.z = v19;
  p_active_bod_list = &g_game_base->active_bod_list;
  p_player = &game->player;
  if ( (slug_slot_cursor->slug.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    slug_slot_cursor->slug.body.bod.bod.list_next = &p_player->body.bod.bod;
    if ( (Player *)p_active_bod_list->first == p_player )
    {
      game->player.body.bod.bod.list_prev = &p_slug->body.bod.bod;
      p_active_bod_list->first = &p_slug->body.bod.bod;
      slug_slot_cursor->slug.body.bod.bod.list_prev = nullptr;
    }
    else
    {
      slug_slot_cursor->slug.body.bod.bod.list_prev = game->player.body.bod.bod.list_prev;
      game->player.body.bod.bod.list_prev = &p_slug->body.bod.bod;
      slug_slot_cursor->slug.body.bod.bod.list_prev->list_next = &p_slug->body.bod.bod;
    }
    list_flags = slug_slot_cursor->slug.body.bod.bod.list_flags;
    BYTE1(list_flags) |= 2u;
    slug_slot_cursor->slug.body.bod.bod.list_flags = list_flags;
  }
  sprite = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 118, -1, -1);
  slug_slot_cursor->slug.sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  set_color_white(&slug_slot_cursor->slug.sprite->color);
  slug_slot_cursor->slug.sprite->gravity_step = 0.0;
  slug_slot_cursor->slug.sprite->progress = 0.0;
  slug_slot_cursor->slug.sprite->progress_step = 0.0;
  slug_slot_cursor->slug.sprite->size_start = 2.0;
  slug_slot_cursor->slug.sprite->size_end = 2.0;
  p_position = &slug_slot_cursor->slug.sprite->position;
  p_position->x = slug_slot_cursor->slug.body.transform.position.x;
  p_position->y = slug_slot_cursor->slug.body.transform.position.y;
  p_position->z = slug_slot_cursor->slug.body.transform.position.z;
  slug_slot_cursor->slug.source_cell = cell;
  slug_slot_cursor->slug.passed_player = 0;
  slug_slot_cursor->slug.hit_flash_pending = 0;
  slug_slot_cursor->slug.hit_flash_progress = 0.0;
  slug_slot_cursor->slug.hit_flash_progress_step = g_game_base->subgame.subgame_rate * 0.16666667;
  slug_slot_cursor->slug.hit_points = 7;
  v16 = slug_slot_cursor->slug.body.bod.bod.list_flags;
  BYTE1(v16) &= ~0x10u;
  slug_slot_cursor->slug.body.bod.bod.list_flags = v16;
  slug_slot_cursor->slug.voice_active = 0;
  slug_slot_cursor->slug.player_encounter_latched = 0;
  slug_slot_cursor->slug.voice_progress = 0.0;
  slug_slot_cursor->slug.voice_progress_step = 0.033333335;
  if ( cell->anchor_position.z > (double)game->next_slug_voice_trigger_z )
  {
    slug_slot_cursor->slug.engagement_voice_gate = 1;
    game->next_slug_voice_trigger_z = game->slug_voice_trigger_spacing_z + game->next_slug_voice_trigger_z;
  }
  slug_slot_cursor->slug.blink_progress = 0.0;
  result = next_math_random_value();
  slug_slot_cursor->slug.blink_step = 1.0 / (((double)result * 0.000030517578 + 1.0) * 60.0);
  return result;
}
