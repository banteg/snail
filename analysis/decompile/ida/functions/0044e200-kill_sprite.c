/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_sprite @ 0x44e200 */
/* selector: kill_sprite */

// Unlinks and returns one live sprite to the manager free list; iOS RSprite.o names this `cRSprite::Kill()`.
void __thiscall kill_sprite(cRSprite *sprite)
{
  cRSprite *next; // eax
  cRSprite *prev; // eax
  cRSprite *v4; // eax

  if ( (sprite->flags & 1) == 0 )
    report_errorf("Sprite kill error, already dead (%s)", sprite->texture_ref->name);
  if ( sprite != (cRSprite *)&g_sprite_sentinel )
  {
    sprite->flags &= ~1u;
    if ( sprite == g_sprite_manager.active_heads[sprite->owner] )
    {
      next = sprite->next;
      if ( next != nullptr )
        next->prev = nullptr;
      g_sprite_manager.active_heads[sprite->owner] = sprite->next;
      sprite->next = g_sprite_manager.free_head;
      g_sprite_manager.free_head = sprite;
    }
    else
    {
      prev = sprite->prev;
      if ( prev != nullptr )
        prev->next = sprite->next;
      v4 = sprite->next;
      if ( v4 != nullptr )
        v4->prev = sprite->prev;
      sprite->next = g_sprite_manager.free_head;
      g_sprite_manager.free_head = sprite;
    }
  }
}
