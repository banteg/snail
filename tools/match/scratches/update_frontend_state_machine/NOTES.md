# update_frontend_state_machine @ 0x4107d0

First source-shaped bridge scratch: 58.12% against the default extent
(`194` target insns, `243` candidate insns), with prefix `12/194`. It covers
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
- Most `data_4df904` call owners now use block-local `GameRoot*` temporaries,
  recovering the native `mov base; lea ecx, [base+offset]` member-call shape
  without going back to preprocessor offset helpers. Remaining differences are
  mostly `eax` versus `edx` owner-register choices and shared-exit label
  distances.
- The state-20 high-score block is source-shaped with a local `GameRoot*`
  because the native code loads one base pointer and reads `+0x314/+0x310`
  before calling `initialize_high_score_screen`.
- The tail now uses explicit live/snapshot `TransformMatrix*` locals. This
  preserves the native x87 `camera_x`/`camera_y` loads, `rep movsd` matrix
  copy, and delayed `camera_y` store without byte-shaped code. `uv run snail
  match idioms six-dword-struct-copy` confirms aggregate copies lower to
  `rep movsd`.
- 2026-06-18: Replaced the local 0x40 matrix view with shared
  `transform_matrix.h`; focused Wibo stays `71.35%`, `176/180`, with
  `53 ok, 1 mismatch`.
- 2026-06-20: The local capture-only mouse call surface is now named
  `FrontendMouseCaptureView` instead of `MouseCursorState`. This keeps the
  scratch byte-stable at `71.35%`, `176/180`, while leaving the shared
  `mouse_cursor_state.h` layout for helpers and frame/update callsites that
  agree on the full ABI.
- 2026-06-20 proof pass: removing the stale `volatile` from direct `g_game`
  lifts the focused match from 71.35% to 93.33%, restores exact instruction
  count parity, and extends the prefix to 131/180. The remaining residual is
  the subgame restore/thanks/help tail. Spelling state 27 as an explicit
  `destroy_subgame(); initialize_subgame(); goto restore_saved_state;` source
  path, rather than sharing the source label with state 28, lets MSVC tail-merge
  the native case-27/case-28 labels and proves the scratch: 100.00%, 180/180,
  prefix 180/180, 69 masked operands OK, no unresolved or mismatched operands.
  Rejected/neutral in this pass: local-owner spelling for the shared
  initialize label, direct/local owner swaps in the thanks/help fallthroughs,
  and warning-actor guard rewrites.
