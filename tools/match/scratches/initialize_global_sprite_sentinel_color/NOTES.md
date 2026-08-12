# initialize_global_sprite_sentinel_color @ 0x44de80

Startup constructs `g_sprite_sentinel.color` at exact address
`0x814cb0 + offsetof(Sprite, color) == 0x814cdc`, proving that the standalone
allocation sentinel owns a complete `Sprite` layout rather than an abbreviated
failure record.

## 2026-08-12 source-unit provenance

Windows `allocate_sprite` returns this sentinel when the free list is empty,
and `kill_sprite` excludes the same address. The iOS versions use exact global
`gSpriteDummy` in those two roles, and the symbol inventory assigns it to
`RSprite.o`. This establishes the Windows initializer's source unit without
transferring the mobile layout.
