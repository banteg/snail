/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_sprite_texture @ 0x44e0f0 */
/* selector: register_sprite_texture */

// Registers or reuses one sprite texture reference; iOS RSprite.o names this manager family `cRSpriteManager::Load(char*, int, int)` and also exposes the adjacent `LoadSet` variant.
TextureRef *__thiscall register_sprite_texture(
        SpriteManager *manager,
        char *texture_path,
        int32_t texture_id,
        int32_t flags)
{
  char *v4; // eax
  char v5; // cl
  TextureRef *texture_ref; // eax
  TextureRef *result; // eax

  v4 = texture_path;
  if ( *texture_path != 46 )
  {
    do
      v5 = *++v4;
    while ( v5 != 46 );
  }
  if ( texture_id >= 1000 )
    report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h", 1000);
  texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, flags);
  *(&g_sprite_texture_table + texture_id) = texture_ref;
  texture_ref->flags |= flags;
  result = *(&g_sprite_texture_table + texture_id);
  result->frame_count = 0;
  return result;
}
