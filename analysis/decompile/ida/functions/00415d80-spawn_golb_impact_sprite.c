/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_impact_sprite @ 0x415d80 */
/* selector: spawn_golb_impact_sprite */

// Side-effect-only `cRSubGolb::Explode(tVector)`/`GolbShot` member that allocates the short-lived impact sprite used when a shot is killed or reaches a terminal collision point, seeded from the supplied world position. Android preserves the owner and effect contract with a platform-specific sprite resource id.
void __thiscall spawn_golb_impact_sprite(GolbShot *shot, Vec3 *position)
{
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    sprite = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 33, -1, -1);
    flags = sprite->flags;
    BYTE1(flags) |= 8u;
    sprite->flags = flags;
    sprite->progress = 0.0;
    sprite->velocity.x = 0.0;
    sprite->lifetime = 0.0;
    sprite->velocity.y = 0.050000001;
    sprite->gravity_step = 0.0;
    sprite->progress_step = 0.055555552;
    sprite->lifetime_step = 0.83333337;
    sprite->size_start = 0.5;
    sprite->size_end = 1.0;
    sprite->velocity.z = 0.0;
    sprite->position = *position;
  }
}
