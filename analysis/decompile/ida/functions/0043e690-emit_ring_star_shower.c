/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: emit_ring_star_shower @ 0x43e690 */
/* selector: emit_ring_star_shower */

// Exact `cRSubRingStar::Shower(cRSubGoldy*)`: emits a managed star sprite from one inline SubRingStar child when a SubRing collection resolves. Cross-port iOS v1.9 preserves the authored signature.
void __thiscall emit_ring_star_shower(SubRingStar *particle, Player *owner)
{
  float *sprite; // esi
  int v4; // eax
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
    sprite = (float *)allocate_sprite(g_sprite_manager, owner->player_slot, particle->parent->star_sprite_id, -1, -1);
    v4 = *((_DWORD *)sprite + 1);
    sprite[26] = 0.0;
    BYTE1(v4) |= 8u;
    sprite[27] = 0.1111111;
    *((_DWORD *)sprite + 1) = v4;
    sprite[24] = 0.40000001;
    sprite[25] = 0.2;
    v8 = particle->phase + 1.0471976;
    v12 = sine(v8) * particle->radius;
    v9 = particle->phase + 1.0471976;
    v10 = v12 * 0.30000001;
    v5 = cosine(v9) * particle->radius * 0.30000001;
    sprite[21] = v10;
    v11 = v5;
    sprite[22] = v11;
    sprite[23] = 0.0;
    p_position = &particle->sprite->position;
    sprite[18] = p_position->x;
    sprite[19] = p_position->y;
    z = p_position->z;
    sprite[30] = 0.0;
    sprite[20] = z;
  }
}
