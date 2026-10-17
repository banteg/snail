# initialize_track_colour_bank_d

CRT constructor body at `0x4349f0` for Windows' second physical 51-entry Slide
bank. Android and iOS address their one original `gLocColourLookupSlide` owner
for both corresponding `BuildColours` calls, but the Windows addresses are
distinct and remain modeled as `slide_0` and `slide_1`. The D suffix remains
only as the stable CRT-table identity. The loop matches the native 12/12
instructions exactly, with both masked operands resolved.

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs `tColour
g_loc_colour_lookup_slide_1[TRACK_COLOUR_BANK_CAPACITY]`. Their original source
is that global's definition, as with RMaths' `TransformMatrix
g_identity_matrix(1.0f)`, and the explicit wrapper and loop here are stand-ins
for it.

VC6 emits this construction only when `tColour` declares its default
constructor (the folded identity body at `0x44db50`). Declaring `tColour();` in
`sprite.h` breaks 118 currently exact functions in the whole-TU build: G0 and
Mouse stop compiling, and 48 functions in Border, Game, SubGame, Font, Path and
other units regress. Those functions still spell `tColour` construction
explicitly through `noop_this_constructor` and the pointer-returning four-float
`Set`. The explicit form stays until `tColour`'s constructors and those callers
are recovered together.
