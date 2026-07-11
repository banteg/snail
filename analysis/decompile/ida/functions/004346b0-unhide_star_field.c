/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_star_field @ 0x4346b0 */
/* selector: unhide_star_field */

// Sets bit 0x40 on every live star-field sprite, re-enabling the background streak pass without rebuilding the controller.
int32_t __thiscall unhide_star_field(StarManager *manager)
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
        sprite->flags |= 0x40u;
        result = manager->count;
      }
      while ( v2 < result );
    }
  }
  return result;
}

