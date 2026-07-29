/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_sprite_texture @ 0x44e570 */
/* selector: get_sprite_texture */

// Returns the texture object for a manager texture id; iOS RSprite.o names this `cRSpriteManager::GetTexture(int)`.
cRTexture *__thiscall get_sprite_texture(cRSpriteManager *manager, int32_t texture_id)
{
  return *(&g_sprite_texture_table + texture_id);
}
