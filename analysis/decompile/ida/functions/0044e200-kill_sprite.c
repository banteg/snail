/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_sprite @ 0x44e200 */
/* selector: kill_sprite */

// Unlinks and returns one live sprite to the manager free list; iOS RSprite.o names this `cRSprite::Kill()`.
void __thiscall kill_sprite(Sprite *sprite)
{
  Sprite *next; // eax
  Sprite *prev; // eax
  Sprite *v4; // eax

  if ( (sprite->flags & 1) == 0 )
    report_errorf("Sprite kill error, already dead (%s)", sprite->texture_ref->name);
  if ( sprite != (Sprite *)&g_sprite_sentinel )
  {
    sprite->flags &= ~1u;
    if ( sprite == g_sprite_active_heads[sprite->owner] )
    {
      next = sprite->next;
      if ( next )
        next->prev = nullptr;
      g_sprite_active_heads[sprite->owner] = sprite->next;
      sprite->next = (Sprite *)g_sprite_free_head;
      g_sprite_free_head = sprite;
    }
    else
    {
      prev = sprite->prev;
      if ( prev )
        prev->next = sprite->next;
      v4 = sprite->next;
      if ( v4 )
        v4->prev = sprite->prev;
      sprite->next = (Sprite *)g_sprite_free_head;
      g_sprite_free_head = sprite;
    }
  }
}
