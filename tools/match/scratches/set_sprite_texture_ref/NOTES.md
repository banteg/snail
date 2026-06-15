# set_sprite_texture_ref

Small sprite mutator at 0x44e550. Selects one frame from the shared sprite
texture table at 0x78ff90 using the native `0xa4` frame stride, stores it at
sprite offset `0x1c`, and returns that selected frame pointer.

Exact match: 100.00%, 8/8 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.
