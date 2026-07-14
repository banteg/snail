# update_subgoldy @ 0x43b120 — 74.20%, 2075/2087 insns, structure complete

The boss of bosses (2091 insns, 8456 bytes) has a full scratch: every block
of the function is transcribed and the diff is dominated by
register-allocation residuals, not semantics. The previously-unread
track-mode slice (steering, replay record/playback, completion handoff,
ghost marking, emitters) is now pinned.

2026-06-13 matcher padding rebaseline: terminal object-padding normalization
removes untargeted bytes after final `ret` instructions. The post-rebaseline
baseline was 72.51%, 2067/2087 normalized instructions. This was a measurement
correction, not a source-shape change; the current camera-lifetime recovery is
documented below.

## Semantics recovered beyond the old dossier

The dossier covered the follow-consumer block and the exit lanes. The
scratch additionally pins:

- **Steering model** (the oracle's lateral lane): `track_z_offset` is a
  mouse-anchor accumulator clamped to [0, 639];
  `resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[steering_mode_selector])`
  is called for its side effect each tick; selector 1 maps `steering_x`
  absolutely; steer target = `(320 - offset) * 0.0125` clamped ±3.7;
  `x += rate*0.2 * (target - x)` unless `click_start.state == 2`. Under control
  override the offset is pulled by `-2 * presentation.transform.basis_up.x`.
- **Lateral quantization EVERY tick**: `position.x =
  convert_math_type16_to_32(convert_math_type32_to_16(x, 16.0), 16.0)` —
  live x snaps to the 16-bit replay codec grid each frame before being
  recorded. PORT IMPLICATION: a port that doesn't quantize x identically
  accumulates lateral drift against recordings.
- **Replay record**: z stored as 16-bit per-tick DELTA against the
  accumulator `unk_643194` (which re-accumulates the decoded value, so
  codec error never compounds); flags bit0/bit1 = fire buttons, bit2 =
  latch, bit3 = end marker. Recording flags only written while
  `track_state_latch` (game+0xa854) is set; the latch arms when both fire
  bits are released, or unconditionally at cursor > 20.
- **Replay playback**: recorded lateral_x drives position.x directly;
  flags bit2 drives the latch; bit3 triggers the frontend fade-out
  (app states 26/10 + skip byte).
- **Completion handoff machine**: timer step 1/60; entry resets voice
  gate, clamps vz into [rate*0.17, rate*0.5], `reset_voice_manager`,
  `end_jetpack_hover`, cutscene state 5, sound 0; past start+2.5 decays vz
  by 2×quantum; voice 8 at t>2; skip lanes (display gate_18 + fire, or
  display state 5, level_mode ≤ 1) jump the timer to 5.0999999; t>5 holds
  by re-subtracting the step while display state != 5; then frontend fade
  state 0 → begin fade-out, state 4 → flush display + `complete_subgame`
  dispatch (last-level via app+0x12d4644 - 1 → states 29/26; level 7 →
  26/2; else substate = state, state = persistent ? 26 : 27).
- **Cruise window**: every non-handoff tick with z < completion_row_start
  (or exit pending) and no boost/override: vz floored at rate*0.17 and
  capped at rate*0.5. With the track-mode accel only firing below
  first_block_row_count, the steady-state z-velocity oscillation
  (oracle's 0.24–0.31) must come from the COLLISION boosts (speedup
  pickup and ring effects set vz = rate*0.5) decaying through
  (1 - rate*0.003) toward the 0.17 floor — the "tile-boost cadence"
  hypothesis is dead; it's ring/speedup cadence.
- **Ghost marking (level_mode 4)**: the selected bank has
  `sizeof(SubSolution)` stride; an offset-preserving `SubSolution` view at
  game+0x944150 owns `active`, `source_tail`, `replay_sample_count`, and the
  six-byte `run_records`; ghost z = min(accumulated ghost z, z+20) through
  flt_643190, anchored by player+0x304;
  `set_subgoldy_ghost_z(float)` each tick.
- **Movement-fire emitters**: require runtime_flags & 0x400000, no
  handoff/override, `click_start.state` 0 or 4; fire cooldown via +0x2730
  progress (+0.3 bias on flags_a fire); replay flags bits 1/2 replay the
  fire actions; app+0x1066bf4 < 10 (the 9-tick startup hold) re-arms the
  cooldown.
- **Wall-14 stall**: probe at z+0.49, y < 6.5; vz = 0,
  z = trunc(z+0.49) - 0.5, squidge z -0.33 (sound 47 on first), stall
  timer at +0x328 → carryover when it wraps past 1.0.
- **Tail**: collisions, 5 anim managers (presentation +0x104, jetpack
  channel base +0x11e0 with manager +0x12e8, weapon channel bases
  +0x64c/+0xa28/+0xe04 stride 0x3dc with managers at base +0x108), track parcels
  (`SubgameRuntime::parcel_manager`), initialize_cutscene,
  update_player_movement_flags, `Completion` row-event display,
  `current_high_score_record.replay_sample_count++`, and
  `replay_update_cursor++ == 21000` → `TimesUp`.

## Struct facts (player block)

Exact embedded children now used here are `Nuke` +0x150,
`PlayerRowEventState` +0x1e8, `DamageGuage` +0x3c4, empty `ProgressBar`
+0x3f0, `Warning` +0x3f4, `Snail` presentation +0x2984, and `Squidge`
+0x4344. Damage-gauge state is the first field and skin_hold_ticks is +0x18.
The presentation owns
(`Object* +0x24`; the lateral/squidge writes are its
`ObjectDistort::{z_wave,y_squash,xyz_scale}` at +0x80/84/88, live
basis_up.x +0x48, cutscene state +0x1964), authored cRSquidge +0x4344
(y output/velocity/phase +0x00/+0x04/+0x08, z output/velocity/phase
+0x0c/+0x10/+0x14), slow commentary +0x435c/+0x4360, movement fire +0x2730/4,
slide threshold +0x2738, track_z offset/anchor +0x273c/+0x2740, handoff
cycle +0x2744/8, authored cRSubHover +0x2750 (state +0xc, wobble x/y/alpha
+0x14/18/1c), camera target +0x2964, steering selector +0x2970,
interaction_max_z +0x2980, movement_mode_selector +0x40c (0/2 = early
out), cRClickStart +0xa0 with state +0x120, resurrect_active +0x84,
`PlayerRowEventState::{id,definition}` +0x1e8/+0x1ec, ghost anchor +0x304,
wall stall +0x328/c, exit voice
timer +0x330/4, lane lean +0x350..+0x35c, timer pair +0x360/+0x368/+0x36c,
nuke progress +0x374/8, handoff timer +0x444/8 + gates +0x44c/d/e.

The scratch now uses the shared exact `Squidge` owner directly. Cross-port
symbols and Android bodies identify the four helpers as
`cRSquidge::{Init,StartY,StartZ,AI}`; the old Windows
`initialize_score_stats` name is only a stable harness identifier.

2026-07-12 nested ClickStart ownership: the former flat movement-state lane is
the state at `+0x80` inside the exact 0xac-byte `ClickStart` child embedded at
Player +0xa0. Replacing the scratch-local flat field with the shared owner and
all reads with `click_start.state` is codegen-neutral at 72.51%, 2067/2087
instructions; no register-shaped adapter was retained.

2026-07-12 presentation-object ownership: the scratch-local `VisualRoot` shell
is retired. The Snail's `+0x24` link is the shared animated `Object*`; the
three apparent presentation scalars at object `+0x80/+0x84/+0x88` are exactly
the shared `ObjectDistort` lanes. Focused matching remains 72.51%, 2067/2087,
with all existing operand evidence unchanged.

Game side: the compact outer call view still owns level_mode +0x40 (NOT
+0x150), level_mode_arg +0x44, runtime_flags +0x4c,
first_block_row_count +0x50, runtime_row_count +0x54, and
completion_row_start +0x58. Proven deeper owners now use
`SubgameRuntime::level_definition` (`SubTracks`), `runtime_rows` (`SubRow`,
stride 0xf4), `current_high_score_record`, selected-record replay state,
`replay_update_cursor`, `track_state_latch`, `parcel_manager`,
`subgame_rebuild_selector`, `completion`, and `times_up`. The level-definition
message lanes are `SubTracks::segment_slots[event_id - 1]` fields rather than
an anonymous +0xa670/16928 table. Root fields now use
`GameRoot::{backdrop,tip_manager}` and
`GameRoot::subgame.{galaxy.record_count,replay_update_cursor}`. `AppShell`
owns the copied 0x40-byte HUD rows and names the +0x34 lane
`scroll_progress`; its destination lands at root +0x300.

2026-06-16 controller consolidation audit: row-event, warning, and nuke all
have shared headers (`completion.h`, `warning.h`,
`nuke.h`) validated by their focused scratches. Keep the local
prefix views in this scratch for now. Those headers pull in
`frontend_widget.h`/`sprite.h`/`vector3.h`, which conflicts with this file's
scratch-local POD `Vector3`/`TransformMatrix` transcription before codegen.
The remaining `Warning` type report hit is therefore an include-boundary
issue, not evidence for a second warning layout. Promote these only after the
whole player scratch moves to the shared math/sprite headers.

2026-06-16 player header follow-up: `player.h` now promotes the nuke subobject
at `Player +0x150` and the presentation cutscene state at
`presentation +0x1964` (`Player +0x42e8`). This matches the struct facts above
and the collision scratch's ring-nuke and slug first-hit consumers. The
`update_subgoldy` scratch still keeps the local controller/presentation views
for the include-boundary/codegen reason described here.

2026-06-16 follow-up probe: replacing only the local POD `Vector3` with
`vector3.h` compiles and preserves the instruction count, but regresses the
masked jump-table audit from `291 ok` to `290 ok, 1 mismatch`
(`update_subgoldy_follow_jump_table` vs `$L1508`). Keep the local vector too;
the blocker is relocation shape, not just a duplicate type definition.

2026-06-16 row-record consolidation probe: adding a local
`TrackAttachmentRuntimeRow` mirror and using `row_record->row_event_id` in the
row-event block also preserved the headline score but regressed the masked
jump-table audit to `290 ok, 1 mismatch`. Reverted for the same reason as the
`Vector3` probe. The row-record layout is already cross-confirmed by
`place_parcels_on_track` and the exact `get_track_runtime_cell_at_world_z`
helper; do not rewrite this scratch's row-event block until the broader
source-shape issue is solved.

## Source-shape idioms that mattered

- Doubled quantum is `quantum + quantum` via a named local (fadd st0,st0),
  never two products (VC6 folds those into one const).
- Gravity sites need `float gravity = rate*rate*-0.0099999998f;` as a
  named local or VC6 rewrites `+ x*-c` into `- x*c` (fsubr).
- Clamp ladders are written negative-arm-first
  (`if (x < lo) ... else if (x > hi) ...`).
- The pending/floor and floor/gravity branches are polarity-flipped
  (`if (!pending) {floor} else {trampoline}`, `if (floor > y) {snap}
  else {gravity}`) so the trampoline/gravity blocks land last and fall
  into the continuation.
- The follow switch is source-ordered case 1/3 first, case 0 falling
  through into case 2.
- The position stash around the camera block is a Vector3 struct copy
  (dead y/z stores survive), and the camera writes go through a
  `Vector3*` local (lea-reused base).
- The tile-14 wall probe and camera wobble offset are separate lexical
  `Vector3` owners. Their lifetimes do not overlap, so VC6 coalesces them into
  the same stack slot; decompilers consequently show one reused `position`
  local. Keeping the wall probe scoped restores the native 0x40-byte frame.
- Camera wobble is one ordinary vector expression:
  `right*wobble_x + up*wobble_y + forward*wobble_alpha`, accumulated into the
  cached camera target. VC6 evaluates the terms forward, up, right and then
  performs `(right + up) + forward`, matching the native x87 sequence.
- The steering lerp needs `pull` and `steer_delta` locals to force the
  fxch evaluation order.
- 2026-06-15 type-consolidation probe: replacing the local `Vector3`
  with shared `vector3.h` preserved the headline score but introduced a
  masked operand mismatch, so this scratch keeps its local view for now.
- 2026-06-15 attachment-layout probe: expanding the local
  `AttachmentSample`/`Path`/`TrackRowCell` views to the
  shared-header field names also preserved the headline score but shrank the
  stack frame and introduced the same jump-table masked mismatch. Keep the
  compact local attachment view until a source-shape fix explains the frame.
- 2026-06-16 tip-manager probe: replacing the local `TipDefinition`/`TipManager`
  view with shared `tip_manager.h` preserved the headline score and instruction
  count but changed the masked audit from 291 ok / 0 mismatch to 290 ok / 1
  jump-table mismatch. Keep this scratch's compact local tip view for now.
- 2026-06-16 timer-counter probe: replacing the local compact timer call view
  with the then-shared header and offset-preserving padding produced the same
  masked-audit regression. The later offset-preserving player view admits the
  shared authored `Time` value at +0x2e8 without reopening that layout change.
- 2026-06-16 voice-manager probe: replacing the local compact
  `VoiceManager` call view with shared `voice_manager.h` preserved the headline
  score but produced the same 290 ok / 1 jump-table masked-audit regression.
  Keep the compact local voice view until the follow-switch layout issue is
  fixed.
- 2026-06-16 audio-system probe: replacing the local compact
  `SoundEffectManager` call view with shared `audio_system.h` produced the same
  290 ok / 1 jump-table masked-audit regression. Keep the compact local sound
  view until the follow-switch layout issue is fixed.
- 2026-06-17 animation-channel correction: the repeated weapon/jetpack
  presentation blocks are full `PresentationAnimationChannel` objects, not
  manager-starting lanes. `selected_state` lives at channel `+0x104`, the
  `AnimManager` at channel `+0x108`, and the channel stride is `0x3dc`.
  `update_subgoldy` can use the shared channel header without changing its
  headline score; this replaces the stale local `WeaponChannel` view.
- 2026-06-20 app-shell consolidation: `AppShell` now lives in
  `app_shell.h`, with the shared `FrontendFade` split out of the former sparse
  border-delay view so this scratch does not pull in
  `frontend_widget.h`/`sprite.h`. `update_subgoldy` remains 72.51% with the
  same masked jump-table mismatch; `update_subgoldy_resurrect` and the small
  fade callers stayed exact. The type report no longer has an `AppShell`
  partial-compatible row. `FrontendFade` is now a remaining unresolved-layout
  cleanup because `game_startup_and_main_loop` still keeps a minimal local
  startup-only declaration.
- 2026-06-20 follow ABI cleanup, corrected 2026-07-13: the local `FollowState`
  declaration now matches the recovered void initializer and const
  world-position parameter from `track_attachment_types.h`. This is codegen
  neutral and leaves `update_subgoldy` at 72.51%, `2067/2087`, with the same
  `290 ok / 1` jump-table masked audit. Rewriting the two swept attachment
  re-entry callsites from by-value `Vector3` arguments to six explicit scalar
  floats is rejected for this caller shape: it fell to 71.14%, `2057/2087`,
  and `288 ok / 1`.
- 2026-06-20 shared call-surface cleanup: `VoiceManager`,
  `SoundEffectManager`, `TipManager`/`TipData`, and `Backdrop`
  now come from their shared headers instead of compact local stubs. This is
  codegen neutral at the current baseline (`72.51%`, `2067/2087`, same
  `290 ok / 1` jump-table audit). Type report impact: `TipManager` is removed
  from the conflict list, `update_subgoldy` drops out of the `VoiceManager` and
  `SoundEffectManager` rows, and `Backdrop` no longer lists this scratch, though
  the type tool still reports a header-only `Backdrop` residual.
- 2026-06-20 attachment view naming: the compact local attachment/follow
  declarations are now named `SubgoldyPathView`,
  `SubgoldyTrackRowCellView`, and `SubgoldyFollowStateView`. This preserves the
  by-value swept-entry caller shape that beat the scalar shared-header call
  spelling above, while making the type report stop advertising these local
  views as ready-to-promote `Path`, `TrackRowCell`, or
  `FollowState` copies. Focused evidence stayed unchanged at `72.51%`,
  `2067/2087`, and the same `290 ok / 1` jump-table masked audit.
- 2026-07-11 cRPath ownership: symbol-preserving ports identify the shared
  `0xa8` owner as `cRPath`, so the compact local view now follows that authored
  vocabulary without pretending to be the complete shared `Path` declaration.
  The rename is codegen neutral at the same focused baseline.
- 2026-07-11 parcel manager owner: the tail now dispatches through the shared
  `ParcelManager` at game `+0x125e480`, removing the local one-method
  `TrackParcels` shell. The later canonical-player promotion below supersedes
  the temporary broad player transcription. This remains codegen-neutral at
  `72.51%`, `2067/2087`, with the same `290 ok / 1` real follow-jump-table
  mismatch.
- 2026-07-11 cRCompletion view naming: the compact local display prefix is now
  `SubgoldyCompletionView`, reflecting that all `+0x12727d8` calls and gates
  belong to the authored embedded `Completion`. The full shared header still
  pulls the frontend sprite/math surface that this scratch deliberately keeps
  local; renaming the prefix removes the fake independent controller without
  perturbing the 72.51% baseline or its 290-clean/one-table audit.
- 2026-07-11 cRTimesUp view naming: the terminal timer calls now use
  `SubgoldyTimesUpView`, a compact prefix of the authored `TimesUp` at
  `+0x1272828`. Exact update/uninit/init siblings and the native size ledger
  prove the shared owner; keeping the local prefix avoids the same frontend
  include boundary and leaves this caller byte-stable.
- 2026-06-20 remaining local view naming: the warning, control-source, and
  cutscene subviews are now named `SubgoldyWarningView`,
  `SubgoldyPlayerControlSourceView`, and `SubgoldyCutSceneStateView`.
  Including the shared warning/player headers is still rejected for the
  include-boundary reasons above, but the type report no longer advertises
  these compact local slices as promotable `Warning`, `PlayerControlSource`,
  or `CutScene` definitions. Focused evidence stayed unchanged at `72.51%`,
  `2067/2087`, and the same `290 ok / 1` jump-table masked audit.
- 2026-06-20 Player ABI cleanup, superseded 2026-07-14: the temporary local
  method surface was aligned with `player.h` for `initialize_subgoldy_death()` and
  `update_player_movement_flags()` returning `int`. Their return values are
  still ignored at the callsites in this large update body, so focused Wibo
  remains `72.51%`, `2067/2087`, with the same `290 ok / 1` jump-table masked
  audit. The complete shared owner now compiles identically.
- 2026-06-21 Player type-row cleanup, superseded 2026-07-14: the temporary
  `SubgoldyPlayerView` prevented a misleading type merge while the shared
  header was incomplete. It is now retired; the body defines
  `Player::update_subgoldy()` directly with unchanged focused evidence.
- 2026-06-20 Game ABI cleanup, superseded 2026-07-14: the temporary
  `SubgoldyGameView` preserved the caller-local
  `float sample_track_floor_height_at_position(...)` return view that keeps the
  native `fadd dword` shape here; forcing the standalone helper's exact
  `double` return into this large caller regressed to `72.46%` and `289 ok / 1`.
  The real owner is now canonical `SubgameRuntime*`; only a fieldless
  `SubgoldyFloorSamplerCallView` retains that return-type ambiguity because
  MSVC does not encode it in the thiscall symbol. Focused Wibo remains
  `72.51%`, `2067/2087`, with the same `290 ok / 1` jump-table masked audit.

## 2026-07-13 canonical child and runtime ownership pass

The shared headers have matured enough to supersede the earlier local-prefix
guidance without perturbing this scheduling-sensitive body:

- The then-local player view adopted the exact shared `Nuke`,
  `PlayerRowEventState`, `Warning`, `Snail`, and `Squidge` children, and uses
  `PlayerControlSource*`. The scratch-local completion, times-up, nuke,
  warning, control-source, presentation, cutscene, and squidge shells are gone.
- Runtime row reads use the canonical `SubRow` slab. Authored row-event text,
  duration, and sample id come from
  `SubgameRuntime::level_definition.segment_slots`, whose owner is
  `SubTracks`.
- Replay and completion lanes now name the canonical selected-record state,
  `current_high_score_record`, `replay_update_cursor`, `track_state_latch`,
  `subgame_rebuild_selector`, `Completion`, `TimesUp`, and `ParcelManager`
  members of `SubgameRuntime`.
- Root accesses now name `GameRoot::backdrop`, `tip_manager`, the Galaxy record
  count, and the replay cursor. `AppShellHudRow::scroll_progress` closes the
  copied HUD row's live +0x34 lane.
- The Time Trial ghost bank still uses an offset-preserving base followed by a
  canonical `SubSolution` view. Spelling the same object directly through
  `SubgameRuntime::sub_high_score.time_trial_route_records[level_mode_arg]`
  regressed this caller to 70.68% and 285 clean operands; it was rejected as a
  source-schedule change, not retained as a cosmetic ownership win.

Focused Wibo remains `72.51%`, `2067/2087`, with 290 clean masked operands and
the same one honest `update_subgoldy_follow_jump_table` mismatch. No waiver,
assembly shim, or other fakematch was added.

## Named residuals (all register-allocation / micro-shape class)

1. esi/edi zero-register swap born at the wall-14 block (`xor esi,esi`
   native vs `xor edi,edi` here) — cascades through the whole tail.
2. eax/ecx/edx scratch rotation shifted by one from the z-record site:
   native splits the game load (`mov edx,[0x408]; mov esi,edx`), ours
   loads esi directly; the missing split shifts every later scratch pick.
3. The three replay-flag ORs: native `or byte [sib+disp], imm` followed
   by a DEAD `lea eax,[sib+disp]`; no source shape found yet that emits
   the dead lea (likely the same idiom in all three).
4. Frame 0x24 vs 0x40: native keeps more spilled temps (the wall-probe
   y/z temps, v136/v137 camera sums, the x-quantize temp survive as
   distinct slots).
5. `(320 - offset)`: native `fld var; fsubr const`, ours
   `fld const; fsub var`.
6. The two window clamps compare via `fld vz; fcomp st(1)` (vz loaded)
   vs our `fcom [vz]`.
7. Free-lane z / case-2 x integrate operand commutation (velocity-first
   vs position-first) — VC6 commutes one site each way regardless of
   source order so far.

2026-07-11 damage-owner recovery: the compact scratch-local gauge view at
player +0x3c4 is replaced by the shared exact 0x2c-byte `DamageGuage`
owner. Android `cRSubGoldy::AI()` calls `cRDamageGuage::AI()` through that
embedded object, while the Windows jetpack controller at +0x2750 remains a
separate neutral composite. Focused Wibo remains 72.51%, 2067/2087
  instructions, with 290 clean masked operands and one jump-table mismatch.

2026-07-11 warning-owner recovery: the compact local warning prefix is renamed
`SubgoldyWarningView` to reflect the authored `cRWarning` owner proven by
Android and iOS. The full shared header remains intentionally outside this
large scratch's local math boundary. Focused Wibo remains 72.51%, 2067/2087
instructions, with 290 clean masked operands and one jump-table mismatch.

2026-07-11 nuke-owner recovery: the compact local prefix at Player +0x150 is
now named `SubgoldyNukeView`, reflecting Android and iOS `cRNuke` without
advertising a second full definition. Android
`cRSubGoldy::AI()` owns both the AI and UnInit call edges through this embedded
object. Focused Wibo remains 72.51%, 2067/2087 instructions, with 290 clean
masked operands and one jump-table mismatch.

2026-07-11 progress-owner recovery: Android and iOS identify the two HUD calls
as `cRProgressBar::AI()`. The shared owner at Player +0x3f0 is now an empty
one-byte class with alignment before cRWarning, matching both the unused
receiver and mobile no-op lifecycle. Focused Wibo remains 72.51%, 2067/2087
instructions, with 290 clean masked operands and one jump-table mismatch.

## Zig port residuals (carried from the pre-scratch dossier, still open)

1. native resets the live-matrix rotation to identity in the grounded
   snap; the port only clears the airborne flag (presentation-level).
2. the trampoline envelope uses a shipped-tile floor-height proxy for the
   cell anchor y (the checklist correction stands).
3. +0x41c boost lane is DEAD CODE in the shipped binary (only ever
   written 0) — the port correctly omits it.
4. NEW (this scratch): the per-tick 16-bit lateral quantization and the
   replay z-delta accumulator are not modeled in the port — audit
   `stepActivePhase`/the oracle harness for codec parity on x.

## 2026-07-14 cell and follow ownership consolidation

- The scratch-local runtime-cell shell is gone. Grid lookup, row-event,
  slide, landing, and trampoline paths now use the complete authored `SubLoc`
  owner, including the primary/secondary attachment cells borrowed from
  canonical `SubRow` records.
- The duplicate 0x40-byte follow shell is replaced by the shared `FollowState`
  (`cRPathFollowGoldy`) owner. Its exact `Path*`, `SubLoc*`, and `Player*`
  relationships now cover both begin and update calls.
- A full promotion of the remaining caller-local `SubgoldyPathView` was
  tested and rejected: spelling the swept-entry call through the shared
  scalar-argument `Path` surface changed the VC6 aggregate push sequence,
  regressing the target to 70.41%, 2043/2087 instructions and 282 clean
  operands. The compact path prefix therefore remains explicitly documented
  as a source-shape view of the shared owner, not a second owner.

The accepted cell/follow consolidation is byte-identical at 72.51%,
2067/2087 instructions, 290 clean operands, and the same one honest follow
jump-table mismatch.

## 2026-07-14 player follow-state ownership

The canonical `Player` now embeds that same 0x40-byte `FollowState` at +0x384;
the former twelve flattened player aliases are retired. Nine independent
callers now traverse the authored `Player::follow_state` owner, including the
exact initializer and exit-carryover producer. All nine focused binaries are
byte-identical to their pre-consolidation baselines; `update_subgoldy` itself
remains 72.51%, 2067/2087 instructions, 290 clean operands, with the same one
honest jump-table mismatch.

## 2026-07-14 canonical player and subgame ownership

The remaining broad player/game local owners are retired. `update_subgoldy` is now the
canonical `Player::update_subgoldy()` method, and `Player +0x38` exposes the full
0x40-byte render transform rather than only its position row. The
shared player also names the replay anchor, tile-14 wall-stall window,
exit-voice timer, and timer-360 state used here. Every outer runtime access now
uses the borrowed canonical `SubgameRuntime*` backlink.

One fieldless caller-ABI view remains for
`sample_track_floor_height_at_position`: the standalone exact helper body is
source-exact under `double`, while this native callsite proves float arithmetic
with `fadd dword`. Keeping that return view restores the native callsite
without duplicating runtime storage or inventing data ownership.

The full promotion is byte-identical at 72.51%, 2067/2087 instructions, 290
clean operands, and the same one honest follow jump-table mismatch.

## 2026-07-14 Player renderable inheritance

The canonical Player now inherits the complete `RenderableBod` prefix, so all
movement, collision, replay, camera, and attachment paths use inherited
`transform` rather than a duplicated `live_matrix` field. GolbShot,
Cameraman, CutScene, and presentation-channel matrices remain distinct owners.
This scratch is byte-identical at 72.51%, 2067/2087 instructions, 290 clean
operands, and the same one honest follow jump-table mismatch.

## 2026-07-14 presentation renderable inheritance

`Player::presentation` now inherits the complete `RenderableBod` prefix; its
lateral steering basis is `presentation.transform.basis_up`, not a separately
owned matrix with the same offset. The large focused partial remains
byte-identical at 72.51%, 2067/2087 instructions, 290 clean operands, and the
same one honest jump-table mismatch.

## 2026-07-14 wall-probe and camera-offset lifetimes

The former scalar camera transcription is replaced by the authored vector
shape. Native assembly computes three scaled render-basis vectors, combines
`(basis_right * wobble_x + basis_up * wobble_y) + basis_forward * wobble_alpha`,
and adds that aggregate to `cached_camera_target_world`. The wall collision
probe is now confined to its collision block, while the later wobble result is
a distinct `camera_offset`. Those two owners have disjoint lifetimes and VC6
reuses their stack storage, explaining why IDA presents both as one `position`
variable without requiring source-level aliasing.

This ownership/lifetime recovery raises the focused match from 72.51%,
2067/2087 instructions to 74.20%, 2075/2087. It also restores the exact native
0x40-byte stack frame and a 12-instruction exact prefix. The operand audit
remains 290 clean operands and the same one honest follow jump-table mismatch.

Rejected probes were retained only as measurements, not source: leaving the
wall probe live through the camera expression produced a 0x4c frame and at
best 73.54%; explicit component constructors reached 73.32% or 72.87% with the
same oversized frame; and a purely sequential `operator+=` chain shrank the
frame to 0x34 and fell to 72.37%. No padding, volatile storage, fake fields, or
register-shaped adapters were introduced.
