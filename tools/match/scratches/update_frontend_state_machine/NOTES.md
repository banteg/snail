# update_frontend_state_machine @ 0x4107d0

Exact bridge scratch: 100.00%, 180/180 instructions, full prefix, and 69 clean
masked operands. It covers the recovered front-end dispatch states, the
subgame handoff/return opcodes at states 10/11 and 26/27/28, and the tail camera
transform snapshot/invert.

The scratch now runs as `GamePlayer::update_frontend_state_machine`, the
Windows `cRPlayer::AI()` owner, and uses the shared `GameRoot`/`GamePlayer`
layout instead of a scratch-local state-machine shell.

Historical recovery notes:

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
- 2026-06-20: A temporary capture-only view kept the then-partial mouse ABI
  isolated while the switch tail was still being recovered. The 2026-07-11
  owner pass supersedes that view with the now-proven embedded
  `MouseCursorState`.
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

2026-07-10 cRPlayer/cRCamera ownership closure:

- `construct_game_runtime` creates two 0x1f8-byte player records at root
  `+0x124/+0x31c`. The callback installed on each record points to this exact
  function, matching the iOS `cRPlayer::AI()` provenance.
- `frontend_state +0x94`, `saved_frontend_state +0x98`, the redispatch byte at
  `+0x1e8`, and selected high-score rank/mode at `+0x1ec/+0x1f0` now belong to
  `GamePlayer`; the old root-level `+0x310/+0x314` names were fields of player
  zero all along.
- The player owns `RenderCamera camera +0xa0`. Its inherited transform lands at
  player `+0xd8`, its view matrix at `+0x120`, and its FOV at `+0x160`. The
  exact tail now copies `GamePlayer::transform` into `camera.transform`, then
  inverts it into `camera.view_matrix` using typed subobjects.
- The explicit live/snapshot pointers remain meaningful aliases of those two
  owned matrices and preserve the native delayed anchor-y store. The fully
  typed owner stays byte-exact at 180/180.

2026-07-11 cursor/overlay ownership closure:

- `MouseCursorState` occupies player `+0x16c..+0x183`; the four exact capture
  callsites now use `mouse_cursor.capture_mouse_cursor()` directly.
- The delayed tail stores at player `+0x178/+0x17c` are the cursor's
  `saved_x/saved_y`, refreshed from the active camera anchor. `run_frame_update`
  consumes those same fields to draw the captured cursor.
- The adjacent 0x24-byte `FrontendOverlayColorLerp` begins at player `+0x184`.
  Its target/current colors are the constructor-proven values at
  `+0x188/+0x198`.
- The fully owned spelling remains exact at 180/180 with 69 clean operands.

2026-07-11 cRGameInput backlink closure:

- Root initialization builds `GameInput game_inputs[2]` at `+0x44` and stores
  the corresponding borrowed pointer in each player at `+0x168`.
- The former `camera_anchor` tail is therefore the player's `game_input` link.
  Its `input.authored_x/y` fields at owner `+0x60/+0x64` feed the cRMouse saved
  coordinates before the camera transform snapshot.
- The corrected ownership remains exact at 180/180 with 69 clean operands.

2026-07-14 cRPlayer::AI return-contract closure:

- `run_frame_update` dispatches both Windows player records through the shared
  `BodAiDispatch::update_bod_ai()` void slot. Android `cRGame::AI()` uses the
  same void virtual-call shape for its embedded player callback.
- Android `cRPlayer::AI()` restores its frame and tail-branches to
  `tMatrix::Invert(tMatrix const&)`; that matrix helper is independently void.
  The decompiler's integer result was therefore only propagated register state.
- Spelling both members `void` removes the synthetic tail return while keeping
  this Windows scratch byte-exact at 180/180 with all 69 masked operands clean.
