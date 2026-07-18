/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sprite_manager @ 0x44e160 */
/* selector: initialize_sprite_manager */

// Initializes the global sprite manager, its sprite pool, and free-list heads; iOS RSprite.o names this `cRSpriteManager::Init()`.
void __thiscall initialize_sprite_manager(SpriteManager *manager)
{
  int v2; // edi
  char *v3; // ebp

  manager->paused = 0;
  manager->active_heads[0] = nullptr;
  manager->active_heads[1] = nullptr;
  manager->active_heads[2] = nullptr;
  manager->active_heads[3] = nullptr;
  v2 = 0;
  manager->active_heads[4] = nullptr;
  manager->free_head = manager->sprites;
  do
  {
    v3 = (char *)manager + 180 * v2;
    initialize_sprite((Sprite *)(v3 + 4));
    if ( v2 )
    {
      if ( v2 == 2999 )
      {
        manager->sprites[2999].prev = &manager->sprites[2998];
        manager->sprites[2999].next = nullptr;
      }
      else
      {
        *((_DWORD *)v3 + 5) = v3 - 176;
        *((_DWORD *)v3 + 4) = v3 + 184;
      }
    }
    else
    {
      manager->sprites[0].prev = nullptr;
      manager->sprites[0].next = &manager->sprites[1];
    }
    ++v2;
  }
  while ( v2 < 3000 );
}
