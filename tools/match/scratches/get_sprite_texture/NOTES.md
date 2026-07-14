# get_sprite_texture

Small sprite texture-table accessor at 0x44e570. Returns the registered texture
pointer from the shared table at 0x78ff90.

Exact match: 100.00%, 3/3 instructions, with the sprite texture table operand
audited through `g_sprite_texture_table`.

The sole Windows caller loads `g_sprite_manager @ 0x790f30` into `ecx`, and
iOS names this accessor `cRSpriteManager::GetTexture(int)`. The body now uses
that real method owner and returns the canonical borrowed `TextureRef*`; it
remains exact at 3/3 with the table operand resolved even though the receiver
is not needed for Windows' separate global table.
