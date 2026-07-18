/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_game_sprites @ 0x44e3d0 */
/* selector: kill_game_sprites */

// Kills all nonpersistent gameplay sprites while preserving manager state; iOS RSprite.o names this `cRSpriteManager::KillGame()`.
void __thiscall kill_game_sprites(SpriteManager *manager)
{
  Sprite **v1; // edi
  Sprite *v2; // ecx
  Sprite *next; // esi

  v1 = g_sprite_active_heads;
  do
  {
    v2 = *v1;
    if ( *v1 )
    {
      do
      {
        next = v2->next;
        if ( (v2->flags & 0x800) != 0 )
          kill_sprite(v2);
        v2 = next;
      }
      while ( next );
    }
    ++v1;
  }
  while ( (int)v1 < (int)&g_sprite_free_head );
}
