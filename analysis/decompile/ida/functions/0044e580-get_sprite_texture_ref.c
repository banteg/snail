/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_sprite_texture_ref @ 0x44e580 */
/* selector: get_sprite_texture_ref */

// Returns the borrowed TGA header and inline pixel payload at `TextureRef::texture_ref +0x98` for one manager texture id. iOS and Android distinguish this as `cRSpriteManager::GetTga(int)`; their separate `GetTextureRef(int)` accessor instead returns record `+0x8c`.
void *__thiscall get_sprite_texture_ref(SpriteManager *manager, int32_t texture_id)
{
  return (*(&g_sprite_texture_table + texture_id))->texture_ref;
}
