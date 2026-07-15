# update_backdrop @ 0x4112f0

Current scratch: 88.24% (67 target insns, 69 candidate insns), clean masks.

Advances the active backdrop distortion grid and dispatches the split or warped
draw path.

Recovered layout:

- the distortion update iterates columns first, rows second: outer stride
  `+0x18`, inner stride `+0xc0` (`8 * sizeof(BackdropDistortCell)`).
- `BackdropDistortCell::current_x_offset +0x10` is `sin(phase) * x_offset`.
- `BackdropDistortCell::current_y_offset +0x14` is `cos(phase) * y_offset`.
- `backdrop_change_queued +0x4c` is consumed here by calling
  `change_backdrop_real()` and then clearing the byte.
- rendering runs only when `active_primary_texture_id != -1` and
  `backdrop_render_enabled == 1`; `active_split_backdrop_pair` selects
  `draw_split_backdrop()` vs `render_backdrop()`.
- The 64 cells are also exposed as the owned row-major
  `BackdropDistortCell distort_grid[8][8]`. This updater traverses that matrix
  column-first (`+0x18` outer, `+0xc0` inner), while `set_backdrop_distort`
  seeds it row-first and `render_backdrop` samples it by `row + 8 * column`.
- `backdrop_render_enabled +0x658` is a persistent draw gate, not a refresh
  countdown: every writer stores only zero or one, and this function decrements
  a local copy solely to spell the native `value == 1` test.

Open source-shape issue: the bit-shadowed phase local recovers the native
8-byte frame and stack compare without using `volatile`, but VC6 still spills
with `fstp [esp+0x10]` followed by integer moves into the cell. Native emits the
tighter `fst [esp+0x10]; fstp [esi]; fld [esp+0x10]` sequence and stores the
sine-derived `current_x_offset` before preparing the cosine argument.

2026-06-21 phase-temporary sweep: address-taken locals, one-element arrays,
struct/union float holders, extra float copies, and explicit x/y offset locals
were neutral at 72.18% because VC6 scalar-replaced the temporary back onto the
x87 stack. A direct bit-shadowed cell store improves the focused score to
88.24% with one additional clean masked operand; the remaining gap is the
float-store scheduling above, not the frame shape.

2026-07-12 authored owner closure: iOS preserves `cRBackdrop::AI()` at
`0x41994` and `cRBackdrop::Render()` at `0x41350`; Android preserves them at
`0x323c0` and `0x319cc`. Mobile advances the distortion owner in `AI()` and
calls `Render()` separately from the game loop. Windows keeps the same
`cRBackdrop` owner but folds the split/single render dispatch into
`update_backdrop`. Replacing the raw float cursors with typed
`BackdropDistortCell*` traversal is codegen-neutral at 88.24% and makes the
shared grid ownership explicit.

## 2026-07-14 distortion-grid extent derivation

Both traversal counts and the column stride now derive from the owned 8x8
grid. The normalized listing remains byte-identical
(`b5b59c2093a28f393046d4be57d18a8987c73251700d05abc1d775a1684eae8f`)
at the honest 88.24% result (`69/67`, prefix `17/67`, seven clean operands).

## 2026-07-15 IDA backdrop receiver ownership

The shared exact-size `Backdrop` declaration now replays into IDA as well as
Binary Ninja. The tracked decompile names the queued change, 8x8 distortion
grid, and active texture through a real `Backdrop *` receiver. This is
analysis-only: the honest result remains 88.24% at 69/67 instructions, with
seven clean operands and no masked-operand mismatches.
