# request_object_vertex_colours @ 0x42f850

Exact match with `END=0x42f89d`; the default manifest gap continues through
padding and a following uncurated thunk.

Semantics:

- allocates `vertex_count * sizeof(tColour)` for `vertex_colours` at `+0x48`;
- initializes the RGB lanes of every colour record to `1.0f`;
- intentionally leaves alpha untouched, matching native.

Source-shape note: the pretest `while (i < vertex_count)` form preserves the
native loop-counter zeroing before the empty-count branch. The equivalent
`if`/`do while` form delays `xor ecx, ecx` until after the branch and leaves a
one-instruction ordering residual.

2026-07-14 allocation ownership: the color bank now derives its 16-byte stride
from `tColour`. Matching remains exact at 30/30 instructions with both operands
clean.

2026-07-15 Binary Ninja replay: the live fastcall prototype and tracked
artifact now retain the canonical `Object* object` receiver. Matching remains
exact.

## 2026-07-23 colour-bank byte-cursor replay

The guarded vertex-storage replay now preserves the allocation as the
Object-owned `tColour* vertex_colours` bank and the native EAX walk as an
integer `colour_byte_offset`. The loop writes only the `r`, `g`, and `b` lanes
at offsets 0, 4, and 8 and advances by `sizeof(tColour) == 0x10`; alpha remains
intentionally untouched. Native MLIL never materializes a per-colour pointer,
so the replay does not invent one.

The replay verifies `tColour` at 0x10, `Object` at 0xdc, and the colour/count
fields before mutation, saves and reads back all annotations, and is fully
idempotent. The matcher remains unchanged at 100.00%, 30/30 instructions,
prefix 30/30, with two clean masked operands.
