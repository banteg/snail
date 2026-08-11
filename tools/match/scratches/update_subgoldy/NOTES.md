# update_subgoldy @ 0x43b120 — 82.75%, 2087/2087 insns, structure complete

The boss of bosses (2087 normalized instructions, 8456 bytes) has a full
scratch: every block of the function is transcribed and the diff is dominated
by register-allocation residuals, not semantics. The track-mode slice
(steering, replay record/playback, completion handoff, ghost marking,
emitters) is pinned. Dual-mobile evidence now aligns the native follow scalar,
both cruise-window speed snapshots, and the complete Windows wall-probe value
copy.

## 2026-08-09 active-window lower-bound closure

Windows `0x43cdfc..0x43ce29` computes one exact per-tick plane and stores it at
`Player +0x2980`:

```text
active_window_min_z = min(completion_row_start - 30, player_z - 8)
```

The live Binary Ninja field index contains 23 unique instruction sites: the
initializer and this producer, plus 21 reads across 15 functions. Every reader
uses `+0x2980` as a lower/trailing boundary, not a maximum:

- health, speedup, jetpack, ring, garbage, slug, salt, and ordinary `cRSubLoc`
  objects retire after their z falls below the plane;
- `SubLazer` runs its floor/attachment collision probes only at or above it,
  and Golb shots run contact sweeps only inside
  `[active_window_min_z, player_z + 46]`;
- fringe objects, cached BOD rows, and row models recycle behind the same
  plane, with their authored extent adjustments;
- parcels keep an extra ten-row teardown margin; path-entry `cRSubLoc` records
  keep their template span plus five rows;
- `update_subgame` derives the forward runtime-row scan end as
  `(int)active_window_min_z + 46`.

Android `cRSubGoldy::AI()` at `0x7ac54` and iOS at `0x277f8` independently
retain the same player-relative `player_z - 8` minimum and a completion-side
cap. The mobile decompilations spell that cap as
`VectorSignedToFloat(route_endpoint) + 30`, rather than the Windows integer
`completion_row_start - 30`; this proves the two-bound lifetime but does not
justify importing either platform's route representation into the other.
Their corresponding pickup, ring, Golb, garbage, and slug readers use the
stored player field with the same alive/cull polarity.

Ownership is therefore correct: this is authored `cRSubGoldy`/`Player` state,
produced by its AI and borrowed by the track runtime. The former shared field
name was stale and polarity-inverted; `active_window_min_z` describes both
lifecycle and interaction consumers. The producer first adopted
that semantic local name, and the completed shared rename remains
codegen-neutral at 82.75%, 2,087/2,087
instructions, prefix 12/2,087, with 315 clean masked operands, no unresolved
or mismatched operands, and the same one visible unaudited `g_game` load.

## 2026-07-27 cruise and wall-value lifetime pass

Both mobile bodies retain two instances of the completion/cruise clamp with
the current z velocity held in one scalar while the `rate * 0.17` and
`rate * 0.5` bounds are formed. Giving each Windows clamp the same scoped
`speed` snapshot raises the focused result from 80.64% to 81.88%, with
2,080/2,087 candidate instructions. The ordinary cruise snapshot contributes
the first 1.08 points and the handoff-entry snapshot a further 0.16 points.

The wall-14 probe supplies a stronger aggregate fact. Android constructs
three adjacent `local_54/local_50/local_4c` lanes and passes that value to
`cRSubGame::LocFromPos(tVector)`. iOS first constructs
`local_70/fStack_6c/local_68`, then copies all three lanes to
`local_4c/local_48/local_44` at the lookup boundary. Windows independently
shows the same two records: it writes x/y/z at stack +0x14, copies them to
+0x20, and passes the second record to the exact pointer-ABI helper.

Spelling those as scoped `wall_probe` and `wall_lookup` values, with the
source probe formed by adjusting z before copying x/y, recovers the entire
Windows instruction sequence from the z load through the lookup call exactly.
The overall focused receipt rises to 82.67%, with 2,086/2,087 candidate
instructions, prefix 12/2,087, 314 clean masked operands, no unresolved
operands, no mismatches, and three visible unaudited global loads. The
standalone Windows helper remains a pointer call; a probe that changed its
signature to the mobile by-value ABI regressed and was rejected.

A direct one-expression transliteration of the mobile steering lerp regressed
the focused score and was rejected. The retained changes recover cross-port
value lifetimes and preserve the clean operand audit; none are register-only
source scheduling.

## 2026-07-27 mobile scalar lifetime pass

Android and iOS both retain the authored `cRSubGoldy::AI()` body. In the
Android body the path-follow speed is carried in `fVar26` into
`cRPathFollowGoldy::Traverse`; iOS carries the analogous velocity component
in `local_f4`, passes that scalar to `Traverse`, and updates the same component
in the returned-mode cases. This is evidence for a value snapshot across the
call, not a second velocity owner or a borrowed pointer. Spelling the Windows
source accordingly as `float follow_speed = velocity.z` before
`update_track_attachment_follow_state` recovers VC6's native register
allocation without importing a mobile layout.

That one lifetime change raises the focused result from 74.43% at 2070/2087
instructions to 80.36% at 2072/2087. The masked audit moves from 305 clean,
one jump-table mismatch, and 19 unaudited operands to 313 clean, no mismatch,
and five unaudited operands. In particular, all four ordered destinations of
the follow-mode switch become honestly aligned.

The mobile bodies also preserve the steering calculation as two semantic
steps: form `320 - track_z_offset`, scale it, then apply
`(target - position.x) * rate * 0.2`. Splitting the corresponding Windows
locals at those operation boundaries recovers the native x87 subtraction
order while leaving the computation unchanged. With both steering lifetimes,
the final focused receipt is 80.64%, 2072/2087 instructions, prefix 12/2087,
with 314 clean masked operands, no unresolved operands, no mismatches, and
three unaudited global loads. Those three remain visible rather than being
waived or inferred; no mask or matcher relaxation is part of this source
change.

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
  `cRSubHover::End`, cutscene state 5, sound 0; past start+2.5 decays vz
  by 2×quantum; voice 8 at t>2; skip lanes
  (`cRCompletion::fast_forward_enabled` + the primary-button press edge, or
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
  game+0x944150 owns `active`, `replay_start_cursor`, `replay_sample_count`, and the
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
  (`cRSubGame::parcel_manager`), update_snail_presentation,
  set_subgoldy_shoot_flags, `Completion` row-event display,
  `current_high_score_record.replay_sample_count++`, and
  `replay_update_cursor++ == 21000` → `TimesUp`.

## Struct facts (player block)

Exact embedded children now used here are `Nuke` +0x150,
`PlayerRowEventState` +0x1e8, `DamageGuage` +0x3c4, empty `ProgressBar`
+0x3f0, `Warning` +0x3f4, `Snail` presentation +0x2984, and `Squidge`
+0x4344. Damage-gauge state is the first field and skin_hold_ticks is +0x18.
The presentation owns
(`Object* +0x24`; the lateral/squidge writes are its
`Distort::{z_wave,y_squash,xyz_scale}` at +0x80/84/88, live
basis_up.x +0x48, cutscene state +0x1964), authored cRSquidge +0x4344
(y output/velocity/phase +0x00/+0x04/+0x08, z output/velocity/phase
+0x0c/+0x10/+0x14), slow commentary +0x435c/+0x4360, movement fire +0x2730/4,
slide threshold +0x2738, track_z offset/anchor +0x273c/+0x2740, handoff
cycle +0x2744/8, authored cRSubHover +0x2750 (state +0xc, wobble x/y/alpha
+0x14/18/1c), camera target +0x2964, steering selector +0x2970,
active_window_min_z +0x2980, movement_mode_selector +0x40c (0/2 = early
out), cRClickStart +0xa0 with state +0x120, resurrect_active +0x84,
`PlayerRowEventState::{id,definition}` +0x1e8/+0x1ec, ghost anchor +0x304,
wall stall +0x328/c, exit voice
timer +0x330/4, lane lean +0x350..+0x35c, timer pair +0x360/+0x368/+0x36c,
nuke progress +0x374/8, handoff timer +0x444/8 + gates +0x44c/d/e.

The scratch now uses the shared exact `Squidge` owner directly. Cross-port
symbols and Android bodies identify the four helpers as
`cRSquidge::{Init,StartY,StartZ,AI}`; the old Windows
`initialize_score_stats` name is no longer attached to
`initialize_squidge`. Android and iOS bodies identify exact Windows helper
`clear_subgoldy_score_buckets` as `cRSubGoldy::ScoreStatsInit()`, so the
compatibility name now follows the real score-stat owner.

2026-07-12 nested ClickStart ownership: the former flat movement-state lane is
the state at `+0x80` inside the exact 0xac-byte `ClickStart` child embedded at
Player +0xa0. Replacing the scratch-local flat field with the shared owner and
all reads with `click_start.state` is codegen-neutral at 72.51%, 2067/2087
instructions; no register-shaped adapter was retained.

2026-07-12 presentation-object ownership: the scratch-local `VisualRoot` shell
is retired. The Snail's `+0x24` link is the shared animated `Object*`; the
three apparent presentation scalars at object `+0x80/+0x84/+0x88` are exactly
the shared `Distort` lanes. Focused matching remains 72.51%, 2067/2087,
with all existing operand evidence unchanged.

Game side: the compact outer call view still owns level_mode +0x40 (NOT
+0x150), level_mode_arg +0x44, runtime_flags +0x4c,
first_block_row_count +0x50, runtime_row_count +0x54, and
completion_row_start +0x58. Proven deeper owners now use
`cRSubGame::level_definition` (`SubTracks`), `runtime_rows` (`SubRow`,
stride 0xf4), `current_high_score_record`, selected-record replay state,
`replay_update_cursor`, `track_state_latch`, `parcel_manager`,
`subgame_rebuild_selector`, `completion`, and `times_up`. The level-definition
message lanes are `SubTracks::segment_slots[event_id - 1]` fields rather than
an anonymous +0xa670/16928 table. Root fields now use
`GameRoot::{backdrop,tip_manager}` and
`GameRoot::subgame.{galaxy.record_count,replay_update_cursor}`. The copied
0x40-byte completion handoff is a `TransformMatrix` snapshot from inherited
`GamePlayer::transform` to `GamePlayer::completion_handoff_transform`; the
destination Y position lands at root `+0x300`.

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
  `AttachmentSample`/`Path`/`cRSubLoc` views to the
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
  presentation blocks are full authored `Weapon` objects, not
  manager-starting lanes. `selected_state` lives at channel `+0x104`, the
  `AnimManager` at channel `+0x108`, and the channel stride is `0x3dc`.
  `update_subgoldy` can use the shared channel header without changing its
  headline score; this replaces the stale local `WeaponChannel` view.
- 2026-06-20 app-shell consolidation, superseded 2026-07-14: the temporary
  `AppShell` lived in `app_shell.h`, with the shared `FrontendFade` split out
  of the former sparse border-delay view so this scratch did not pull in
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
  views as ready-to-promote `Path`, `cRSubLoc`, or
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
- 2026-06-20 Player ABI cleanup, superseded 2026-07-25: the temporary local
  method surface was aligned with `player.h` for `initialize_subgoldy_death()`.
  Android has since closed the second call as the authored void
  `cRSubGoldy::SetShootFlags()` mutator; its incidental Windows EAX residue was
  already ignored at this callsite. The `SetShootFlags` manifest alias keeps
  that call's masked operand clean; current focused Wibo remains `74.43%`,
  `2070/2087`, with `290 ok / 1` remaining compiler-local jump-table mismatch.
- 2026-06-21 Player type-row cleanup, superseded 2026-07-14: the temporary
  `SubgoldyPlayerView` prevented a misleading type merge while the shared
  header was incomplete. It is now retired; the body defines
  `Player::update_subgoldy()` directly with unchanged focused evidence.
- 2026-06-20 Game ABI cleanup, superseded 2026-07-14: the temporary
  `SubgoldyGameView` preserved the caller-local
  `float sample_track_floor_height_at_position(...)` return view that keeps the
  native `fadd dword` shape here; forcing the standalone helper's exact
  `double` return into this large caller regressed to `72.46%` and `289 ok / 1`.
  The real owner is now canonical `cRSubGame*`; only a fieldless
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
  `cRSubGame::level_definition.segment_slots`, whose owner is
  `SubTracks`.
- Replay and completion lanes now name the canonical selected-record state,
  `current_high_score_record`, `replay_update_cursor`, `track_state_latch`,
  `subgame_rebuild_selector`, `Completion`, `TimesUp`, and `ParcelManager`
  members of `cRSubGame`.
- Root accesses now name `GameRoot::backdrop`, `tip_manager`, the Galaxy record
  count, and the replay cursor. The temporary `AppShellHudRow` interpretation
  was retired by the root-owner proof below.
- The Time Trial ghost bank still uses an offset-preserving base followed by a
  canonical `SubSolution` view. Spelling the same object directly through
  `cRSubGame::sub_high_score.time_trial_route_records[level_mode_arg]`
  regressed this caller to 70.68% and 285 clean operands; it was rejected as a
  source-schedule change, not retained as a cosmetic ownership win.

Focused Wibo remains `72.51%`, `2067/2087`, with 290 clean masked operands and
the same one honest `update_subgoldy_follow_jump_table` mismatch. No waiver,
assembly shim, or other fakematch was added.

## 2026-07-14 frontend bridge root-owner closure

The duplicate `AppShell` lens is retired in favor of the canonical `GameRoot`
and its first owned `GamePlayer`:

- Root `+0x1b8/+0x1bc` are player-relative `+0x94/+0x98`, the existing
  `frontend_state` and `saved_frontend_state` fields.
- Root `+0x30c/+0x30d` are player-relative `+0x1e8/+0x1e9`, the existing
  `redispatch_requested` and `high_score_entry_pending` flags.
- Native copies `0x40` bytes from root `+0x15c` (player-relative `+0x38`, the
  inherited `RenderableBod::transform`) to root `+0x2cc` (player-relative
  `+0x1a8`), then subtracts `1.0f` from destination `+0x34`. That is exactly
  `TransformMatrix::position.y`, proving the destination as
  `completion_handoff_transform` rather than a synthetic HUD row.

Focused compilation remains an honest partial at `74.30%` (target `2087`,
candidate `2072`), with `290` clean masked operands and the same one
`update_subgoldy_follow_jump_table` mismatch. No score-shaping change or
fakematch was added.

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

2026-07-16 replay flag-word closure: the expanded six-byte replay sample owns
one 16-bit `flags` field at `+0x04`; compact persistence merely stores its low
byte. Replaying that true layout improves the focused result from 74.30%
(2072/2087) to 74.43% (2070/2087), retaining 290 clean masked operands and the
single audited follow jump-table mismatch. No source scheduling was changed.

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

## 2026-07-14 cell and follow ownership consolidation

- The scratch-local runtime-cell shell is gone. Grid lookup, row-event,
  slide, landing, and trampoline paths now use the complete authored `cRSubLoc`
  owner, including the primary/secondary attachment cells borrowed from
  canonical `SubRow` records.
- The duplicate 0x40-byte follow shell is replaced by the shared `FollowState`
  (`cRPathFollowGoldy`) owner. Its exact `Path*`, `cRSubLoc*`, and `Player*`
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
uses the borrowed canonical `cRSubGame*` backlink.

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

## 2026-07-14 ghost record-bank owner derivation

The offset-preserving ghost cursor remains intact, but its former `0x944150`
bank base now derives from `offsetof(cRSubGame, sub_high_score) +
offsetof(SubHighScore, time_trial_route_records)`. This identifies the exact
owned time-trial bank while retaining the native `sizeof(SubSolution) *
level_mode_arg` evaluation order that the direct indexed-member spelling had
regressed.
The macro-expanded cursor preserves the normalized candidate listing
byte-for-byte
(`56d9084051f977d866ddf7443f41deab0d9a04521c830d3e2d4f3d96da2003cb`)
and the honest 74.20% focused result (`2075/2087`, prefix `12/2087`, 290 clean
operands, one bounded jump-table mismatch).

## 2026-07-14 player-side SubRow flags

Primary and secondary swept path entry now use the shared attachment-span
bits. The authored `NoFall` lane is also closed through its only proved player
consumer: when the bit is absent after an attachment exit, forward z velocity
receives rate-scaled drag; when present, that drag is skipped. Focused output
is byte-identical at 74.20%, 2075/2087 instructions, prefix 12/2087, 290 clean
operands, and the same bounded jump-table mismatch.

## 2026-07-14 game-wide feature consumers

The player update now identifies `runtime_flags & 0x400` as the game-wide
falling gate and `runtime_flags & 0x400000` as the movement-fire emitter gate.
The former remains separate from per-row `SUBROW_FLAG_NO_FALL`. Focused output
is byte-identical at 74.20%, 2,075/2,087 instructions, prefix 12/2,087, 290
clean operands, and the same bounded jump-table mismatch.

## 2026-07-14 completion lifecycle ownership

The player-side handoff now waits explicitly for
`COMPLETION_STATE_CONTINUE_ACCEPTED`, holds the timer while any earlier state is
active, and only flushes a non-`INACTIVE` controller after the fade completes.
This closes the consumer side of the exact `cRCompletion` state graph. Focused
output remains byte-identical at 74.20%, 2,075/2,087 instructions, prefix
12/2,087, 290 clean operands, and the same bounded jump-table mismatch.

## 2026-07-14 damage lifecycle ownership

The player gate that suppresses the ordinary movement branch now tests
`DAMAGE_GUAGE_STATE_DRAINING` rather than raw state 2. This is one of only two
direct non-member state consumers recovered by Binary Ninja field xrefs; the
other is `calc_subgame_rate`. Focused output remains byte-identical at 74.20%,
2,075/2,087 instructions, prefix 12/2,087, 290 clean operands, and the same
bounded jump-table mismatch.

## 2026-07-14 hover lifecycle ownership

All player-side hover gates now consume `SubHoverState`: the active lane adds
forward acceleration, suppresses attachment lateral handling, shapes the
vertical hover response, and owns the late attachment-exit retirement branch.
Focused output remains byte-identical at 74.20%, 2,075/2,087 instructions,
prefix 12/2,087, 290 clean operands, and the same bounded jump-table mismatch.

## 2026-07-15 durable root composition replay

The root tail now places the exact `0xf4`-byte `HighScore` at `+0x12e6e50`,
keeps the proved `0x14`-byte gap, and owns `TipManager` at `+0x12e6f58`.
Consequently both tracked decompilers render the row-event enqueue through
`g_game_base->tip_manager` instead of a raw tail offset. The scratch source is
unchanged; a fresh focused receipt is 74.30%, 2,072/2,087 instructions, prefix
12/2,087, with 290 clean operands and the same bounded jump-table mismatch.

The same regeneration exposed an HLIL-only false owner for the pre-biased
`segment_slots[event_id - 1]` message addresses. Three replayed register views
now keep those accesses as byte arithmetic instead of pretending they belong
to `SegmentCache` or `Tutorial`; no overlapping convenience field was added.

## 2026-07-15 complete root composer preservation

Subgame-runtime replays now preserve the exact catalog, loader, front-end, and
tail components in the same guarded `GameRoot` graph instead of shrinking the
database back to a partial view. This function does not consume the catalog or
loader directly, but its regenerated IDA listing proves the later gameplay
lane retains the established player, subgame, and tip-manager owners. The
matching source remains unchanged at 74.30%, 2,072/2,087 instructions, prefix
12/2,087, with 290 clean operands and the same bounded jump-table mismatch.

## 2026-07-16 follow-state tail ownership

The live byte at `FollowState +0x3c` is now carried into both analysis lanes as
`flag_3c`. `update_subgoldy` reads it together with
`completion_handoff_active` before forcing the track-z handoff values. The only
other recovered access clears it while runtime cells are rebuilt; no nonzero
producer is known, so the neutral offset-based name is retained rather than
inventing stronger semantics. This is an analysis ownership correction only;
the matching source and its documented residual remain unchanged.

The void prototype also lets BN eliminate one transient `GameRoot*` name in
the completion-copy block. Its health check now asserts the durable
`players[0].transform` and `players[0].completion_handoff_transform` ownership
paths without pinning an analyzer-generated local suffix.

## 2026-07-16 void callback ABI

`update_subgoldy` is slot zero of `g_subgoldy_callback_table`, installed on the
embedded Player and invoked by `run_frame_update` through the shared void
`BodAiDispatch` interface. Its seven native return sites leave unrelated call,
global-load, or branch-register values in EAX; they do not form a result. The
durable BN and IDA declarations now therefore match the authored
`cRSubGoldy::AI()` contract as `void __thiscall(Player*)` instead of preserving
an inferred integer return. This is a decompiler ABI correction only; the
matching source remains unchanged at 74.30%, 2,072/2,087 instructions, prefix
12/2,087, with 290 clean operands and the same bounded jump-table mismatch.

## 2026-07-18 replay and time-trial record ownership replay

The two persistent replay-Z lanes are now durable typed globals in both
analysis databases: `g_replay_accum_z` at `0x643194` is the recording codec's
decoded-Z accumulator, while `g_subgoldy_ghost_z` at `0x643190` accumulates the
time-trial ghost record. Both are proved `float` by their x87 load/store use
and by the existing matching source; Binary Ninja had retained them as
`int32_t`, and the first still lacked a durable symbol.

The native time-trial expression deliberately remains
`game + level_mode_arg * sizeof(SubSolution)`. Its exact EAX/Hex-Rays lifetime
is now a borrowed `TimeTrialRouteRecordCursor *`, rooted at
`cRSubGame + offsetof(cRSubGame, sub_high_score) +
offsetof(SubHighScore, time_trial_route_records)`. This recovers
`SubSolution::{active,replay_start_cursor,replay_sample_count,run_records}` in both
tracked decompilers without flattening the `SubHighScore` owner or claiming a
second record allocation. The analytical cursor size is `0x963c10`, its
terminal `record` starts at `0x944150`, and the owned record remains exactly
`0x1fac0` bytes.

The Binary Ninja identity is `RegisterVariableSourceType` index 7143 in EAX;
the IDA identity is the sole non-stack local defined at `0x43cd08`. Focused
replays assert those exact identities and all owner sizes, and the broad path
replays carry the same facts. This is analysis-only ownership recovery: the
matching source and masks are unchanged, so the honest focused result remains
74.43%, 2,070/2,087 normalized instructions, prefix 12/2,087, with 290 clean
audited operands and the same one bounded jump-table mismatch.

## 2026-07-19 Player position cursor lifetime

The playback and recording arms both initialize EBX from
`Player + offsetof(Player, body.transform.position) == Player + 0x68`, at
`0x43b2c0` and `0x43b4f6`. Binary Ninja kept those definitions separate from
the post-branch PHI at `0x43b694`, leaving nearly every movement, attachment,
wall-probe, camera-target, and follow-state consumer on the opaque `ebx_1`.
The guarded replay now splits and merges the two producer definitions, then
names the stable joined lifetime `p_position` as `Vec3 *`. The bounded EAX
copy at `0x43bdb9`, used only to marshal the first swept-motion aggregate
argument, is also typed `Vec3 *`; that removes the false `int32_t *` view
without inventing another owner.

The replay exposed a stale broad-header spelling before it changed the
database. Canonical `TransformMatrix` storage is four `Vec3` rows, each
followed by its authored scalar W component; in particular, `position` at
`+0x30` is `Vec3` and `position_w` is the adjacent float at `+0x3c`.
`path_template_types.h` now preserves that ownership instead of flattening
each row to `Vec4`, while retaining the exact 0x40-byte matrix layout. The
now-unused broad-header `Vec4` alias was retired with the correction.

The raw replay-Z expression was deliberately left alone. The owned
`current_high_score_record.run_records[cursor].delta_z` address is
`game + 0xfd2b82 + cursor * 6`; because `0xfd2b82 / 6 == 0x2a31eb`, VC6 folds
the field offset into the record index and emits
`game + (cursor + 0x2a31eb) * 6`. A fabricated replay-record pointer would
hide real code generation rather than recover ownership.

This slice is analysis-only. The matching source remains unchanged at 74.43%,
2,070/2,087 normalized instructions, prefix 12/2,087, with 290 clean audited
operands and the same one bounded jump-table mismatch.

## 2026-07-24 one-based row-event segment ownership

The row-event message path now has one concrete owner instead of three raw or
misattributed addresses. Native code proves `event_id > 0` and
`event_id < level_definition.segment_count + 1`, then reads:

- `game + event_id * 0x4220 + 0xa670` for `message_text`;
- `game + event_id * 0x4220 + 0xa870` for `message_duration`;
- `game + event_id * 0x4220 + 0xa874` for `message_sample_id`.

Those addresses are exactly
`SubTracks::segment_slots[event_id - 1] + {0x4018, 0x4218, 0x421c}` because
`cRSubGame::level_definition` begins at `+0xa874` and
`SubTracks::segment_slots` at `+0x4`. The bounded
`SubSegmentEventBiasView` therefore starts its one-based alias at `+0x6658`;
element N aliases the real segment slot N-1, while element zero is explicitly
invalid. Its `0x1a7cf8` extent ends with the real 100-slot segment bank. It is
a borrowed analysis view, not a second `SubTracks` or `cRSubGame` owner.

Binary Ninja had merged the scalar `row_event_id` EAX lifetime with the later
game-base load at `0x43b752`. The replay splits only that definition
(`RegisterVariableSourceType / 1586 / EAX`) and types it plus the independent
message, duration, and sample game-base lifetimes. The scalar remains
`int32_t`. IDA independently materializes only the sample base as a local
(`0x43b823`, EDX), so its replay types that honest lifetime and deliberately
leaves the three inlined Hex-Rays expressions untouched rather than installing
overlapping fields.

The tracked Binary Ninja artifact now resolves message presence, text,
duration, and sample through `segment_slots_one_based`; IDA resolves the sample
through the same view. Binary Ninja's `.message_duration.bits` spelling is its
union-member presentation for the float load; the matching source retains the
authored `.message_duration.value`. No matching source changed. A fresh
focused receipt remains 74.43%, 2,070/2,087 normalized instructions, prefix
12/2,087, with 290 clean operands and the same single bounded jump-table
mismatch.

## 2026-07-24 player runtime-row ownership replay

The player tick now shares the same concrete `SubRow` slab ownership already
proved in the runtime-row producer and other consumers. IDA's numeric operand
inspection independently identifies nine native displacements:

- `0x43b709 -> 0x5ccac8` and `0x43b710 -> 0x5ccbb8` form the selected
  `SubRow` and read its `row_event_id`;
- `0x43bcf3`, `0x43bd44`, and `0x43be19 -> 0x5ccac8` read the current row
  flags;
- `0x43bd98` and `0x43bde6 -> 0x5ccb6c` read
  `primary_attachment_cell`;
- `0x43be6d` and `0x43bebb -> 0x5ccb70` read
  `secondary_attachment_cell`.

Those offsets are exactly `cRSubGame::runtime_rows + {0x0,0xa4,0xa8,0xf0}`
with `sizeof(SubRow) == 0xf4`. The guarded replay normalizes only those
operands, types the borrowed row lifetime at `0x43b70a` as `SubRow *`, and
names the independent row-event and primary/secondary attachment cell/index
lifetimes. The tracked IDA decompile consequently exposes
`runtime_row->row_event_id`, both attachment-cell owners, and each cell's
`attachment_template_record` without the false `byte_5CCAC8`,
`unk_5CCBB8`, `unk_5CCB6C`, or `unk_5CCB70` globals. Binary Ninja already
rendered the same ownership graph and required no semantic correction.

This is analysis-only ownership recovery. The scratch and masks are unchanged;
a fresh focused receipt remains 74.43%, 2,070/2,087 normalized instructions,
prefix 12/2,087, with 290 clean audited operands and the same one bounded
`update_subgoldy_follow_jump_table` mismatch.

## 2026-07-25 authored shoot-SFX call ownership

The four firing-edge calls now use the cross-port authored member
`cRSubGoldy::PlayShootSfx()`. Android and iOS retain that exact symbol, and the
Android body independently matches the Windows flag buckets, SFX 17..24
families, cached variant, and attachment-exit attenuation. The stable
`play_subgoldy_shoot_sfx` manifest entry carries `PlayShootSfx` as an alias,
so the source clarification does not hide or relax any call relocation. The
focused match remains honestly unchanged.

## 2026-07-25 authored Shoot call ownership

The four firing-edge emitter calls now use the cross-port authored member
`cRSubGoldy::Shoot(cRSubGoldy*)`. Android retains that exact symbol and repeats
the Windows flag-to-projectile-budget classifier plus the receiver-owned
12-slot Golb scan. The canonical `shoot_subgoldy` manifest entry
carries `Shoot` as an alias, so every call relocation remains audited. This is
an ownership clarification only; the focused match remains honestly
unchanged.

## 2026-07-25 shoot cooldown field ownership

The completed authored shooting chain closes Player `+0x2730/+0x2734` as
`shoot_cooldown_progress` and `shoot_cooldown_step`. `SetShootFlags` selects
the step from the active weapon family. `cRSubGoldy::AI()` blocks another shot
while progress is positive, advances it by that step to the terminal
threshold, and seeds it again on every `PlayShootSfx`/`Shoot` firing edge.
No non-shooting consumer exists in the recovered Windows or Android bodies.

The older `movement_fire_progress` names remain only as stable Frida trace
schema keys; the C++ and analysis struct now carry the narrower ownership.
Field spelling does not affect code generation, so the focused match remains
honestly unchanged.

## 2026-07-28 row-event TipData coordinates

The row-event producer's adjacent `0.0f` and `30.0f` stores are now
`TipData::anchor_x` and `TipData::layout_y`. Dual-mobile `cRTip::Init` bodies
independently pass those exact lanes as widget X/anchor-X and Y, and the
Windows initializer consumes them in the same argument positions. The former
`text_scale` name at `+0x08` had no font-scale consumer and is retired.

This ownership correction is codegen-neutral. The focused result remains
82.67%, 2,086/2,087 instructions, with 314 clean masked operands and no
unresolved or mismatched references.

## 2026-07-28 replay-origin cursor ownership

The Time Trial index expression is now explicit:
`record.replay_start_cursor - player.replay_start_cursor + cursor`.
Windows producers close both sides through click-start, completion, and reset;
Android and iOS `cRSubGoldy::AI()` independently preserve the same subtraction
and cursor addition. This identifies one replay-origin cursor while leaving
mobile offsets non-authoritative. The focused result remains honestly
unchanged at 82.67%, 2,086/2,087 instructions with 314 clean operands.

## 2026-07-28 steering pull lifetime

Android and iOS both retain the authored steering smoothing semantics:
`position.x += (steer_target - position.x) * game_rate * 0.2`. Windows remains
the ABI and scheduling authority: its x87 sequence loads `subgame_rate`,
multiplies it by `0.2f`, subtracts the old x position from the target, then
multiplies and adds the old position.

Spelling the rate as a scoped `pull`, multiplying it by `0.2f` in a separate
statement, and preserving the mobile expression order makes the Windows
candidate exact from function offsets `+0x334` through `+0x3ed`. The focused
result rises from 82.67% to 82.75%; candidate and target are both 2,087
instructions, with 314 clean masked operands, no unresolved or mismatched
references, and three visible unaudited global loads. A local switch-table
audit false positive exposed by this honest source change was fixed in the
matcher rather than waived or hidden with a symbol alias.

## 2026-07-30 exit frontend-state owner boundary

The remaining one-sided reference is isolated to the completion-exit branch.
Native reads `selected_level_record_persistent`, loads `g_game` once for the
saved/current frontend-state copy, then loads it a second time before the
branch and reuses that owner for both state 26 and state 27 stores. VC6 hoists
the copy owner before the flag read and reloads `g_game` independently in each
branch arm.

Three recorded sweeps cover shared `GameRoot` and `GamePlayer` owners,
destination pointers/references, conditional or selected-state stores, and
separately scoped copy/branch owners. All 15 unique variants regress. The
smallest loss is 21 fuzzy bytes for a shared field pointer/reference; broader
owners lose 46 to 121 bytes by perturbing the surrounding register schedule.
Most variants clear the audit entry, but none are a net match improvement.

The experiment ledger records those particular forms as unsuccessful; it does
not close the lane. The retained source remains 82.75%, 2,087/2,087
instructions, prefix 12/2,087, with 315 clean references and one explicitly
unaudited duplicated `g_game` load. No longer-lived root owner or
conditional-store rewrite is kept merely to make the audit count look cleaner.

## 2026-08-09 attachment-exit retirement closure

The four live direct clears of `attachment_exit_pending` are retirement
events, not a progress-expiry state machine. They preserve the established
`if (!pending) { floor } else { trampoline }` polarity and split into four
distinct authored outcomes:

- `0x43bf6f` retires the exit after entering the ordinary occupied,
  non-trampoline grounded envelope. The pending byte is cleared even when
  upward velocity prevents the accompanying y/velocity snap.
- `0x43c06d` is the same-tick cancellation of the open-edge arm at
  `0x43c008`: when falling is disabled (or `g_cheat_state.flags & 0x2` is set)
  and y is below `0.49`, it squidges, zeros vertical velocity, restores y to
  `0.49`, and retires the newly armed exit.
- `0x43c3ea` retires a pending exit only after the trampoline cell's authored
  `anchor_y +/- 0.49` envelope accepts the player; the same branch launches
  vertical velocity, sets `trampoline_bounce_active`, and plays SFX 41.
- `0x43ce75` makes active `SubHover` authoritative over the exit lifecycle. It
  clears pending after the low-hover vertical response and before the exit
  progress/voice-gate consumer.

Windows field references show one fifth direct clear at `0x43bcb3`, but that
branch is headed by `boost_one_tick`, whose complete field-xref set has no
nonzero producer in the shipped binary. Android and iOS retain the same five
source branches, independently confirming the four live retirement families
without making the dead Windows boost lane live.

Retirement deliberately clears only the pending byte. It does not clear the
anchor, progress, gates, or either carryover lane; exact
`begin_post_follow_carryover` overwrites all of the live lifecycle state on the
next arm. In particular, the former `post_follow_value_b` at Player `+0x430`
is now bounded as write-only carryover in the shipped Windows program:

- the type-field reference set contains only `0x43af78` (copy the live
  template's installed-heading dword) and `0x43af8c` (zero it when follow is
  inactive);
- a whole-image constant search for displacement `0x430` finds those two
  member stores and no Player-field load, while `+0x42c` independently has
  the expected `update_cameraman` consumer at `0x4465bb`;
- Android's exact `cRSubGoldy::FallingInit()` and the retained iOS inlined
  carryover paths corroborate the paired producer: they copy the same template
  dword into their layout-relative second lane, or zero it when follow is
  inactive. Their raw numeric offsets are not used as exhaustive cross-port
  consumer evidence.

This closes the shipped Windows consumer search, not a whole-program claim for
the differently laid-out mobile binaries. Preserve the second value as
captured state when tracing or comparing ports, but do not synthesize common
gameplay from it without new consumer evidence. No source-shape rewrite was
retained because the four native clear sequences already compile locally
instruction-for-instruction; their remaining listing displacement comes from
earlier register scheduling. A fresh focused receipt remains 82.75%,
2,087/2,087 instructions, prefix 12/2,087, with 315 clean masked operands, no
unresolved or mismatched references, and one visible unaudited duplicated
`g_game` load.

## 2026-08-09 completion fast-forward latch closure

The completion skip is a bounded one-shot lifecycle, not a generic held-fire
gate:

- native `cRCompletion::Init` arms Windows `Completion +0x18` at `0x404cca`;
- exact `cRCompletion::AI` clears that byte at `0x404e2e` when it reveals the
  summary and enters `COMPLETION_STATE_SUMMARY_ACTIVE`;
- this consumer loads the same byte at `0x43c89e`, requires the literal value
  `1`, then tests byte `Player::control_source +0x05` with mask `0x40` at
  `0x43c8b4`; that byte test is the little-endian high byte of
  `InputState::pressed_buttons +0x04 & INPUT_BUTTON_PRIMARY (0x4000)`, not the
  held/down field at `+0x0c`; and
- the accepted edge writes `0x40a33333` (`5.1f`) to
  `completion_handoff_timer` at `0x43c8ba`. The independent
  `COMPLETION_STATE_CONTINUE_ACCEPTED` lane writes the same value at
  `0x43c8c8`.

The player/controller alias is also closed. `build_subgame_level` passes the
sole Goldy initializer argument `1` at `0x43838e`; `initialize_subgoldy`
therefore stores `&GameRoot::game_inputs[0].input` into
`Player::control_source` at `0x43ae25`. The root input loop starts its index at
zero and writes it to the first record's `InputState::controller_slot` at
`0x41009a`. Exact `cRGameInput::AI` samples that controller word into
`current_buttons`, and native `cRInput::Update` derives the `pressed_buttons`
edge consumed here. Thus the shipped primary player uses controller slot 0;
there is no additional completion-only controller or input buffer.

The two completion consumers reach that input through different, deliberate
owners. The summary widget's accept route reads fixed
`players[0].game_input->input.pressed_buttons` at `0x404ebc`--`0x404ec2` and
enters state 5 at `0x404ecb`; this late Goldy handoff reads the owning
`Player::control_source` at `0x43c8ae`. For the sole primary Goldy, the Init
alias above makes both paths resolve to `game_inputs[0].input`.

Android and iOS independently preserve the same contract despite their
compact layouts: `cRCompletion::Init(int, bool)` sets its skip byte at compact
`+0x14`, `cRCompletion::AI()` clears it on summary entry, and
`cRSubGoldy::AI()` requires that byte plus the selected input's `+0x04 &
0x4000` before assigning `0x40a33333`. Both mobile
`cRSubGoldy::Init(int)` bodies also map player slot `1` to the first root input
at root `+0x94`. These mobile offsets corroborate lifecycle and ownership only;
Windows remains authoritative for `Completion +0x18` and Player layout.

No source-shape retry was made: this closes provenance around an already
recovered partial. The focused result remains honestly 82.75%, 2,087/2,087
instructions, with 315 clean masked operands and the one documented duplicated
`g_game` load.

## 2026-08-11 replay-record owner reopening

Live Windows disassembly gives the record block three distinct owner
lifetimes. The lateral write at `0x43b521` uses the existing `esi` owner. At
`0x43b546` native reloads `game` into `edx`, copies it to `esi`, and preserves
that `esi` owner across the fixed-point conversion calls for both z writes.
The z reads at `0x43b579` and `0x43b5c6` independently reload `game` into
`ecx`. The retained source mirrors those roles with a lateral `record_game`, a
fresh `record_game_z`, and direct `game` reads.

Four recorded sweeps cover declaration order, gate/cursor snapshots, split
roles, and the complete one- through four-site base/index owner matrix. The
combined matrix evaluates all 191 variants. Its apparent 84.95% leaders are
not faithful local recoveries: they keep source aliases where native reloads
`game`, steal `edi` from the native `0x4000` input-mask lifetime, and improve
later zero-register scheduling. Smaller split-role forms gain only eight
weighted bytes outside the record block while leaving the native reload
sequence wrong. Those score-only aliases are rejected; the scratch remains
82.75%, 2,087/2,087 with 315 clean references and one visible unaudited load.
The lane remains open to a source form that reproduces the observed owners
without trading away surrounding native lifetimes.
