# get_sprite_texture

Small sprite texture-table accessor at 0x44e570. Returns the registered texture
pointer from the shared table at 0x78ff90.

Exact match: 100.00%, 3/3 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.
