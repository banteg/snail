/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_game_sprites @ 0x44e3d0 */
/* selector: kill_game_sprites */

void kill_game_sprites()
{
  int *bucket; // edi
  int sprite; // ecx
  int next; // esi

  bucket = g_sprite_active_heads;
  do
  {
    sprite = *bucket;
    if ( *bucket )
    {
      do
      {
        next = *(_DWORD *)(sprite + 12);
        if ( (*(_DWORD *)(sprite + 4) & 0x800) != 0 )
          kill_sprite(sprite);
        sprite = next;
      }
      while ( next );
    }
    ++bucket;
  }
  while ( (int)bucket < (int)&g_sprite_free_head );
}
