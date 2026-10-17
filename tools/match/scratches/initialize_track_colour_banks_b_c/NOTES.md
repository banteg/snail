# initialize_track_colour_banks_b_c

CRT constructor body at `0x4349c0` for the 102-entry contiguous Windows owner
holding the 51-entry Floor bank followed by the first 51-entry Slide bank. The
mobile ports preserve these names as `gLocColourLookupFloor` and
`gLocColourLookupSlide`; Windows' single constructor proves that its two views
share one `0x660`-byte allocation. It invokes the folded no-op `tColour`
constructor across the complete owner before `build_track_colours` supplies the
authored white values. The B/C suffix remains only as the stable CRT-table
identity. The loop matches the native 12/12 instructions exactly, with both
masked operands resolved.

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs one 102-element
`tColour` array at `g_loc_colour_lookup_floor_slide_0` (a single loop of 102,
so one array rather than the two-member `TrackFloorSlideColourBanks` view,
whose implicit constructor would construct each member separately). Their
original source is that global's definition, as with RMaths' `TransformMatrix
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
