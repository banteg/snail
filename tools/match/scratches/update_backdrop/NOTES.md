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

2026-07-17 Binary Ninja ABI closure: the live function is now an explicit
`int32_t __thiscall` Backdrop member. Its Windows result contract is retained;
only the analyzer's inferred fastcall spelling and unnamed receiver are
removed. The split renderer remains `int32_t`, while the cross-port-authored
single-texture renderer is `void`.

## 2026-07-24 distortion-cell cursor ownership

The column-first grid traversal carries two borrowed cell pointers, not
pointers to the complete `BackdropDistortCell[8][8]` owner. The outer EBX
lifetime starts at `distort_grid[0]` and advances by one `0x18`-byte cell to
select the next column. The inner ESI lifetime starts at that cell and advances
by eight cells (`0xc0` bytes) to visit the same column in each subsequent row.
`Backdrop` remains the sole owner of the complete grid.

IDA independently recovers the same physical lifetimes at `0x41130a` and
`0x411315`. Replaying both as `BackdropDistortCell*` produces direct
`phase`, `phase_step`, source-offset, and current-offset field accesses,
`cell += 8`, and `++column_start`; the previous inner `float*` view and Binary
Ninja's false parent-relative subtraction are rejected by the health checks.
The replay verifies `sizeof(BackdropDistortCell) == 0x18` and
`sizeof(Backdrop) == 0x6cc` before mutation and is idempotent.

Matcher source and bytes remain untouched at the honest 88.24%, 69/67
candidate/target instruction frontier with seven clean operands. This is
durable borrowed-cursor ownership, not source or operand shaping.

## 2026-07-26 mobile AI return-boundary audit

Android and iOS both declare `cRBackdrop::AI()` void, and the Windows root BOD
dispatcher ignores this callback's result. Windows nevertheless folds the
split/single render dispatch into AI, unlike mobile, and its native tail keeps
the selected renderer's integer state.

A natural Windows `void` probe regressed focused matching from 88.24% to
85.29% with the same 69/67 instruction counts because VC6 changed the register
schedule around the folded dispatch. The observed Windows `int32_t` contract
is therefore retained. This is an intentional platform ABI boundary, not a
reason to copy the mobile declaration or shape a fake return.

## 2026-07-29 current-X borrow

Three recorded sweeps evaluated 36 phase, offset-publication, and bit-lifetime
forms. Borrowing `BackdropDistortCell::current_x_offset` as a `float&` is the
only retained improvement. It prevents VC6 from hoisting the following cosine
argument load across the completed sine-result store, exactly recovering the
native X/Y publication schedule. Pointer and paired-pointer forms emit the same
bytes, but the single reference states the narrow ownership relationship most
clearly.

Focused matching rises from 88.24% to **89.71%**, still 69/67 instructions,
with all seven references clean. The remaining difference is isolated to phase
publication: native duplicates the live x87 sum into the stack spill and cell
with `fst`/`fstp`, while the best source-shaped bit-preserving form materializes
the same bits through four integer instructions. Plain float, pointer,
reference, union, chained-assignment, and alternate bit-shadow forms are
neutral or worse; no volatile dependency is retained.
