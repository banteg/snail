# get_sprite_texture_ref

Small sprite texture-table accessor at 0x44e580. Returns the texture reference
stored at offset `0x98` inside the registered sprite texture record.

Exact match: 100.00%, 4/4 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.
