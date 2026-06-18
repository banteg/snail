/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */
/* selector: update_ring_or_special_effect_particle */

// Advances one child sprite in the bullet-owned ring or special-effect halo, updating its circular phase around the parent projectile and refreshing the live effect position before optional star-shower emission.
void __thiscall update_ring_or_special_effect_particle(RingOrSpecialEffectParticle *particle)
{
  double orbit_x_unit; // st7
  RingOrSpecialEffectParent *parent; // eax
  double staged_x; // st7
  Vec3 *sprite_position; // ecx
  double staged_y_tmp; // st7
  RingOrSpecialEffectParent *result_parent; // eax
  float orbit_y; // [esp+4h] [ebp-10h]
  float staged_x_local; // [esp+8h] [ebp-Ch]
  float staged_y_local; // [esp+Ch] [ebp-8h]
  int staged_z_bits; // [esp+10h] [ebp-4h]

  if ( particle->parent->kind != 3 )
    particle->phase = particle->phase_step + particle->phase;
  if ( particle->phase > 6.2831855 )
    particle->phase = particle->phase - 6.2831855;
  orbit_y = cosine(particle->phase) * particle->radius;
  orbit_x_unit = sine(particle->phase);
  parent = particle->parent;
  staged_x = orbit_x_unit * particle->radius + parent->world_position.x;
  sprite_position = &particle->sprite->position;
  staged_x_local = staged_x;
  staged_y_tmp = orbit_y + parent->world_position.y;
  staged_z_bits = *(_DWORD *)&parent->world_position.z;
  sprite_position->x = staged_x_local;
  staged_y_local = staged_y_tmp;
  sprite_position->y = staged_y_local;
  *(_DWORD *)&sprite_position->z = staged_z_bits;
  result_parent = particle->parent;
  if ( !result_parent->star_shower_counter )
    emit_ring_star_shower(particle, result_parent->owner_player);
}
