/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_star_field @ 0x434270 */
/* selector: destroy_star_field */

// Destroys the live star-field sprite pool, tears down its per-entry records, and returns the controller to state 0. This is a void lifecycle edge; its sole Windows caller discards the incidental count left in EAX. Cross-port Android symbols match this exact member to `cRStarManager::UnInit()`.
void __thiscall destroy_star_field(StarManager *manager)
{
  int32_t v2; // ebx
  int v3; // edi

  v2 = 0;
  if ( manager->count <= 0 )
  {
    manager->state = 0;
  }
  else
  {
    v3 = 0;
    do
    {
      manager->entries[v3].active = 0;
      kill_sprite((int)manager->entries[v3].sprite);
      ++v2;
      ++v3;
    }
    while ( v2 < manager->count );
    manager->state = 0;
  }
}
