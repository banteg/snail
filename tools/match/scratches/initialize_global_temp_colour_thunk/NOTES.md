# initialize_global_temp_colour_thunk

CRT table entry `0x4a1028` points to this one-instruction thunk at `0x42f8a0`,
which tail-jumps over 11 alignment nops to the adjacent `GTempColour`
constructor. The source-level tail call matches the native 1/1 instruction
exactly, with its target resolved.

The direct CRT edge carries the constructor's exact iOS global provenance:
`GTempColour` belongs to `RObject.o`, so this one-hop startup thunk does too.

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs `tColour
g_temp_colour`. Their original source is that global's definition, as with
RMaths' `TransformMatrix g_identity_matrix(1.0f)`, and the explicit wrapper and
loop here are stand-ins for it.

VC6 emits this construction only when `tColour` declares its default
constructor (the folded identity body at `0x44db50`). Declaring `tColour();` in
`sprite.h` breaks 118 currently exact functions in the whole-TU build: G0 and
Mouse stop compiling, and 48 functions in Border, Game, SubGame, Font, Path and
other units regress. Those functions still spell `tColour` construction
explicitly through `noop_this_constructor` and the pointer-returning four-float
`Set`. The explicit form stays until `tColour`'s constructors and those callers
are recovered together.
