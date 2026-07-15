# run_frame_update

Exact source-shaped scratch for the frame update loop at `0x40a2a0`.

Current match: 100.00% (`135/135` candidate instructions, full prefix, 23
masked operands ok). The former residuals were local scheduling/argument
evaluation around the accumulator store and captured-cursor draw.

Rejected/neutral probes:

- Inlining only `color.set_color_rgba(...)` while retaining precomputed mouse
  x/y locals matched the target's layer-before-tint evaluation order, but grew
  the stack frame and regressed the function to 75.74%.
- Naming the mouse-state pointer is source-legible but codegen-neutral; the
  target still schedules the `lea ecx, [this+0x290]` before the float store.

The main Sprite evidence is the active-bucket traversal:

- starts at `g_sprite_active_heads`;
- walks each `Sprite::next` chain while saving `next` before `update_sprite`;
- increments a local sprite update counter;
- stops by signed pointer comparison against `&g_sprite_free_head`.

This mirrors the exact `kill_game_sprites` bucket topology but calls
`Sprite::update_sprite` instead of conditionally killing `0x800` sprites.

## Type consolidation (2026-06-17)

`MouseCursorState` and `FrontendOverlayColorLerp` now live in shared headers.
`run_frame_update`, `is_mouse_captured`,
`release_mouse_cursor`, `resolve_uncaptured_cursor_sensitivity_scale`, and
`initialize_frontend_overlay_color_lerp` all keep their previous focused match
results with those headers.

Two mouse callsites remain local on purpose: `uninit_pause_menu` declares
`release_mouse_cursor` as returning `int` to preserve the native tail-return
shape, while `update_frontend_state_machine` keeps the compact
`capture_mouse_cursor` declaration because including the full header dirties
the jump-table/global masked operand audit without improving structure.

2026-06-18 cheat header cleanup: `CheatState` is now shared with
`initialize_cheat`, `match_cheat_text`, and `update_cheat`. Focused Wibo remains
pinned at 97.78%, 135/135 instructions, with the same mouse-state/tint
argument scheduling residuals and 23 clean masked operands.

2026-06-20 frame-order retry: hoisting the `MouseCursorState* mouse` declaration
above the frame-accumulator temporary is codegen-neutral and keeps the early
`fstp [base+0x518]` before `lea ecx, [base+0x290]`. Naming the cursor draw
layer as a local `int layer = 7` is also codegen-neutral; the layer push still
lands after `tColour::set_color_rgba`. The residual remains argument/store
scheduling, not a missing local name.

2026-06-20 ActiveBod ABI cleanup: the frame loop now uses
`include/active_bod.h` and calls the known slot-0 updater as
`update_active_bod()`. This removes the scratch-local `virtual update()`
conflict without changing the pinned 97.78% residual profile. The adjacent
`RuntimeCallback` vtable row remained local at this point because it spanned
larger partials with different callback names; the shared ABI pass below later
retires it.

2026-06-20 runtime no-op AI split: the empty runtime-slot callback is now
spelled as `RuntimeSlot::noop_runtime_ai()` in the three subgame/player
callsite scratches. This left the local `RuntimeCallback` scoped to the two
frame-loop virtual `update()` slots at `base + 0x124` and `base + 0x31c` until
the later shared-dispatch pass. Focused Wibo remains pinned at 97.78% with the
same two scheduling residuals.

2026-06-20 larger near-proof pass: replacing the named `MouseCursorState*`
local with a direct `((MouseCursorState*)(base + 0x290))->is_mouse_captured()`
call is codegen-neutral at 97.78%. It does not move the native
`lea ecx, [base+0x290]` before the accumulator store, so the retained named
local remains the clearer source shape.

2026-06-20 near-proof continuation: focused Wibo still reports 97.78%,
135/135 instructions, 18/135 prefix, and 23 clean masked operands. Recasting
the mouse receiver as a C++ reference (`MouseCursorState& mouse =
*(MouseCursorState*)(base + 0x290)`) is codegen-neutral and still schedules
the frame-accumulator `fstp [base+0x518]` before `lea ecx, [base+0x290]`.
Keep the pointer local; the residual remains statement scheduling around the
mouse receiver and cursor-quad tint/layer evaluation.

2026-07-11 contact-registry owner pass: the fixed-step tail now resets
`subgame.enemy_manager` directly. Exact init/search/register helpers and the
iOS `cREnemyManager` symbols prove this is the root-owned subgame registry, not
an anonymous count-only placeholder. The focused result stays
at 97.78%, 135/135, with the same two scheduling-only differences and 23 clean
masked operands.

2026-07-11 cRGame frame-owner pass:

- iOS `Game.o` independently names this method `cRGame::AI()`.
- Root fields are now named as `fade`, `frontend_quit_requested`,
  `fixed_update_count`, `fixed_update_accumulator`, `frame_counter`, and
  `input_sampling_gate`; the border allocator and game-input bridge prove the
  latter two outside this function.
- Player zero owns `MouseCursorState +0x16c` and
  `FrontendOverlayColorLerp +0x184`. The cursor quad deliberately consumes
  `saved_x/saved_y`: capture copies live coordinates there, release restores
  them, and exact `cRPlayer::AI()` refreshes them from the current camera
  anchor.

2026-07-13 shared player AI dispatch: both embedded Player slot-zero calls now
use the shared `BodAiDispatch` ABI overlay. This retires the last local
`RuntimeCallback` shell without adding a second vptr to Player's explicit
cRBod-compatible prefix. Focused Wibo remains 97.78%, 135/135 instructions,
prefix 18/135, with all 23 operands clean.
- The active BOD traversal now begins at `active_bod_list.first`, both virtual
  callbacks are the two owned `players`, and the level-mode/contact-registry
  tail is reached through `subgame`.
- All ownership substitutions are codegen-neutral. Focused Wibo remains the
  honest 97.78%, 135/135 result with the same two scheduling differences and
  23 clean masked operands.

## 2026-07-13 frame-lifetime closure

- The fixed-step seed is an in-place owner update,
  `fixed_update_accumulator += 1.0f`, rather than a detached temporary copied
  back later. VC6 consequently keeps the x87 sum live across the mouse-owner
  `lea` and quit-latch clear, matching the native store schedule.
- The captured-cursor quad is one source-level call expression. Keeping the
  saved x/y offsets and `tColour::set_color_rgba` expression directly in the
  call lets VC6 evaluate the final layer argument first, construct the tint,
  and then materialize y/x without spill slots. Inlining only the tint while
  retaining precomputed mouse locals grows the frame and remains rejected.
- Final focused Wibo is exact: 100.00% (`135/135`, full prefix), with all 23
  masked operands resolved and equal. No register hints, volatile state, dummy
  control flow, or flag changes are used.

## 2026-07-14 active-list flag ownership

The active BOD walk now names `BOD_FLAG_DEBUG` and
`BOD_FLAG_NEXT_UPDATE_GUARD`. The latter is set only on the saved successor
while the current node's virtual AI runs, then cleared before advancing;
`BodList::remove_bod` independently rejects removal of that protected node with
the native `List remove NEXTBOD` diagnostic. The shared names preserve the
exact 135/135 instruction stream and all 23 audited operands.

## 2026-07-14 canonical subgame analysis owner

Binary Ninja's frame bootstrap originally left `GameRoot::subgame` typed as a
sparse `FrameSubgameRuntime`, even after the complete `SubgameRuntime` owner
was available. The replay now promotes that root member to the canonical
runtime when present. The fixed-step tail consequently resets
`subgame.enemy_manager`, matching the matcher source and retiring the parallel
`contact_targets` presentation identity. The sparse frame type remains only
for standalone bootstrap imports.
