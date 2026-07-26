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
artifact retain the canonical `Object* object` receiver. Matching remains
exact; the later mobile owner replay below resolves that ABI-equivalent helper
as an authored member.

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

## 2026-07-24 paired IDA ownership replay

The object-render replay now applies the exact
`void __fastcall request_object_vertex_colours(Object*)` ABI to the tracked
IDA database. IDA now agrees with Binary Ninja that the allocation populates
the canonical Object-owned `tColour* vertex_colours` bank and that the loop
uses `Object::vertex_count`. This retires the stale
`PathTemplateStripMesh`/`Color4f` owner shell without altering the exact
matcher source or inventing an alpha write.

## 2026-07-26 Android owner and source recovery

Android exposes the exact-demangled `cRObject::RequestColours()` method and an
equivalent body: one 16-byte colour per vertex, RGB initialized to 1.0, and
alpha deliberately untouched. This resolves the Windows fastcall-equivalent
helper as an authored `Object` member. Rewriting the canonical scratch as
`void Object::request_object_vertex_colours()` remains byte-exact at 30/30
instructions with two clean operands, and its exact `request_object_vertices`
caller also accepts the member spelling.

The difficult worm-path constructor is a source-shape exception, not an
ownership exception: changing that call site to member syntax collapses its
VC6 register and temporary plan and broadly reschedules the function despite a
coincidentally unchanged aggregate score. It therefore retains a local
fastcall-compatible declaration until that caller's unresolved source shape is
recovered.
