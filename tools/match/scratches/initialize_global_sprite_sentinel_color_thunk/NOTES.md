# initialize_global_sprite_sentinel_color_thunk @ 0x44de70

CRT constructor-table entry at `0x4a1070`. The shipped function is a tail jump
to the adjacent initializer for the standalone allocation-sentinel color.

The direct CRT edge carries the exact `gSpriteDummy` provenance from the
constructor body; iOS assigns that sentinel global to `RSprite.o`.

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
