# get_sprite_texture_ref / cRSpriteManager::GetTga

Small sprite texture-table accessor at 0x44e580. Returns the texture reference
stored at offset `0x98` inside the registered sprite texture record.

Exact match: 100.00%, 4/4 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.

## 2026-07-14 TGA owner recovery

The stable Windows harness name predates the cross-port provenance. iOS and
Android distinguish three sprite-manager accessors: `GetTexture` returns the
texture record, `GetTextureRef` returns record `+0x8c`, and `GetTga` returns
record `+0x98`. This Windows helper returns `TextureRef::texture_ref` at
`+0x98`, and `cRBorder::MouseTest()` consumes it as an inline TGA header plus
pixels. The source is now the real `SpriteManager::get_sprite_tga()` member
with a borrowed `TgaImageView*` result. It remains exact at 4/4 instructions.
