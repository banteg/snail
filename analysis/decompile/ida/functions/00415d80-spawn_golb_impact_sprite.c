/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_impact_sprite @ 0x415d80 */
/* selector: spawn_golb_impact_sprite */

// Side-effect-only `GolbShot` member that allocates the short-lived impact sprite used when a shot is killed or reaches a terminal collision point, seeded from the supplied world position.
void __thiscall spawn_golb_impact_sprite(GolbShot *shot, Vec3 *position)
{
  Vec3 *sprite; // eax
  float y; // ecx

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    sprite = (Vec3 *)allocate_sprite(g_sprite_manager, shot->owner_player->player_slot, 33, -1, -1);
    y = sprite->y;
    BYTE1(y) |= 8u;
    sprite->y = y;
    sprite[8].z = 0.0;
    sprite[7].x = 0.0;
    sprite[9].y = 0.0;
    sprite[7].y = 0.050000001;
    sprite[10].x = 0.0;
    sprite[9].x = 0.055555552;
    sprite[9].z = 0.83333337;
    sprite[8].x = 0.5;
    sprite[8].y = 1.0;
    sprite[7].z = 0.0;
    sprite[6] = *position;
  }
}
