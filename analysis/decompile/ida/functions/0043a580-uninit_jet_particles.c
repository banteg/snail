/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_jet_particles @ 0x43a580 */
/* selector: uninit_jet_particles */

// Exact Windows `SubHover::uninit_jet_particles`, authored as `cRSubHover::JetUnInit`: kills both sprites in each of the owner's fifteen inline jet rows.
void __thiscall uninit_jet_particles(SubHover *sub_hover)
{
  JetParticleSlot *particle_slots; // esi
  int v2; // ebx
  int v3; // edi

  particle_slots = sub_hover->particle_slots;
  v2 = 15;
  do
  {
    v3 = 2;
    do
    {
      kill_sprite(particle_slots->sprite);
      ++particle_slots;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
}
