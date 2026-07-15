/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_star_field @ 0x434670 */
/* selector: hide_star_field */

// Clears bit 0x40 on every live star-field sprite, hiding the background star pass without destroying its controller state. All six Windows callers discard the incidental loop value in EAX, proving this exact lifecycle member is void. Cross-port Android and iOS symbols match it to `cRStarManager::Hide()`.
void __thiscall hide_star_field(StarManager *manager)
{
  int32_t v1; // edx
  int v2; // esi
  Sprite *sprite; // eax

  if ( manager->state )
  {
    v1 = 0;
    if ( manager->count > 0 )
    {
      v2 = 0;
      do
      {
        sprite = manager->entries[v2++].sprite;
        ++v1;
        sprite->flags &= ~0x40u;
      }
      while ( v1 < manager->count );
    }
  }
}
