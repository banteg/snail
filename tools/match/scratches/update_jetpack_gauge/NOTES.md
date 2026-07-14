# update_jetpack_gauge @ 0x43a390

Source-shaped partial scratch for the jetpack countdown/warning controller.

Current match: 85.93% (`132` candidate instructions vs `131` target,
`34` clean masked operands).

Recovered behavior:

- native treats state `0` and non-`1` states as immediate returns; only state
  `1` advances `progress` by `progress_step`;
- it ends hover and clears the controller when progress exceeds 1.0 or the
  player passes `game->completion_row_start - 5`;
- it ramps warning intensity at the start, holds it through the middle range,
  and fades it out after `0.94`;
- while in the middle range it samples the current runtime row through
  `get_track_runtime_cell_at_world_z(game+0x74618, game+0x42fde4)` and forces
  `progress = 0.94` when `BYTE1(row->flags) & 0x80` is set, i.e. the 32-bit
  flag mask is `0x8000`;
- once active, it updates wobble x/y/alpha and calls the one-instruction
  `spawn_track_speedup` address with the authored `cRSubHover::Hover`
  `(Vector3&, float)` receiver/signature.

Important corrections made during matching:

- inactive state `0` does not call `end_jetpack_hover`; it returns before any
  cleanup;
- the `0.94` middle/fade branch is naturally expressed as `> 0.94` first, then
  the middle hold branch;
- the empty `spawn_track_speedup` target is `ret 8`; cross-port evidence now
  proves the hover call is a real `SubHover` member alias, so the former fake
  derived caller view is retired.

Known residuals:

- VC6 still delays the `xor edi, edi` zero initialization instead of placing it
  before the state switch like native;
- the native state dispatch is `sub eax, edi; je return; dec eax; jne return`,
  while the clean `switch(state)` source recovers the `dec/jne` part but not the
  early zero register setup;
- `game`/`player` loads around the completion-row check use different registers,
  though the field offsets and behavior are aligned.

2026-06-20 type cleanup: the jetpack presentation receiver is intentionally a
scratch-local `UpdateJetpackPresentationView`, paired with
`ArmJetpackPresentationView` in `arm_jetpack_gauge`. That removes the false
shared unresolved-layout row without promoting any unproven
authored `Snail` fields. Rebuilt matcher stays at 85.82% with
34 clean masked operands; `arm_jetpack_gauge` remains exact at 18/18.

2026-06-20 state-dispatch retry: spelling the state gate as an explicit
`live_state` ladder recovers native's early `xor edi, edi` before testing the
controller state and improves focused Wibo to `85.93%`, with prefix `6/131`
and the same 34 clean masked operands. VC6 still uses `cmp eax, edi` plus a
separate `test eax, eax` after `dec eax`, while native reuses flags from
`sub eax, edi` and `dec eax`; a `switch (state - zero)` spelling regressed to
`84.29%` and disturbed the progress-add x87 order, so keep the ladder.

2026-06-21 subgame owner typing: `SubHover::game` is now typed
as `SubgameRuntime*`, and the global row-sampler cast uses the same shared
runtime view at `g_game_base + 0x74618`. This removes the scratch-local
generic `Game` shell without moving the codegen; focused Wibo remains at
`85.93%`, `132/131`, prefix `6/131`, with 34 clean masked operands.

2026-07-11 player/root ownership closure: `SubHover::player` is
the borrowed containing `Player*`; the completion check reads its real
`position.z`. Global presentation and row-sampler paths now resolve through
`GameRoot::subgame` and its embedded player, retiring
`PlayerForJetpackGauge` and `UpdateJetpackPresentationView`. Focused Wibo is
unchanged at `85.93%`, `132/131`, prefix `6/131`, with 34 clean masks.

2026-07-11 authored-owner closure: Android and iOS identify the entire method
as `cRSubHover::AI()`. Android matches the Windows state/progress fields,
borrowed parent pointers, warning curve, wobble outputs, JetUnInit edge, runtime
row flag, and final `Hover(tVector&, float)` call. The exact owner is 0x214
bytes at `Player +0x2750`; the stable Windows function names remain unchanged.
Replacing the fake derived no-op caller with the typed SubHover member call is
codegen-neutral at the same honest 85.93% with 34 clean masks.

## 2026-07-14 JetPack row flag

The auto-shutoff test now consumes `SUBROW_FLAG_JETPACK_OFF`, copied from the
authored `JetPack=Off` metadata lane. It belongs to `SubRow::flags`; the same
numeric `0x8000` in the separate `SubLoc::lane_and_flags` owner is unrelated.
Focused output remains 85.93%, 132/131 instructions, prefix 6/131, with all 34
operands clean.

## 2026-07-14 hover lifecycle ownership

The native early ladder and teardown store now name
`SUB_HOVER_STATE_INACTIVE`; the only armed value is
`SUB_HOVER_STATE_ACTIVE`. This preserves the deliberate VC6 ladder shape and
the honest 85.93%, 132/131-instruction partial, prefix 6/131, with all 34
operands clean.
