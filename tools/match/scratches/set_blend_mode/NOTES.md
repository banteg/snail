# set_blend_mode

Object blend preset mapper at `0x412d00`.

Current Wibo result: 81.52%, 92/92 instructions, prefix 14/92, masked operands
14 ok, 0 unresolved, 1 mismatch.

Recovered relationships:

- Uses `set_blend_mode_lookup_table` at `0x412e30` to map authored blend modes
  `0..20` onto six compact switch cases.
- Programs Direct3D render states `0x1b`, `0x13`, and `0x14`.
- Lookup case `5` and out-of-range values return the original blend mode
  without touching render state.

Expected residuals:

- The source-shaped sparse switch correctly regenerates the compiler byte
  lookup/table idiom, but VC6 picks a different tail-sharing owner for the two
  identical `src=5, dest=6` blend cases.
- The lookup bytes are content-audited and match. The remaining masked operand
  mismatch is the jump table; do not hide it with convenience aliases unless the
  target label evidence is recovered independently.

`render_object` calls this helper before applying the object tint and grouped
draw call.
