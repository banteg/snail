# update_frontend_state_machine @ 0x4107d0

First source-shaped bridge scratch: 48.50% against the default extent
(`194` target insns, `239` candidate insns), with prefix `12/194`. It covers
the recovered front-end dispatch states, the subgame handoff/return opcodes at
states 10/11 and 26/27/28, and the tail camera transform snapshot/invert.

The scratch now uses a local `GameRoot` layout for the known `data_4df904`
owners instead of preprocessor offset accessors. `uv run snail match types
--paths` leaves this local, as expected; the global/root layout is still too
partial to consolidate.

Residuals are intentionally left to the matcher rather than papered over:

- Switch lowering and shared fall-through labels are not yet shaped beyond the
  semantic state grouping from IDA/Binary Ninja. Region output shows most of
  the remaining loss is jump-table target placement plus shared exit-label
  distance, not missing states.
- `data_4df904` reload ownership differs in many call blocks: native often
  loads the game base into `eax`/`edx` and then uses `lea ecx, [reg+offset]`,
  while the current typed member calls usually lower to `mov ecx; add ecx`.
- The state-20 high-score block is source-shaped with a local `GameRoot*`
  because the native code loads one base pointer and reads `+0x314/+0x310`
  before calling `initialize_high_score_screen`.
- The tail now uses explicit live/snapshot `TransformMatrix*` locals. This
  preserves the native x87 `camera_x`/`camera_y` loads, `rep movsd` matrix
  copy, and delayed `camera_y` store without byte-shaped code. `uv run snail
  match idioms six-dword-struct-copy` confirms aggregate copies lower to
  `rep movsd`.
