/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: emit_ring_star_shower @ 0x43e690 */
/* selector: emit_ring_star_shower */

// Exact `cRSubRingStar::Shower(cRSubGoldy*)`: emits a managed star sprite from one inline SubRingStar child when a SubRing collection resolves. Cross-port iOS v1.9 preserves the authored signature.
void __thiscall emit_ring_star_shower(SubRingStar *particle, Player *owner)
{
  Sprite *sprite; // esi
  SpriteFlag flags; // eax
  double v5; // st7
  Vec3 *p_position; // eax
  float z; // eax
  float v8; // [esp+0h] [ebp-24h]
  float v9; // [esp+0h] [ebp-24h]
  float v10; // [esp+Ch] [ebp-18h]
  float v11; // [esp+10h] [ebp-14h]
  float v12; // [esp+18h] [ebp-Ch]

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    sprite = allocate_sprite(&g_sprite_manager, owner->player_slot, particle->parent->star_sprite_id, -1, -1);
    flags = sprite->flags;
    sprite->progress = 0.0;
    BYTE1(flags) |= 8u;
    sprite->progress_step = 0.1111111;
    sprite->flags = flags;
    sprite->size_start = 0.40000001;
    sprite->size_end = 0.2;
    v8 = particle->phase + 1.0471976;
    v12 = sine(v8) * particle->radius;
    v9 = particle->phase + 1.0471976;
    v10 = v12 * 0.30000001;
    v5 = cosine(v9) * particle->radius * 0.30000001;
    sprite->velocity.x = v10;
    v11 = v5;
    sprite->velocity.y = v11;
    sprite->velocity.z = 0.0;
    p_position = &particle->sprite->position;
    sprite->position.x = p_position->x;
    sprite->position.y = p_position->y;
    z = p_position->z;
    sprite->gravity_step = 0.0;
    sprite->position.z = z;
  }
}
