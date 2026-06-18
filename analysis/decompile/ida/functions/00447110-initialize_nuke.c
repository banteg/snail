/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_nuke @ 0x447110 */
/* selector: initialize_nuke */

// Spawns the 25-sprite ring effect used by ring/special-effect collision kinds `2` and `6`, seeds its orbit height and phase step from the owning player and global tick delta, and immediately dispatches the first update. Cross-port Android symbols match this helper to `cRNuke::Init()`.
int32_t __thiscall initialize_nuke(NukeController *nuke)
{
  void **sprite_slots; // esi
  int v3; // ebp
  double v4; // st7
  void *sprite; // eax
  int v6; // edx
  _DWORD *v7; // eax
  _DWORD *v8; // eax

  if ( !nuke->state )
  {
    sprite_slots = nuke->sprite_slots;
    v3 = 25;
    nuke->orbit_center_z = nuke->owner_player->live_matrix.position.z - 5.0;
    v4 = *((float *)MEMORY[0x4DF904] + 119188) + *((float *)MEMORY[0x4DF904] + 119188);
    nuke->orbit_phase = 0.0;
    nuke->orbit_phase_step = 0.10471976;
    nuke->state = 1;
    nuke->orbit_center_z_step = v4;
    do
    {
      sprite = allocate_sprite(g_sprite_manager, nuke->owner_player->player_slot, 131, -1, -1);
      *sprite_slots = sprite;
      v6 = *((_DWORD *)sprite + 1);
      BYTE1(v6) |= 8u;
      ++sprite_slots;
      *((_DWORD *)sprite + 1) = v6;
      *((_DWORD *)*(sprite_slots - 1) + 26) = 0;
      *((_DWORD *)*(sprite_slots - 1) + 27) = 0;
      *((_DWORD *)*(sprite_slots - 1) + 24) = 1077936128;
      *((_DWORD *)*(sprite_slots - 1) + 25) = 1077936128;
      v7 = (char *)*(sprite_slots - 1) + 84;
      v7[2] = 0;
      v7[1] = 0;
      *v7 = 0;
      v8 = (char *)*(sprite_slots - 1) + 72;
      --v3;
      v8[2] = 0;
      v8[1] = 0;
      *v8 = 0;
      *((_DWORD *)*(sprite_slots - 1) + 30) = 0;
    }
    while ( v3 );
  }
  return update_nuke(nuke);
}
