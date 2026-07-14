# initialize_completion_screen

`initialize_completion_screen` @ `0x404920` builds the delivery-complete result
screen object used by the cutscene completion handoff. It is called only from
`update_cutscene` with `game+0x12e6df0`, not from the frontend prompt object at
`game+0x4f3ac`.

Recovered relationships:

- The authored `Completion` uses widgets at `+0x00/+0x04/+0x08/+0x0c/+0x10`.
- `+0x48` is the computed bonus score and `+0x4c` is the total score built from
  `game+0x430060 + delivered_count * 100 + bonus`.
- Postal perfect delivery awards `50,000`; challenge mode indexes the two
  `0x4a1194/0x4a11ac` six-entry bonus tables from either live challenge slider
  globals `data_4df960/4df958` or replay record fields `+0x50/+0x4c`.
- The `SubSolution` tail fields at `+0x48/+0x4c/+0x50` now line up with the
  `complete_subgame` result-record copy and the completion replay bonus read.

Current match: 89.89%, 278 target instructions / 276 candidate instructions,
with a 23-instruction exact prefix and 44 masked operands all resolved. The
remaining bonus-table block is a register-allocation residual: native carries
the difficulty/y index in `esi` and the speed/x source through `ecx`, while the
straightforward C++ selects the opposite pair before converging on the same
clamps, perfect-bonus test, and table lookups. No fakematching.

2026-07-10 owner closure: replay-active and replay-record reads now use the
embedded `GameRoot::subgame` aliases at relative `+0xff25d0/+0xff25d4`. The
focused result stays codegen-neutral at 64.10%.

2026-07-11 cRCompletion closure: this method, exact `flush_row_event_display`,
exact `register_parcel_delivery`, and exact `update_row_event_display` all act
on `SubgameRuntime::completion +0x12727d8`. The `Completion` union names both
the parcel-display and final-result phases without duplicating storage;
`sizeof(Completion) == 0x50` matches the native ledger and ends exactly at
`TimesUp`. The focused initializer remains honestly at 64.10%, 268/278, with
all 34 operands clean.

2026-07-12 source-shape recovery:

- Removing the long-lived `GameRoot*` borrow matches the native ownership
  boundaries: the root is reloaded for the initial mode, replay record, total
  score, and later UI mode reads rather than being retained across widget
  allocation callbacks.
- Computing the difficulty/y division inside each replay/live-source branch
  restores the native 23-instruction prefix and keeps the speed/x source raw
  until the shared division point.
- The perfect/non-perfect continue-widget calls are again separate source
  branches, matching the native shared-tail layout without a synthetic stack
  y-coordinate.
- Together these changes raise the focused result from 64.10% (`268/278`,
  prefix 0, 34 clean operands) to 89.89% (`276/278`, prefix 23, 44 clean
  operands). Natural declaration-order, switch, shared-color, and temporary
  variants were rejected because they regressed the result or only exchanged
  registers; the residual stays visible.

2026-07-13 cross-tool owner routing:

- Binary Ninja and IDA now carry `Completion` and the adjacent `TimesUp`
  directly in their canonical `SubgameRuntime` headers. The `0x50`-byte
  completion owner at `+0x12727d8` ends exactly where the `0x10`-byte times-up
  owner begins at `+0x1272828`.
- The path-template sync no longer owns those root fields, and its redundant
  IDA Completion prototypes have been removed in favor of the dedicated
  completion-screen lane. BN lifecycle prototypes now live with the
  SubgameRuntime owner. This is codegen-neutral ownership cleanup; the honest
  89.89%, 276/278 initializer result remains unchanged.

2026-07-13 canonical root reloads:

- Each scene-state read now reloads the typed `GameRoot*` global and follows
  `subgame` to the level mode, replay launch record, or player score. This
  preserves native's short borrow boundaries across widget callbacks without
  reconstructing `GameRoot` from a raw byte-base declaration.
- All five UI handles are allocated through the root-owned `BorderManager`.
  Focused Wibo remains codegen-neutral at 89.89%, 276/278 instructions,
  prefix 23, with all 44 masked operands clean; the documented challenge-bonus
  register allocation remains the honest residual.

## 2026-07-14 challenge bonus table extents

Both challenge inputs are divided into 20-point bands, clamped to indices
`0..5`, and used only against the adjacent tables at `0x4a1194` and
`0x4a11ac`. The six dwords between those addresses close the Y table, and the
same shared six-entry capacity now owns the X table and all clamp/perfect-cell
tests rather than repeating the terminal index literal.

This source-only ownership recovery preserves the normalized candidate
listing byte-for-byte
(`03523667ddb744274769571200084df1e3be01036f1cd98d61b8d5c89c0fbea7`)
and the honest 89.89% result (`276/278`, prefix `23/278`, 44 clean operands).
The remaining gap is still the documented x/y register allocation, not table
layout.
