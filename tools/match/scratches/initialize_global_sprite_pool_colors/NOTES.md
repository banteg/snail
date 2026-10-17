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

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs the sprite pool in
`g_sprite_manager`, whose 3000 `cRSprite` elements each construct their `color`
member. Their original source is that global's definition, as with RMaths'
`TransformMatrix g_identity_matrix(1.0f)`, and the explicit wrapper and loop
here are stand-ins for it.

VC6 emits this construction only when `tColour` declares its default
constructor (the folded identity body at `0x44db50`). Declaring `tColour();` in
`sprite.h` breaks 118 currently exact functions in the whole-TU build: G0 and
Mouse stop compiling, and 48 functions in Border, Game, SubGame, Font, Path and
other units regress. Those functions still spell `tColour` construction
explicitly through `noop_this_constructor` and the pointer-returning four-float
`Set`. The explicit form stays until `tColour`'s constructors and those callers
are recovered together.
