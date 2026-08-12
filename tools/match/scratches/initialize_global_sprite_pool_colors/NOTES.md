# initialize_global_sprite_pool_colors @ 0x44de50

Startup constructs exactly 3000 `Sprite::color` subobjects inside
`g_sprite_manager`. The first receiver is manager `+0x30` (`sprites + 0x2c`),
then advances by the exact `sizeof(Sprite) == 0xb4` stride. Together with the
manager layout assertion, the loop directly proves ownership of the complete
fixed sprite pool.

## 2026-08-12 source-unit provenance

The symbol-preserving iOS inventory assigns the exact global
`gRSpriteManager` to `RSprite.o`. Windows initializes the color lane inside
that recovered cRSpriteManager owner, and live xrefs show this startup loop is
the sole reference to its first color subobject. This recovers the constructor
source object without claiming a mobile function map.
