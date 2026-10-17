# initialize_global_temp_colour

CRT constructor body `0x42f8b0` passes the 16-byte global at `0x503308` to the
folded `tColour::noop_this_constructor` at `0x44db50`. No other Windows
instruction addresses its four lanes.

The symbol-preserving iOS v1.9 executable independently names the corresponding
16-byte owner `GTempColour`: `nm -n` places it at `0x2adfac`, immediately before
`gEdgeStore` at `0x2adfbc`. The matching type, extent, engine-object provenance,
and absence of a stronger consumer support the recovered Windows name without
inventing a more specific role.

The source matches the native 2/2 instructions exactly, with both the global
owner and folded constructor operands resolved.

## 2026-08-12 source-unit provenance

The symbol-preserving iOS inventory assigns the exact `GTempColour` global to
`RObject.o`. Live Windows xrefs show that this constructor is the sole code
reference to the corresponding 16-byte global at `0x503308`, and neighboring
verified Windows functions are also from `RObject.o`. This recovers the
Windows constructor's source object without claiming a mobile function map.

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
