/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_trail_sprite @ 0x415bb0 */
/* selector: spawn_golb_trail_sprite */

// `GolbShot` member that allocates and returns one short-lived trail sprite for the straight-flight Golb family at the supplied world position. `update_golb_ai` emits it in a short three-point chain behind the projectile each tick.
Sprite *__thiscall spawn_golb_trail_sprite(GolbShot *shot, Vec3 *position)
{
  Sprite *result; // eax
  SpriteFlag flags; // ecx
  uint32_t movement_flags; // ecx

  result = (Sprite *)allocate_sprite(g_sprite_manager, shot->owner_player->player_slot, 33, -1, -1);
  flags = result->flags;
  BYTE1(flags) |= 8u;
  result->progress = 0.0;
  result->flags = flags;
  movement_flags = shot->owner_player->movement_flags;
  if ( (movement_flags & 1) != 0 )
  {
    result->progress_step = 0.23809524;
  }
  else if ( (movement_flags & 2) != 0 )
  {
    result->progress_step = 0.33333334;
  }
  result->progress_step = 0.55555558;
  result->lifetime = 0.0;
  result->lifetime_step = 0.0;
  result->size_start = 0.2;
  result->size_end = 0.029999999;
  result->velocity.z = 0.0;
  result->velocity.y = 0.0;
  result->velocity.x = 0.0;
  result->gravity_step = 0.0;
  result->position = *position;
  result->object_ref = shot->object_ref;
  return result;
}
