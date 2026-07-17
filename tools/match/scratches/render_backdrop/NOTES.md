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
  `int` declaration for normal users while this scratch opts into the
  likely-void `render_backdrop` declaration with
  `BACKDROP_RENDER_BACKDROP_RETURNS_VOID`.
- 2026-06-20: `backdrop.h` now spells that conditional return through a single
  macro-expanded declaration, so each preprocessed scratch still receives the
  same `void`/`int` prototype as before without presenting two competing
  `Backdrop::render_backdrop` declarations to `snail match types`. Focused Wibo
  remains `85.56%`, `189/192`, with the same two constant-lane masked
  mismatches.
- 2026-06-21 coordinate-lane sweep: a small permutation sweep over the branch
  local coordinate declaration order found that declaring `left_x` before
  `right_y` in both render branches improves focused Wibo from `85.56%` to
  `86.61%`, keeps the candidate at `189/192` instructions, and clears the two
  previous masked constant-lane mismatches (`26 ok`, no unresolved or
  mismatched operands). The remaining first mismatch is still the branch-invariant
  coordinate hoist before the `active_flip` test and the duplicated flipped-path
  stack-slot schedule; `volatile`/direct `active_flip` spellings either regressed
  or were neutral.
- 2026-06-21 common-tail retry: refactoring the two render branches to set only
  UV/color locals and share one corner calculation plus one
  `queue_textured_quad_corners` call matches the IDA shape conceptually, but
  VC6 over-optimizes the source into a different frame/register layout. The
common-tail variants score only 41.46% and 38.53%, so the intentionally
duplicated branch calls remain the better compiler-shape evidence.

## 2026-07-14 distortion-grid extent derivation

The 7x7 quad bounds and cell-row multiplier now derive from the owned 8x8
distortion grid. The normalized listing remains byte-identical
(`112316678a1762b5135e27a350402ae953dd0d86d18baf2ffff2ac820acc2c40`)
at the honest 86.61% result (`189/192`, prefix `12/192`, 26 clean operands).

## 2026-07-15 IDA backdrop receiver ownership

The shared exact-size `Backdrop` declaration now replays into IDA as well as
Binary Ninja. The tracked decompile names the `active_flip` and texture owner
through a real `Backdrop *` receiver instead of `int this` arithmetic. This is
analysis-only: the honest result remains 86.61% at 189/192 instructions, with
26 clean operands and no masked-operand mismatches.

## 2026-07-17 Binary Ninja consumer ABI closure

A guarded preview and persisted replay now give the three remaining Backdrop
consumers their real receiver owner. `render_backdrop` keeps the cross-port
authored `void __thiscall` contract, while `draw_split_backdrop` and Windows'
folded `update_backdrop` retain their observed `int32_t` results. This removes
scalar fastcall views without pretending the Windows update result is void.
No matcher source changed; the honest 86.61% render result remains visible.
