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
- `level_progress_base` is a borrowed backlink to the enclosing
  `SubgameRuntime`. Play/Deliver writes its `level_mode_arg` and calls the
  embedded `level_definition`; no separate progress object owns those fields.
- Replay launch sets `SubgameRuntime::selected_level_record_active` and lends
  `selected_level_record` a pointer into the enclosing owner's persistent
  `sub_high_score.time_trial_route_records[selected_index]` bank. The native
  address identity is exact: `0x68b4c8 + 0x2b8c88 == 0x944150`, with
  `sizeof(SubSolution) == 0x1fac0`.

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
- Mouse coordinates and click flags belong to
  `GameRoot::players[0].game_input`, while the mode-1 exit handoff and fade
  gate belong to `GameRoot::exit_controller`, `players[0]`, and `fade`.

## Match state

Current result: 68.72%, 566 target instructions, 569 candidate instructions,
a 79-instruction exact prefix, and 52 clean / 0 unresolved / 0 mismatched
masked operands.

The first residual is now the route-icon loop exit target (`jl L28f` versus
`jl L28d`). The loop has the native behavior and instruction count through its
route-name color copy, but VC6 assigns the scaled route base and copied color
lanes to different registers, shortening the candidate block by two bytes.

Rejected probes:

- At the then-current source shape, reloading click flags directly from
  `*(g_game_base + 0x28c)` at the tail regressed the frame to `0x38`; the live
  typed `GameInput*` remains the better whole-function spelling.
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

## 2026-07-12 enclosing-subgame backlink closure

- `load_galaxy_layout` stores `&GameRoot::subgame` at `Galaxy +0x10f70`.
  `initialize_galaxy`, `open_galaxy_route`, and this updater independently use
  that same value as a `SubgameRuntime*`.
- The typed backlink recovers the launch/replay ownership described above and
  preserves this scratch's honest 61.11%, 550/566 result with all 43 operands
  clean. The exact opener remains 266/266 and the exact initializer remains
  338/338.

## 2026-07-12 global sound-manager ABI recovery

- The route-open, route-switch, and route-close feedback calls use the global
  `g_sound_effect_manager` receiver, agreeing with exact neighboring callers
  and the iOS `cRSound`/`gRSound` owner. The function body at `0x44dde0` does
  not consume `ecx`, but native callsites still materialize that authored
  receiver; a free stdcall spelling was therefore semantically incomplete.
- Correcting the three calls lifts the focused result from `61.11%`
  (`550/566`) to `63.76%` (`535/566`) while preserving the six-instruction
  prefix and improving the clean masked operands from 43 to 47 with no
  unresolved or mismatched operands.

## 2026-07-12 line-helper owner recovery

- Both native callsites load the enclosing `Galaxy*` into `ecx` before calling
  `0x409b00`. The exact helper does not consume that register, which allowed a
  false standalone stdcall spelling to match its body while losing the
  authored owner at every caller.
- Promoting it to `Galaxy::draw_galaxy_line` keeps the helper exact at 67/67
  and raises this updater from `63.76%` (`535/566`) to `63.83%` (`537/566`).
  The six-instruction prefix and 47 clean / 0 unresolved / 0 mismatched
  operands are preserved.

## 2026-07-12 mobile phase split and render ownership

- Android keeps `cRGalaxy::AI()` at `0x4f6e8`, `cRGalaxy::Render()` at
  `0x4e308`, and the one-field `cRGalaxy::AIControl()` getter at `0x4da0c`.
  Its game loop calls `AI()` and `Render()` separately. iOS preserves the same
  three symbols at `0x69c60`, `0x6a6c4`, and `0x68674` respectively.
- Windows `update_galaxy` combines the mobile `AI()` slot tick, hit testing,
  and input/handoff phases with the complete `Render()` icon/line pass. It
  returns the handoff result directly, so mobile `AIControl()` is a caller-side
  state getter rather than a missing Windows rendering or update method.
- Each icon iteration first copies
  `route_names[record->route_name_index].color` into the working color and then
  overwrites it with the white icon tint. Restoring that apparently redundant
  authored copy closes the route-slot-to-route-name ownership edge and recovers
  twelve missing candidate instructions.
- The selected-card connector is two source branches with one line call in
  each branch, and the unreachable route-zero icon passes
  `set_color_rgba(...)` directly as the quad color argument. Those source
  expressions reproduce the native argument scheduling without padding.
- The hit-test subtraction materializes a by-value `Vector3` result and copies
  it into the address-taken normalized probe. A scratch-local two-component
  `GalaxyScreenPoint` captures the native x/y subtraction while preserving the
  route record's z; the same temp-to-local shape is already exact in
  `look_at_point` and is visible in the Android Galaxy AI decompile.
- Keeping the secondary route-zero color inside the fused render phase lets
  VC6 reuse that dead storage for the later vector temporary while the primary
  color remains function-scoped. This recovers the native `0x3c` frame and
  moves the exact prefix from 6 to 79 instructions.
- Together these changes raise the honest focused result from 63.83%
  (537/566, 47 clean operands) to 68.72% (569/566, 52 clean operands), with no
  unresolved or mismatched masked operands.
