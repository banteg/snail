# update_salt_hazard @ 0x441c10

First correctly named scratch for the salt runtime updater after the 2026-06-16
vtable correction. `initialize_salt_hazard_runtime` installs vtable
`data_497340`, and `data_497340` points at `0x441c10`.

Pinned at `62.96%`, `79/83` target instructions. Field offsets are aligned;
the remaining masked mismatch is the state-2 error-string tail merge (`List
remove` versus `List remove NEXTBOD`) in the candidate control-flow shape.

Recovered behavior:

- skips while `owner_game +0x09` `subgame_pause_gate` is set
- state `2` performs the standard live-list removal against `game +0x5a8`
- state `1` computes a fade fraction from `position.z`, clamps it to
  `[0, 1]`, writes alpha through `tColour::set_color_alpha(0.9)`, and moves
  to state `2` once behind `owner_game +0x3be0e4`

This replaces the previous salt interpretation of `0x4417d0`; that function is
now correctly owned by the sub-lazer vtable.

2026-06-16 BOD/renderable consolidation: the shared `SaltHazardSlot` header now
uses the promoted `BodNode` prefix and `BodList` anchor, and records the
complete `RenderableBod` through `+0x7f`. This updater now calls
`color.set_color_alpha(...)` through the promoted `tColour color +0x28` field
instead of a raw cast, while spawn/initializer/collision prove the position
row at `+0x68`. Focused Wibo remains `62.96%`, `79/83`, with the same known
state-2 error-string tail merge mismatch.

2026-06-19 local game-base staging: spelling the state-2 free-list anchor
through a local `Game* game = g_game` improves the focused match from `62.96%`
to `75.78%` and clears the previous masked string mismatch (`10 ok / 0
unresolved / 0 mismatch`). The remaining state-2 residual is still real:
native materializes `game+0x5a8` as an anchor pointer in `ecx`, while the
candidate keeps the game base and folds anchor accesses to `+0x5ac/+0x5b0`;
the first error-report call also remains tail-merged in candidate code.

2026-06-20 volatile audit: direct `g_game` is now a normal external here too.
Focused Wibo improves from 75.78% to 81.48%, with 83 target / 79 candidate
instructions and 11 masked operands OK. This keeps the game-base lifetime
consistent with the damage/salt family and avoids stale volatile reloads; the
remaining residual is still state-2 control-flow/tail merging plus anchor
materialization.

2026-06-21 state-2 cleanup split: preserving the native order for the first
error path requires `report_errorf("List remove")` before clearing `state`, but
that straight-line spelling tail-merges with the later `NEXTBOD` path. A local
`goto first_remove_error` after the first report gives the compiler the same
unique cleanup tail as native without changing side effects. Focused Wibo is
now exact: `100.00%`, `83/83` target/candidate instructions, `83/83` prefix,
and `12 ok / 0 unresolved / 0 mismatch` masked operands.

Rejected variants: clearing `state` before the first report also reached
`98.80%`, but it reverses observable error-report ordering. Flattening the
error branches, storing the report result in a local, introducing a state-value
local, and spelling the unlink guard without `else` all stayed at `81.48%`.
Clearing state before both reports and forcing a positive live branch regressed.

2026-06-21 subgame-owner consolidation: `SaltHazardSlot::owner_game` is now a
`SubgameRuntime*` for the pause gate, fade start, and kill-plane fields. The
root free-list anchor is kept as a narrow `RootBodListView` at `g_game +0x5a8`
instead of another ambiguous local `Game` shell. Focused Wibo remains exact at
`100.00%`, `83/83` instructions, with `12` clean masked operands.

2026-07-11 root-list ownership closure: renderer traversal and salt teardown
are the two sides of the same `GameRoot +0x5a8` `BodList`: `first +0x04` is
the active head and `free_top +0x08` receives unlinked nodes. The synthetic
`RootBodListView` is retired in favor of `GameRoot::active_bod_list`. Focused
Wibo remains exact at `100.00%`, `83/83`, with `12` clean masked operands.

2026-07-11 authored owner: iOS preserves this callback as `cRSalt::AI()`, and
the Windows constructor table at `0x497340` points directly here. The scratch
now defines the method on `Salt`; matching remains exact at 83/83 with twelve
clean operands.

2026-07-13 Binary Ninja ownership consolidation: the callback now consumes the
canonical authored `Salt` established by startup. The lanes at `+0x8c`,
`+0x90`, and `+0x94` are the fade, spawn-y, and collision-latch fields proved
across the exact spawn, update, and collision paths, while `owner_game +0x88`
is a borrowed `SubgameRuntime*`.
`SubgameRuntime` owns the exact 40-slot `SaltManager` at `+0x3578c0`; this
replaces both the stale sparse slot experiment and lane-local `FrameSaltSlot`.
Matching remains exact at 83/83.

2026-07-14 renderable-owner closure: both fade/kill-plane reads now name
`Salt::transform.position`. With the constructor and spawner, this proves the
whole prefix is the shared inherited `RenderableBod`, while the manager still
owns the 40 inline derived records. Matching remains exact at 83/83 with twelve
clean operands.

2026-07-15 analysis-lane owner replay: the exact callback now decompiles on
the authored `Salt` receiver in both lanes. The inherited transform, colour,
and list node resolve through `body`, while the proved `+0x8c/+0x90/+0x94`
fade, spawn-y, and collision-latch overlays retain their semantic names.
Matching remains exact; no source-shape claim was changed.

2026-07-19 lifecycle-state closure: state `0/1/2` is now the 32-bit
`SaltState` owner (`INACTIVE`, `ACTIVE`, `RECYCLE_PENDING`), and the updater
writes `fade_alpha` directly. The exact 83/83 code and twelve clean operands
are unchanged; the old `Vec3` overlay is retired.
