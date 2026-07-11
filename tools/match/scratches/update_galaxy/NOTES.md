# update_galaxy @ 0x4092f0

Relationship-first scratch for the Star Map update/render controller. It now
uses the shared `Galaxy` and route-record layouts recovered across
`load_galaxy_layout`, `initialize_galaxy`, `open_galaxy_route`, and
`close_galaxy_route`.

This function owns the route icon/line render pass, route-card hit testing,
highlight-target assignment, route-card open/switch/close input, and the
selected-level/replay launch handoff back to the subgame state machine.

## Recovered behavior

- Hides gameplay scores through `level_progress_base` before any route work.
- Ticks every route slot from the owned array at `this +0x10`, stepping by
  `0x2a0`.
  The callee at `0x409bd0` is a `thiscall` helper, not a cdecl helper that takes
  a record pointer.
- Renders the selected-card connector line through exact `draw_galaxy_line`
  when the card is open and visible.
- Draws route icons (`151`) and route highlight glows (`150`), plus the
  inter-route line texture (`154`) and the ten galaxy sprites (`139..148`).
- Hit-tests the open route-card frame, then route points, and writes
  `highlight_target` to `1.0f` for selected/hovered routes.
- Consumes Back/Exit, Play/Deliver, Replay, route switch, and close-card clicks,
  including the mode-1 return through the saved frontend state fields at
  `g_game_base + 0x4f3ac/+0x4f3b4`.
- Replay launch writes `level_progress_base +0xff25d0` and points
  `+0xff25d4` at the selected high-score/replay record:
  `level_progress_base + 0x944150 + selected_index * 0x1fac0`.

## Layout notes

- `RuntimeConfig::highest_galaxy_route_index` at `+0xa0` is the inclusive
  highest galaxy route index shared with subgame setup and challenge setup.
- `GalaxyRouteSlot` starts at `this +0x10` and owns a `GalaxyRouteRecord` at
  slot `+0x04`. The native icon loop instead keeps the controller-relative
  base `this + route_index * 0x2a0` and reads fields at
  `+0x1c/+0x20/+0x24/+0x28/+0x2c`; the explicitly non-owning
  `GalaxyRouteIndexedSlotView` preserves that access shape without competing
  with slot ownership.
- The native route icon loop starts at `route_index = 1` but still retains an
  apparently unreachable `route_index == 0` branch that draws a red-ish route
  zero icon with a second stack `Color4f`.
- The native function constructs one no-op `Color4f` at entry with the shared
  `0x44db50` thunk. Modeling the second stack color and the route-zero branch
  recovers the native `0x3c` frame.

## Match state

Retained result: 61.11%, 566 target instructions, 550 candidate instructions,
6-instruction prefix, and 43 clean / 0 unresolved / 0 mismatched masked
operands.

The first residual is stack-color slot assignment:

```asm
target:    lea ecx, [esp+0x3c]
candidate: lea ecx, [esp+0x2c]
```

Both functions allocate `0x3c`, but VC6 places the main color and the secondary
route-zero color in the opposite order from native. Swapping declaration order
or swapping source uses did not change the emitted layout.

Rejected probes:

- Reading click flags directly from `*(g_game_base + 0x28c)` at the tail made
  that local look more native locally, but regressed the frame to `0x38` and
  dropped the score to 57.94%.
- A free `update_galaxy_route_record(void*)` helper produced a cdecl call and
  missed the native `mov ecx, ebx; call` route-record tick shape.

## 2026-07-11 route-slot ownership closure

- The constructor proves 101 complete slots rather than 100 oversized records
  plus padding. The new exact `update_galaxy_route_record` scratch independently
  proves the slot's tint/target fields at `+0x18/+0x1c`.
- Using owned slots for iteration and a documented controller-relative view
  only where native retains that base preserves the 61.11% baseline, 550/566
  instruction shape, and all 43 clean operands.

2026-07-11 authored parent: Android/iOS retain this state machine as
`cRGalaxy::AI()`. The primary 0x10fa8 `Galaxy` owner replaces the smaller
semantic parent view without changing the honest 61.11%, 550/566 result or its
43 clean operands.
