/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_nuke @ 0x447110 */
/* selector: initialize_nuke */

// Initializes the exact 0x7c-byte cRNuke owner at Player +0x150: spawns the 25-sprite ring effect used by collision kinds `2` and `6`, seeds its orbit height and phase step from the owning player and global tick delta, and immediately dispatches `cRNuke::AI()`. Android retains this method as `cRNuke::Init()`.
void __thiscall initialize_nuke(Nuke *nuke)
{
  Sprite **sprite_slots; // esi
  int v3; // ebp
  double v4; // st7
  Sprite *sprite; // eax
  SpriteFlag flags; // edx
  Vec3 *p_velocity; // eax
  Vec3 *p_position; // eax

  if ( nuke->state == NUKE_STATE_INACTIVE )
  {
    sprite_slots = nuke->sprite_slots;
    v3 = 25;
    nuke->orbit_center_z = nuke->owner_player->body.transform.position.z - 5.0;
    v4 = g_game_base->subgame.subgame_rate + g_game_base->subgame.subgame_rate;
    nuke->orbit_phase = 0.0;
    nuke->orbit_phase_step = 0.10471976;
    nuke->state = NUKE_STATE_ACTIVE;
    nuke->orbit_center_z_step = v4;
    do
    {
      sprite = allocate_sprite(&g_sprite_manager, nuke->owner_player->player_slot, 131, -1, -1);
      *sprite_slots = sprite;
      flags = sprite->flags;
      BYTE1(flags) |= 8u;
      ++sprite_slots;
      sprite->flags = flags;
      (*(sprite_slots - 1))->progress = 0.0;
      (*(sprite_slots - 1))->progress_step = 0.0;
      (*(sprite_slots - 1))->size_start = 3.0;
      (*(sprite_slots - 1))->size_end = 3.0;
      p_velocity = &(*(sprite_slots - 1))->velocity;
      p_velocity->z = 0.0;
      p_velocity->y = 0.0;
      p_velocity->x = 0.0;
      p_position = &(*(sprite_slots - 1))->position;
      --v3;
      p_position->z = 0.0;
      p_position->y = 0.0;
      p_position->x = 0.0;
      (*(sprite_slots - 1))->gravity_step = 0.0;
    }
    while ( v3 );
  }
  update_nuke(nuke);
}
