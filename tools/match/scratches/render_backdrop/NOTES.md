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

## 2026-07-27 dual-mobile Render boundary

Android `cRBackdrop::Render()` at `0x0003e194` and iOS
`cRBackdrop::Render()` at `0x00041350` close the authored identity of Windows
`0x00411040`; the manifest now exposes `cRBackdrop_Render` as an exact alias.
Both ports independently confirm the void member ABI, the Backdrop-owned
distortion grid, the nested grid traversal, and the flip-controlled UV lane.

The platform render boundary is intentionally different. Android and iOS fill
their own `cGLVertexUV` buffers and submit them once through
`G0RenderBackdrop`; Windows traverses its fixed 8x8 distortion-cell grid and
queues each of the 7x7 quads through `queue_textured_quad_corners`. Mobile
loop bounds, vertex strides, field offsets, and the final renderer call
therefore do not transfer to Windows. No matcher source or mask changed: the
focused Windows receipt remains 86.61%, 189/192 candidate instructions,
prefix 12/192, with 27 clean operands, no unresolved or mismatched operands,
and three explicitly unaudited constant loads.

## 2026-07-29 branch-local lifetime recovery

The native branch schedule is recovered through source ownership rather than
volatile or address-forcing fakematches:

- Moving the distortion-cell pointer into each render branch, immediately
  after `next_row`, raises the focused result from 86.61% to 90.91% and moves
  the exact prefix from 12 to 21 instructions.
- Declaring the coordinate calculations as `right_y`, `left_x`, `right_x`,
  then `left_y` in both branches raises the result to 92.99% and makes the
  entire normal branch exact through instruction 102. All 24 declaration
  orders for the flipped branch were tested; none improved that residual.
- Giving the four coordinate objects one lifetime across both branches makes
  the flipped branch use the same native stack slots as the normal branch.
  This raises the result to 99.22%, extends the exact prefix to 174/192, and
  leaves all 28 aligned references clean. Eight plausible shared declaration
  orders compile to the same binary, so the retained order follows the
  calculation order.

The only residual is the inner-loop comparison. Native reloads `next_column`
once and uses non-popping `fcom 7.0`; VC6 reloads the same slot twice and uses
`fcomp`, leaving a 193-instruction candidate against 192 native instructions
and two corresponding unaudited constant operands. Five trailing bounded
sweeps cover direct `column`/`next_column` condition owners, declaration scope,
assignment expressions, coordinated condition hoisting, and explicit
pre-branch `next_column` ownership. Across 36 variants, 12 are byte-neutral,
10 regress, and 14 are unavailable lexical-scope combinations. With no
improvement, the experiment ledger records this one-instruction tail;
the evidence-backed 99.22% source remains open to genuinely new evidence.

## 2026-07-30 compare-reference proof

The masked-reference audit now aligns x87 `fcom`/`fcomp` variants only within
their own compare family, requiring the same memory width, canonical reference,
and sequence order. A regression test keeps compare instructions distinct from
ordinary `fld`/`mov` loads.

That closes the two one-sided `7.0f` entries without normalizing away the real
stack-scheduling difference. The retained source remains 99.22%, 193/192
candidate/target instructions, and prefix 174/192; all 29 aligned references
are now clean. The extra reload plus popping compare remain the intentionally
visible byte residual.
