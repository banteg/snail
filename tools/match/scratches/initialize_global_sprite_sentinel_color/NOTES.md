# initialize_global_sprite_sentinel_color @ 0x44de80

Startup constructs `g_sprite_sentinel.color` at exact address
`0x814cb0 + offsetof(Sprite, color) == 0x814cdc`, proving that the standalone
allocation sentinel owns a complete `Sprite` layout rather than an abbreviated
failure record.
