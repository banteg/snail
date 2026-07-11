/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_star_field @ 0x434670 */
/* selector: hide_star_field */

// Clears bit 0x40 on every live star-field sprite, hiding the background star pass without destroying its controller state.
int32_t __thiscall hide_star_field(StarManager *manager)
{
  int32_t result; // eax
  int32_t v2; // edx
  int v3; // esi
  Sprite *sprite; // eax

  result = manager->state;
  if ( result )
  {
    result = manager->count;
    v2 = 0;
    if ( result > 0 )
    {
      v3 = 0;
      do
      {
        sprite = manager->entries[v3++].sprite;
        ++v2;
        sprite->flags &= ~0x40u;
        result = manager->count;
      }
      while ( v2 < result );
    }
  }
  return result;
}

