/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_jet_particles @ 0x43a5b0 */
/* selector: initialize_jet_particles */

// Exact Windows `SubHover::initialize_jet_particles`, authored as `cRSubHover::JetInit`: allocates and initializes the 15-by-2 inline jet sprite grid.
void __thiscall initialize_jet_particles(SubHover *sub_hover)
{
  JetParticleSlot *particle_slots; // esi
  int v2; // ebx
  Sprite *sprite; // eax
  SpriteFlag flags; // edx
  Vec3 *p_velocity; // eax
  tColour *v6; // eax
  tColour *p_color; // ecx
  int v8; // [esp+10h] [ebp-14h]
  Color4f color; // [esp+14h] [ebp-10h] BYREF

  particle_slots = sub_hover->particle_slots;
  v8 = 15;
  do
  {
    v2 = 2;
    do
    {
      sprite = allocate_sprite(&g_sprite_manager, 1, 158, -1, -1);
      particle_slots->sprite = sprite;
      flags = sprite->flags;
      BYTE1(flags) |= 8u;
      sprite->flags = flags;
      particle_slots->sprite->progress = 0.0;
      particle_slots->sprite->progress_step = 0.0;
      particle_slots->sprite->lifetime = 0.0;
      particle_slots->sprite->lifetime_step = 0.0;
      particle_slots->sprite->size_end = 0.0;
      particle_slots->sprite->size_start = 0.0;
      p_velocity = &particle_slots->sprite->velocity;
      p_velocity->z = 0.0;
      p_velocity->y = 0.0;
      p_velocity->x = 0.0;
      particle_slots->sprite->gravity_step = 0.0;
      v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.99900001);
      p_color = &particle_slots->sprite->color;
      ++particle_slots;
      --v2;
      *p_color = *v6;
      particle_slots[-1].wobble_x = 0.0;
      particle_slots[-1].sprite->draw_mode = 0;
      particle_slots[-1].wobble_y = 0.0;
      particle_slots[-1].wobble_alpha = 0.16666667;
    }
    while ( v2 );
    --v8;
  }
  while ( v8 );
}
