/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_parcel_slots @ 0x443160 */
/* selector: initialize_track_parcel_slots */

// Exact `ParcelManager` initializer: clears all 50 Parcel states and seeds each borrowed cRSubGame backlink. Android retains the authored member as `cRParcelManager::Init()`.
void __thiscall initialize_track_parcel_slots(ParcelManager *manager)
{
  cRSubGame **p_owner_subgame; // eax
  int i; // ecx

  p_owner_subgame = &manager->slots[0].owner_subgame;
  for ( i = 50; i != 0; --i )
  {
    *(p_owner_subgame - 1) = nullptr;
    *p_owner_subgame = &g_game_base->subgame;
    p_owner_subgame += 35;
  }
}
