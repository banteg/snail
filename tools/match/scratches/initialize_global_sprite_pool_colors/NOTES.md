# initialize_global_sprite_pool_colors @ 0x44de50

Startup constructs exactly 3000 `Sprite::color` subobjects inside
`g_sprite_manager`. The first receiver is manager `+0x30` (`sprites + 0x2c`),
then advances by the exact `sizeof(Sprite) == 0xb4` stride. Together with the
manager layout assertion, the loop directly proves ownership of the complete
fixed sprite pool.
