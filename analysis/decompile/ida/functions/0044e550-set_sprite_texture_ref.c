/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_sprite_texture_ref @ 0x44e550 */
/* selector: set_sprite_texture_ref */

// Assigns one sprite's texture reference and frame metadata from a manager texture id; iOS RSprite.o names this `cRSprite::SetTextureRef(int, int)`.
void __thiscall set_sprite_texture_ref(cRSprite *sprite, int32_t texture_id, int32_t frame)
{
  sprite->texture_ref = &(*(&g_sprite_texture_table + texture_id))[frame];
}
