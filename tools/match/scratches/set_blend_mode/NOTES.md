# set_blend_mode

Object blend preset mapper at `0x412d00`.

Current Wibo result: 92.39%, 92/92 instructions, prefix 2/92, masked operands
15 ok, 0 unresolved, 1 mismatch.

Recovered relationships:

- Uses `set_blend_mode_lookup_table` at `0x412e30` to map authored blend modes
  `0..20` onto six compact switch cases.
- Programs Direct3D render states `0x1b`, `0x13`, and `0x14`.
- Lookup case `5` and out-of-range values return the original blend mode
  without touching render state.

Expected residuals:

- The source-shaped sparse switch correctly regenerates the compiler byte
  lookup/table idiom. The retained source now spells the decompiler's shared
  `dest=6` suffix explicitly with `source_blend`, which fixes the previous
  wrong tail-sharing owner for the two `src=5, dest=6` groups.
- The lookup bytes are content-audited and match. The remaining masked operand
  mismatch is the jump table; do not hide it with convenience aliases unless the
  target label evidence is recovered independently.
- Native pushes the source blend immediate before entering the shared suffix;
  the retained explicit suffix keeps that value in a register instead. A narrower
  pair of immediate-valued `goto` labels regressed back to 81.52% by letting VC6
  choose the old wrong full-block owner, so keep the `source_blend` spelling.
- 2026-06-20 render-state family audit: rechecked the literal source-blend call
  plus shared destination suffix against the current headers. It still regresses
  to 78.26%, duplicating the wrong full blocks and dropping two masked
  references, so the `source_blend` local remains the best source-shaped owner
  for the native shared `dest=6` suffix. Replacing the shared
  `direct3d_device8_view.h` include with a local narrow device/vtable view is
  codegen-neutral at 92.39% and leaves the same jump-table masked mismatch.

`render_object` calls this helper before applying the object tint and grouped
draw call.
