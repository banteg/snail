# request_object_vertex_colours @ 0x42f850

Exact match with `END=0x42f89d`; the default manifest gap continues through
padding and a following uncurated thunk.

Semantics:

- allocates `vertex_count * sizeof(Color4f)` for `vertex_colours` at `+0x48`;
- initializes the RGB lanes of every colour record to `1.0f`;
- intentionally leaves alpha untouched, matching native.

Source-shape note: the pretest `while (i < vertex_count)` form preserves the
native loop-counter zeroing before the empty-count branch. The equivalent
`if`/`do while` form delays `xor ecx, ecx` until after the branch and leaves a
one-instruction ordering residual.

2026-07-14 allocation ownership: the color bank now derives its 16-byte stride
from `Color4f`. Matching remains exact at 30/30 instructions with both operands
clean.
