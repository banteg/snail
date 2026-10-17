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

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs `cRSprite
g_sprite_sentinel`, whose implicit constructor constructs its `color` member.
Their original source is that global's definition, as with RMaths'
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
