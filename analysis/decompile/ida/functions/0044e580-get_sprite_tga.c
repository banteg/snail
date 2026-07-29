/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_sprite_tga @ 0x44e580 */
/* selector: get_sprite_tga */

// Returns the borrowed TGA header and inline pixel payload at `TextureRef::texture_ref +0x98` for one manager texture id. Its sole Windows caller, `border_mouse_test`, reads the TGA width and height at `+0x0c/+0x0e` before sampling the inline pixels at `+0x12`. iOS and Android distinguish this as `cRSpriteManager::GetTga(int)`; their separate `GetTextureRef(int)` accessor instead returns record `+0x8c`.
TgaImageView *__thiscall get_sprite_tga(cRSpriteManager *manager, int32_t texture_id)
{
  return (TgaImageView *)(*(&g_sprite_texture_table + texture_id))->texture_ref;
}
