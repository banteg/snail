# set_sprite_texture_ref

Small sprite mutator at 0x44e550. Selects one frame from the shared sprite
texture table at 0x78ff90 using the native `0xa4` frame stride and stores it at
sprite offset `0x1c`.

Exact match: 100.00%, 8/8 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.

2026-07-13 Binary Ninja ownership repair: the live database had retained the
`Sprite*` prototype but degraded both `Sprite` and `TextureRef` to zero-sized
forward declarations. The guarded star/sprite replay now checks their exact
`0xb4` and `0xa4` extents before selectively restoring them. Live pseudocode
again expresses the native `0xa4` indexing as
`g_sprite_texture_table[texture_id][frame]`, stores through
`sprite->texture_ref`, and returns `TextureRef*`; a second replay is a complete
no-op.

## 2026-07-29 authored method and return contract

Android and iOS independently preserve
`cRSprite::SetTextureRef(int, int)` and decompile it as `void`. Every recovered
Windows caller also discards EAX. Spelling the Windows method as `void` and
removing the explicit source return still compiles to the same 8/8 native
instructions: VC6 incidentally leaves the selected `cRTexture*` in EAX after
the final store. The primary matcher API now uses the authored name and void
contract; the older analysis prototype above remains only as historical replay
evidence.
