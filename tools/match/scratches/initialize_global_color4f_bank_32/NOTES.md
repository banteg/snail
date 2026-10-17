# initialize_global_color4f_bank_32

CRT constructor body `0x410c10` walks 32 `tColour` records from `0x4f6e50` at
stride `0x10` and calls the folded no-op constructor at `0x44db50`. The loop's
`0x200`-byte extent ends exactly where `g_sprite_depth_buckets` begins; the
preceding `g_sprite_depth_nodes` allocation ends exactly at its base.

An exhaustive absolute-reference scan found no address of the bank or any of
its 31 later elements outside this constructor. The allocation therefore keeps
a structural name: adjacency alone does not prove backdrop, sprite-manager, or
other class ownership.

The recovered loop matches all 12 native instructions exactly, with both the
global base and folded constructor operands resolved.

## 2026-08-12 source-unit provenance

The constructor run is physically bounded by two independently verified
`Game.o` bodies: Windows `cRPlayer::AI()` ends before the CRT thunk, and
`cRBackdrop::SetZoom(float)` begins immediately after the constructor body.
The matching Android and iOS methods on both sides retain those exact authored
owners in `Game.o`, recovering the Windows loop's compilation unit as
`Game.o`.

This does not narrow the unused bank to cRPlayer, cRBackdrop, or any other
class. The exhaustive Windows reference result still requires the structural
`g_color4f_bank_32` name. The exact 12/12 body is unchanged.

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs `tColour
g_color4f_bank_32[GLOBAL_COLOR4F_BANK_CAPACITY]`. Their original source is that
global's definition, as with RMaths' `TransformMatrix g_identity_matrix(1.0f)`,
and the explicit wrapper and loop here are stand-ins for it.

VC6 emits this construction only when `tColour` declares its default
constructor (the folded identity body at `0x44db50`). Declaring `tColour();` in
`sprite.h` breaks 118 currently exact functions in the whole-TU build: G0 and
Mouse stop compiling, and 48 functions in Border, Game, SubGame, Font, Path and
other units regress. Those functions still spell `tColour` construction
explicitly through `noop_this_constructor` and the pointer-returning four-float
`Set`. The explicit form stays until `tColour`'s constructors and those callers
are recovered together.
