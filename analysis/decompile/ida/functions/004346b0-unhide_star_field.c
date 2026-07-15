/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_star_field @ 0x4346b0 */
/* selector: unhide_star_field */

// Sets bit 0x40 on every live star-field sprite, re-enabling the background streak pass without rebuilding the controller. Both Windows callers discard the incidental loop value in EAX, proving this exact lifecycle member is void. Cross-port Android and iOS symbols match it to `cRStarManager::UnHide()`.
void __thiscall unhide_star_field(StarManager *manager)
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
        sprite->flags |= 0x40u;
      }
      while ( v1 < manager->count );
    }
  }
}
