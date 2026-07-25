/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */
/* selector: update_ring_or_special_effect_particle */

// Windows `cRSubRingStar::AI()`: advances one inline SubRingStar child around its borrowed SubRing parent, updates the child sprite position, and optionally dispatches Shower. Cross-port iOS preserves the authored owner and method.
void __thiscall update_ring_or_special_effect_particle(SubRingStar *particle)
{
  double v2; // st7
  SubRingPositionAdvanceCursor *parent_position_cursor; // eax
  double v4; // st7
  Vec3 *p_position; // ecx
  double v6; // st7
  SubRing *parent; // eax
  float v8; // [esp+4h] [ebp-10h]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]
  float position_z_after_advance; // [esp+10h] [ebp-4h]

  if ( particle->parent->kind != SUB_RING_KIND_SLOW_DEFAULT )
    particle->phase = particle->phase_step + particle->phase;
  if ( particle->phase > 6.2831855 )
    particle->phase = particle->phase - 6.2831855;
  v8 = cosine(particle->phase) * particle->radius;
  v2 = sine(particle->phase);
  parent_position_cursor = (SubRingPositionAdvanceCursor *)particle->parent;
  v4 = v2 * particle->radius + parent_position_cursor->position_x_before_advance;
  parent_position_cursor = (SubRingPositionAdvanceCursor *)((char *)parent_position_cursor + 104);
  p_position = &particle->sprite->position;
  v9 = v4;
  v6 = v8 + parent_position_cursor->position_y_after_advance;
  position_z_after_advance = parent_position_cursor->position_z_after_advance;
  p_position->x = v9;
  v10 = v6;
  p_position->y = v10;
  p_position->z = position_z_after_advance;
  parent = particle->parent;
  if ( !parent->star_shower_counter )
    emit_ring_star_shower(particle, parent->owner_player);
}
