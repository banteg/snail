# update_galaxy @ 0x4092f0

Current recovery: semantic-complete (`compiler` residual). Exact Android/iOS
`cRGalaxy::AI()` and `Render()` bodies, their `AIControl()` state getter, and
the live Windows Galaxy method establish the combined route tick, icon/line
rendering, hit testing, card controls, level launch, replay selection, and
frontend handoff. All 55 references are clean; the 569/566 candidate's
remaining deltas are equivalent stack-slot and register colouring across the
connector, route-icon, and input-tail lanes.

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
  `cRSubGame`. Play/Deliver writes its `level_mode_arg` and calls the
  embedded `level_definition`; no separate progress object owns those fields.
- Replay launch sets `cRSubGame::selected_level_record_active` and lends
  `selected_level_record` a pointer into the enclosing owner's persistent
  `sub_high_score.time_trial_route_records[selected_index]` bank. The native
  address identity is exact: `0x68b4c8 + 0x2b8c88 == 0x944150`, with
  `sizeof(SubSolution) == 0x1fac0`.

## Layout notes

- `RuntimeConfig::highest_galaxy_route_index` at `+0xa0` is the inclusive
  highest galaxy route index shared with subgame setup and challenge setup.
- `GalaxyStar` starts at `this +0x10` and owns a `GalaxyRouteRecord` at
  slot `+0x04`. The native icon loop instead keeps the controller-relative
  base `this + route_index * 0x2a0` and reads fields at
  `+0x1c/+0x20/+0x24/+0x28/+0x2c`; the explicitly non-owning
  `GalaxyRouteIndexedSlotView` preserves that access shape without competing
  with slot ownership.
- The native route icon loop starts at `route_index = 1` but still retains an
  apparently unreachable `route_index == 0` branch that draws a red-ish route
  zero icon with a second stack `tColour`.
- The native function constructs one no-op `tColour` at entry with the shared
  `0x44db50` thunk. Modeling the second stack color and the route-zero branch
  recovers the native `0x3c` frame.
- Mouse coordinates and click flags belong to
  `GameRoot::players[0].game_input`, while the mode-1 exit handoff and fade
  gate belong to `GameRoot::exit_controller`, `players[0]`, and `fade`.

## Match state

Current result: 71.01%, 566 target instructions, 569 candidate instructions,
a 48-instruction exact prefix, and 55 clean / 0 unresolved / 0 mismatched /
0 unaudited masked operands.

The first residual is the selected-card connector's saved `map_y` temporary:
native reuses `[esp+0x10]`, while the candidate uses the later cursor-y slot at
`[esp+0x18]`. The connector behavior and both call operands remain correct.
The next structural residual is still the route-icon loop: VC6 assigns its
scaled route base and copied route-name color lanes to different registers.

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
  that same value as a `cRSubGame*`.
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

- Both native callsites load the enclosing `cRGalaxy*` into `ecx` before calling
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
  it into the address-taken normalized probe. The same temp-to-local shape is
  already exact in `look_at_point`; the Galaxy-specific subtraction preserves
  the route record's z while subtracting the cursor x/y coordinates.
- Keeping the secondary route-zero color inside the fused render phase lets
  VC6 reuse that dead storage for the later vector temporary while the primary
  color remains function-scoped. This recovers the native `0x3c` frame and
  moves the exact prefix from 6 to 79 instructions.
- Together these changes raise the honest focused result from 63.83%
  (537/566, 47 clean operands) to 68.72% (569/566, 52 clean operands), with no
  unresolved or mismatched masked operands.

## 2026-07-13 scalar cursor ownership

- Android `cRGalaxy::AI()` loads the authored cursor axes into two independent
  scalar values (`v11` x and `v10` y), then subtracts those scalars from each
  route position while copying the route position's z lane into the normalized
  `tVector`. Windows performs the same two-axis subtraction at `0x4097ae` and
  `0x40983e`.
- Replacing the scratch-only `GalaxyScreenPoint` aggregate with owned
  `mouse_x`/`mouse_y` scalars and an inline `subtract_screen_xy` expression
  therefore removes an invented type without changing behavior. It lifts the
  focused match from 68.72% to 71.01% at the same 569/566 instruction shape and
  preserves all 52 clean operands with no unresolved or mismatched operands.
- The scalar locals reduce the exact prefix from 79 to 48 because VC6 assigns
  the selected-card connector temporary to a later reusable stack slot. That
  is kept as an honest residual: direct native-style reloads of the card edge
  or click input shrink the candidate frame to `0x38`, and retaining a
  function-scoped `GameRoot*` regresses the whole-function score.

## 2026-07-14 route-zero coordinate ownership

The overview marker's former raw `this +0x1c/+0x20` reads are exactly
`route_slots[0].record.map_x/map_y`: the slot array begins at `Galaxy +0x10`,
its record at slot `+0x04`, and the coordinates at record `+0x08/+0x0c`.
The scratch now uses that complete owner chain. Focused Wibo is unchanged at
71.01%, 569/566 instructions, prefix 48, with all 52 operands clean.

## 2026-07-14 canonical root transitions

Mouse input, delayed-widget gating, the mode-1 Exit handoff, and the fade gate
now start from a typed `GameRoot*` and traverse `players[0]`, `border_manager`,
`exit_controller`, and `fade` directly. No function-scoped root borrow was
introduced, preserving the short lifetimes required by the current source
shape. Focused output remains 71.01%, 569/566 instructions, prefix 48/566,
with all 52 operands clean.

## 2026-07-15 Binary Ninja lifecycle replay

The live database records `int32_t __thiscall update_galaxy(cRGalaxy*)` and
resolves its two former anonymous helpers as
`update_galaxy_route_record(GalaxyStar*)` and the true cRGalaxy member
`draw_galaxy_line`. The focused export also retains typed destroy/open/close
transitions and the enclosing subgame backlink. Honest matching is unchanged
at 71.01%, 569/566 candidate/target instructions, prefix 48, and 52 clean
operands.

## 2026-07-24 route-slot cursor ownership

The first route-update pass borrows one element from the Galaxy-owned
`route_slots[101]` bank. Native seeds EBX with `Galaxy +0x10`, calls
`update_galaxy_route_record`, and advances EBX by exactly `0x2a0`, the proven
`sizeof(GalaxyStar)`. Binary Ninja had promoted that induction value to
`GalaxyStar (*)[101]`, which misleadingly presented the borrow as a
pointer to the complete owner and rendered its increment through the whole
array type.

The exact SSA identity (`RegisterVariableSourceType`, index `40`, storage
`69`) now replays as a borrowed `GalaxyStar* route_slot_cursor`. The
tracked decompile consequently shows the one-slot update and
`route_slot_cursor = &route_slot_cursor[1]`. IDA independently retains the
same `GalaxyStar*` loop cursor, so no competing aggregate owner is
needed.

The later hover scan carries the interior
`GalaxyRouteRecord::highlight_target` address in EDI and advances it by the
same slot stride. Reanalysis had degraded that borrow to `int32_t*` because
the loop stores the float constants as raw dword bits. Its exact SSA identity
(`RegisterVariableSourceType`, index `1352`, storage `73`) is now pinned as
`float* highlight_target_cursor`; Binary Ninja again exposes `1f` / `0f`
stores, and IDA independently retains the same float-field cursor. A matching
annotation on the earlier reset loop was tested and explicitly removed:
typing that interior ECX value suppressed Binary Ninja's useful containing
owner inference and expanded each native dword store into four byte writes.

The focused export also catches the artifact up with the already-proved
`g_sound_effect_manager` receiver on the three route open/switch/close feedback
calls. That ABI was recovered in the 2026-07-12 pass; the stale checked-in
Binary Ninja text had still omitted the receiver even though the live
prototype and matcher source were current.

The focused replay fails closed unless `GalaxyStar == 0x2a0` and the
complete `Galaxy == 0x10fa8`; it also removes the rejected reset-loop
experiment before applying the two useful borrows. A second run reports all
three operations already current. This is an analysis-only ownership
clarification. Focused matching remains honestly unchanged at 71.01%,
569/566 instructions, prefix 48/566, with 52 clean and no unresolved or
mismatched masked operands.

## 2026-07-28 mobile GalaxyStar ownership

Android names each `0x2a0` child as `cRGalaxyStar` and calls its standalone
`AI()` method from `cRGalaxy::AI()`. iOS inlines the same method, but preserves
the identical stride and first-field layout. Together with the exact Windows
helper at `0x409bd0`, this establishes the route bank as 101 owned
`GalaxyStar` children rather than anonymous route slots.

The matcher, Binary Ninja replay, and IDA replay now use `GalaxyStar` as the
primary owner while retaining `GalaxyRouteSlot` only as a compatibility
typedef. Matching remains honestly unchanged at 71.01%; this slice recovers
class identity and cross-port provenance, not a compiler-shape trick.

## 2026-07-30 bounded lifetime sweep

Three complete mutation plans tested the remaining evidence-backed compiler
shapes without changing the retained source:

- 11/11 connector `map_y` and card-edge lifetime variants;
- 6/6 route-icon record/name owner-order variants;
- 76/76 mouse-input, tail-borrow, and returned-vector materialization variants.

None of the 93 unique variants improves the 71.01% baseline. Twenty-three
hover variants are byte-identical, while every changed candidate regresses
the fuzzy match or exact prefix. In particular, naming the connector ordinate
moves the first mismatch earlier, direct `active_padding` reloads shrink the
frame and lose the complete prefix, delayed route-record owners lose at least
four weighted bytes, and the source-equivalent vector declaration/assignment
forms compile identically. The current residual is bounded to documented stack-slot and register
colouring until new source or compiler evidence appears.

The same pass exposed six formerly unaudited global references where target
and candidate used the same manifest identity but different destination
registers. The matcher now performs a conservative final reference alignment
on opcode, masked operand position/kind, and canonical identity. Focused
matching remains 71.01%, 569/566 instructions, and prefix 48/566, while the
audit improves from 52 clean plus 6 unaudited entries to 55 clean with no
unresolved, mismatched, or unaudited operands.

## 2026-08-09 primary Galaxy owner surface

The matcher now emits this Windows-combined state machine as
`int cRGalaxy::AI()` and binds `?AI@cRGalaxy@@QAEHXZ`. Its child tick is the
authored `cRGalaxyStar::AI()`, and the internal helper calls now use
`Line`, `UnInit`, `BoxOff`, and `BoxOn`. Binary Ninja confirms the integer
thiscall contract and the three external Windows calls at `0x406893`,
`0x438ce3`, and `0x438d3e`. Mobile splits the render pass and exposes
`AIControl()` separately, while Windows returns that state directly.

The naming-only change leaves the current frontier at 71.01%, 569/566
instructions and prefix 48/566. Before shared alias integration the
ten renamed internal call relocations report as expected operand mismatches;
registering the exact owner-qualified aliases restores the established 55
clean operands. The three receipted mutation plans and experiments ledger are
intentionally byte-identical and remain historical rather than active work.

## 2026-08-14 RealArcade revision boundary

The recovered 2004-11-10 RealArcade-derived executable maps this function at
the same address. Through the next function boundary, the earlier body decodes
to 569 instructions and the 2004-12-04 canonical target to 579. The sole
replacement block is the replay handoff: the earlier body proceeds directly to
`selected_level_record_active = 1`, while the canonical body first writes
`selected_index` to the enclosing subgame's level argument and calls
`cRSubTracks::Load(level_mode, level_mode_arg)`.

This independently confirms the current source placement of the replay load
and proves it is a later source revision, not compiler scheduling. The rest of
the function remains structurally identical modulo relocated addresses, so the
older build does not offer an alternate allocation shape for the documented
canonical residual.

## 2026-09-05 continued loop-owner campaign

Fifteen child-owner combinations test typed route records, indexed tick/line/name loops, indexed hit probes, and color scope. Indexed tick/line/name traversal alone raises **71.01% to 71.19%** with the 48-instruction prefix and all 55 references intact. That tradeoff-free source simplification is retained. The higher-scoring typed-record alternatives regress the prefix and are not retained.

## 2026-09-05 screen-vector and input-decision ownership

Seven `whole-screen-vector-and-record-owners-20260905-mutations.json` forms
compare the screen-XY subtraction helper with the shared vector subtraction
of a zero-z screen position, a named screen vector, and a component result
constructor, together with current or directly owned route-record access.
The two shared subtraction forms are neutral at 71.19%; the constructor
regresses. Owned route records reach 73.13% but shorten the native prefix
from 48 to 25 instructions, so no tradeoff is retained.

The native input tail keeps a game owner and separately reloads its input
pointer for click decisions. The current scratch instead retains the input
pointer and one flags snapshot. Ten game/live-owner and player-owner forms
were attempted in `whole-game-input-decision-lifetimes-20260905-mutations.json`.
Six compile: game pointer/reference owners reach 70.94%, while fresh global
reads reach 67.08%. The four player alternatives accidentally declared
cRSubGoldy instead of the root array's cRPlayer element type and fail to
compile; the digest-bound audit excludes only those invalid plan alternatives.
The separate corrected four-form `whole-player-input-decision-lifetimes-20260905-mutations.json`
replay compiles and reaches 68.95%. All 17 compiling alternatives across the
three receipts retain 55 clean references. No source or shared type change
is retained. The native owner lifetime remains a concrete lead that these
isolated forms do not recover.
