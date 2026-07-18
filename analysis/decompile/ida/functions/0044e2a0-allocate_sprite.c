/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_sprite @ 0x44e2a0 */
/* selector: allocate_sprite */

// Allocates one sprite from the manager free list, assigns texture ids, and links it into the selected active bucket; iOS RSprite.o names this `cRSpriteManager::New(int, int, int, int)`.
Sprite *__thiscall allocate_sprite(
        SpriteManager *manager,
        int32_t owner,
        int32_t texture_id,
        int32_t texture_a,
        int32_t texture_b)
{
  Sprite *free_head; // esi
  Sprite *v7; // eax
  int v8; // ecx
  int v9; // edi
  SpriteFlag v10; // ecx

  free_head = manager->free_head;
  if ( !free_head )
    return (Sprite *)&g_sprite_sentinel;
  manager->free_head = free_head->next;
  free_head->owner = owner;
  v7 = manager->active_heads[owner];
  if ( v7 )
    v7->prev = free_head;
  free_head->prev = nullptr;
  free_head->next = manager->active_heads[owner];
  manager->active_heads[owner] = free_head;
  initialize_sprite(free_head);
  v8 = (1 << (owner + 24)) | free_head->flags;
  free_head->flags = v8;
  free_head->texture_ref = *(&g_sprite_texture_table + texture_id);
  if ( texture_b == -1 )
  {
    if ( texture_a != -1 )
    {
      free_head->flags = v8 | 0x10;
      free_head->texture_ref_a = *(&g_sprite_texture_table + texture_a);
    }
  }
  else
  {
    free_head->flags = v8 | 0x20;
    free_head->texture_ref_a = *(&g_sprite_texture_table + texture_a);
    free_head->texture_ref_b = *(&g_sprite_texture_table + texture_b);
  }
  free_head->size_end = 0.0;
  free_head->texture_id = texture_id;
  free_head->frame_progress = 0.0;
  free_head->frame_progress_step = 0.0;
  free_head->frame_count = (*(&g_sprite_texture_table + texture_id))->frame_count;
  if ( ((*(&g_sprite_texture_table + texture_id))->flags & 0x2000) != 0 )
  {
    v9 = free_head->flags | 0x2000;
    free_head->flags = v9;
    v10 = v9;
    free_head->frame_progress_step = (*(&g_sprite_texture_table + texture_id))->frame_progress_step;
    if ( ((*(&g_sprite_texture_table + texture_id))->flags & 0x4000) != 0 )
    {
      BYTE1(v10) = BYTE1(v9) | 0x40;
      free_head->flags = v10;
    }
  }
  return free_head;
}
