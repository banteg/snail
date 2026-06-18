# render_backdrop

- Initial scratch for `render_backdrop @ 0x411040`.
- This is the 7x7 single-texture backdrop mesh renderer. It samples four
  neighboring `BackdropDistortCell::current_*_offset` pairs for each quad.
- The grid index is `row + 8 * column`; the renderer visits the same
  column-major layout updated by `update_backdrop`.
- The C source uses a `float*` view for the queue call because native keeps the
  pointer as `this + index * 0x18` and folds the `distort_cells +0x58` base into
  later offsets (`+0x68`, `+0x6c`, ...). A direct
  `&distort_cells[index]` version proved the same relationship but generated
  `+0x10`/`+0x14` style addressing instead.
- The UV arguments intentionally follow the native queue-helper order. In this
  function the first stored UV lane receives the row-derived value and the second
  receives the column-derived value; keep that shape unless the queue helper
  names are revised globally.
- Current Wibo result: 85.56%, 192 target instructions versus 189 candidate
  instructions, prefix 12/192, with 24 masked operands ok and no unresolved
  masks. The remaining residual is source-scheduler shape: VC6 hoists one
  common coordinate multiply ahead of the `active_flip` test while native loads
  `active_flip` first and keeps both render branches more duplicated.
- IDA presents `render_backdrop`, `draw_split_backdrop`, and `update_backdrop`
  as `void`, but changing the shared prototypes currently worsens
  `update_backdrop` codegen. The shared header therefore keeps the corpus-default
  `int` declaration while this scratch opts into the likely-void
  `render_backdrop` declaration with `BACKDROP_RENDER_BACKDROP_RETURNS_VOID`.
