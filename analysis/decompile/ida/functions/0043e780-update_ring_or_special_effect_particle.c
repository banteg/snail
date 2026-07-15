/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */
/* selector: update_ring_or_special_effect_particle */

// Windows `cRSubRingStar::AI()`: advances one inline SubRingStar child around its borrowed SubRing parent, updates the child sprite position, and optionally dispatches Shower. Cross-port iOS preserves the authored owner and method.
void __thiscall update_ring_or_special_effect_particle(SubRingStar *particle)
{
  double v2; // st7
  SubRing *parent; // eax
  double v4; // st7
  Vec3 *p_position; // ecx
  double v6; // st7
  SubRing *v7; // eax
  float v8; // [esp+4h] [ebp-10h]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]
  struct BodNode *list_prev; // [esp+10h] [ebp-4h]

  if ( particle->parent->kind != SUB_RING_KIND_SLOW_DEFAULT )
    particle->phase = particle->phase_step + particle->phase;
  if ( particle->phase > 6.2831855 )
    particle->phase = particle->phase - 6.2831855;
  v8 = cosine(particle->phase) * particle->radius;
  v2 = sine(particle->phase);
  parent = particle->parent;
  v4 = v2 * particle->radius + parent->body.transform.position.x;
  parent = (SubRing *)((char *)parent + 104);
  p_position = &particle->sprite->position;
  v9 = v4;
  v6 = v8 + *(float *)&parent->body.bod.bod.list_flags;
  list_prev = parent->body.bod.bod.list_prev;
  p_position->x = v9;
  v10 = v6;
  p_position->y = v10;
  LODWORD(p_position->z) = list_prev;
  v7 = particle->parent;
  if ( !v7->star_shower_counter )
    emit_ring_star_shower(particle, v7->owner_player);
}
