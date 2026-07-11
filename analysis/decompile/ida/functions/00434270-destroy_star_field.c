/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_star_field @ 0x434270 */
/* selector: destroy_star_field */

// Destroys the live star-field sprite pool, tears down its per-entry records, and returns the controller to state 0.
int32_t __thiscall destroy_star_field(StarManager *manager)
{
  int32_t v2; // ebx
  int32_t result; // eax
  int v4; // edi

  v2 = 0;
  result = manager->count;
  if ( result <= 0 )
  {
    manager->state = 0;
  }
  else
  {
    v4 = 0;
    do
    {
      manager->entries[v4].active = 0;
      kill_sprite((int)manager->entries[v4].sprite);
      result = manager->count;
      ++v2;
      ++v4;
    }
    while ( v2 < result );
    manager->state = 0;
  }
  return result;
}

