/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_ring_or_special_effect_particles @ 0x43e470 */
/* selector: initialize_ring_or_special_effect_particles */

// Windows `cRSubRing::Init(int)`: arms one SubRing and initializes its ten inline 0x20-byte SubRingStar children, mapping authored effect kinds onto the ParticleRing, ParticleExplode, and ParticleSlow sprite families. The function is exact at 153 instructions.
int32_t __thiscall initialize_ring_or_special_effect_particles(SubRing *ring, int32_t unused_lives_snapshot)
{
  Vec4 *p_position; // ebp
  SubRingStar *particles; // esi
  SubRingKind kind; // eax
  SpriteFlag flags; // ecx
  Vec3 *v7; // edx
  SubRingKind v8; // eax
  int32_t result; // eax
  int v10; // [esp+10h] [ebp-14h]
  Color4f color; // [esp+14h] [ebp-10h] BYREF

  v10 = 0;
  ring->state = SUB_RING_STATE_ACTIVE;
  ring->star_shower_counter = 0;
  p_position = &ring->body.transform.position;
  particles = ring->particles;
  do
  {
    particles->phase = (double)v10 * 0.62831855;
    particles->phase_step = ring->rate_source->subgame_rate * 0.10471976;
    particles->parent = ring;
    particles->base_position.x = p_position->x;
    particles->base_position.y = p_position->y;
    particles->base_position.z = p_position->z;
    particles->radius = 1.2;
    kind = ring->kind;
    switch ( kind )
    {
      case SUB_RING_KIND_NORMAL_DEFAULT:
      case SUB_RING_KIND_NORMAL_AUTHORED:
      case SUB_RING_KIND_POWER_UP_AUTHORED:
        particles->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 135, -1, -1);
        ring->star_sprite_id = 136;
        particles->sprite->draw_mode = 9;
        break;
      case SUB_RING_KIND_EXPLODE_RAMP:
      case SUB_RING_KIND_EXPLODE_AUTHORED:
        particles->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 131, -1, -1);
        ring->star_sprite_id = 132;
        particles->sprite->draw_mode = 13;
        break;
      case SUB_RING_KIND_SLOW_DEFAULT:
      case SUB_RING_KIND_SLOW_AUTHORED:
        particles->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 133, -1, -1);
        ring->star_sprite_id = 134;
        particles->sprite->draw_mode = 13;
        break;
    }
    particles->sprite->color = *set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.80000001);
    flags = particles->sprite->flags;
    BYTE1(flags) |= 8u;
    particles->sprite->flags = flags;
    particles->sprite->progress = 0.0;
    particles->sprite->progress_step = 0.0;
    particles->sprite->gravity_step = 0.0;
    particles->sprite->size_start = 0.72000003;
    particles->sprite->size_end = 0.72000003;
    v7 = &particles->sprite->position;
    v7->x = p_position->x;
    v7->y = p_position->y;
    v7->z = p_position->z;
    particles->sprite->facing_angle = particles->phase;
    v8 = ring->kind;
    if ( v8 == SUB_RING_KIND_SLOW_DEFAULT || v8 == SUB_RING_KIND_EXPLODE_AUTHORED )
      particles->sprite->facing_angle_step = 0.0;
    else
      particles->sprite->facing_angle_step = -particles->phase_step;
    update_ring_or_special_effect_particle(particles++);
    result = ++v10;
  }
  while ( v10 < 10 );
  return result;
}
