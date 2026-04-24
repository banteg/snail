# Zig code structure

The two files that have grown past a reasonable ceiling during iterative porting:

| File | Lines | Shape |
| --- | --- | --- |
| `zig/src/main.zig` | ~8800 | `AppState` god object plus screenshot plumbing, render entry points, test fixtures, and several gameplay render helpers. |
| `zig/src/gameplay.zig` | ~9600 | `Runner` god object (≈4500 lines, ~300 methods) plus state type zoo (RowEventDisplayController, DamageGaugeRuntime, JetpackGauge, SnailSkinTransition, Projectile, RunnerPhase, AttachmentFollowState, LaunchState, etc.), free helpers, and test fixtures. |

Everything else is already sized sensibly (≤3700 lines each) or already split into subfolders (`zig/src/frontend/**`, `zig/src/gameplay/**`, `zig/src/debug/**`).

## Principles for the split

- **Make subsystem ownership explicit at call sites.** Extract helpers as free functions in sub-modules that take `*Runner` / `*AppState` as the first argument; keep thin wrapper methods only when external call sites need a gradual migration.
- **Move pure data types first.** Enum and struct decls without Runner/AppState references are risk-free to relocate behind `pub const X = @import("sub.zig").X;` re-exports.
- **Keep behavior changes out of the refactor.** Each phase is move-only; no semantic edits. Tests and health checks gate every commit.
- **Prefer one-file-per-subsystem over many-mini-files.** Group by subsystem, not by function count.
- **Split the system being touched.** If a porting fix adds behavior to a god module, first look for a narrow subsystem module that can own that behavior; leave only resource-backed drawing or process entry glue in `main.zig`.

## Architecture audit note

The architecture is serviceable for port discovery but suboptimal for continued parity work. The main risks are:

- `main.zig` still mixes application lifecycle, frontend ownership, asset IO, gameplay presentation, and render helpers. This makes behavior fixes look like app changes and encourages unrelated coupling through `AppState`.
- `gameplay.zig` still mixes the runner orchestrator with subsystem internals. Completed controller splits have helped, but attachment, cutscene/handoff, motion, presentation, and scoring still have cross-field access that makes native dataflow harder to audit.
- Rendering/resource ownership and simulation ownership are not consistently separated. The good boundary is: simulation modules emit plain state or transient effects; `main.zig` maps those to loaded textures/models/sounds.
- `resource_store.zig` now owns the archive catalog plus cached texture, sound, model, and object handles. App/global art should use `store.texture(...)`, `store.sound(...)`, `store.model(...)`, or `store.object(...)`; direct catalog loaders should be limited to stateful streams, active animations, parsers, and generated track-preview internals.
- Archive member bytes and catalogs are already resident for the full app lifetime, so small global resource sets should follow that shape too. Gameplay sound effects, gameplay sprites, and static gameplay models/objects are app-global resources, not per-level state.
- `app/audio.zig` now owns app audio dispatch, music/preview slots, gameplay sound cues, native/gameplay voice routing, and config-volume application. `main.zig` should call that module directly instead of growing new `AppState` audio methods.
- Existing focused modules (`frontend/**`, `gameplay/jetpack.zig`, `gameplay/damage.zig`, `gameplay/hazards.zig`, `gameplay/parcel.zig`, `gameplay/combat.zig`, `gameplay/effects.zig`, `gameplay/presentation.zig`) are the better shape: small controller/pool types with tests near the behavior.

Treat future refactors as opportunistic architecture repair, not broad churn. When touching a subsystem, extract the data/controller boundary that the native code already implies, then land the port behavior through that boundary.

## `zig/src/gameplay.zig` split plan

Proposed end-state: `gameplay.zig` stays the public entry point (re-exports, the `Runner` struct, top-level `step`). Each subsystem owns its own module under `zig/src/gameplay/runner/`.

| Target file | Content |
| --- | --- |
| `gameplay/runner_state.zig` | Pure data types: `RunnerInput`, `ReplayDirective`, `AttachmentHint`, `MovementMode`, `SessionMode`, `DeathCause`, `RecentEvent`, `EncounterCounters`, `ScoreTotals`, `Stopwatch`, `DamageWarningState`, `DamageWarningActorState`, `DamageGaugeRuntime`, `DamageWarningActor`, `SnailSkinSlot`, `SnailSkinTransition`, `JetpackWarningBand`, `JetpackGauge`, `WeaponChannelStates`, `Projectile`, `RowEventDisplayState`, `RowEventDisplayController`, `AttachmentFollowState`, `AttachmentExitCarryover`, `InstalledAttachmentEntry`, `LaunchState`, `WorldFrame`, `AttachmentCameraProgress`, `FallState`, `RunnerPhase`, `RunnerHandoff`. Plus the constants that live with these types (cutscene ids, row event step values, fall thresholds). |
| `gameplay/row_event.zig` | Row-event controller logic: `armRowEventPromptGate`, `armRowEventStagingIfNeeded`, `stepRowEventProgress`, `updateRowEventDisplay`, `syncCurrentRowMessageSegment`, `rowEventCounterVisible`, `rowEventBonusVisible/BlinkAlpha/Score`, `maybeAwardRowEventCompletionBonus`. |
| `gameplay/parcel.zig` | Track-parcel runtime: `allocateTrackParcelSlot`, `findTrackParcelSlotIndex`, `collectLiveTrackParcel`, `collectParcelRow`, `stepTrackParcelHome`, `stepTrackParcelDelivery`, `updateTrackParcels`, `processTrackParcelCollisions`, `flushPendingParcelDeliveries`, `registerParcelDelivery`, `beginTrackParcelHome`, `beginTrackParcelDelivery`, `currentTrackParcelHomeAnchor`, `hasActiveRowEventDeliveryParcel`, `refreshLiveTrackParcels`. |
| `gameplay/hazards.zig` | Hazard + pickup + ring effect runtime + collision: `addRuntimeHazard`, `refreshLiveRuntimeHazards/Pickups/RingEffects`, `updateRuntimeHazards/Pickups/RingEffects`, `processRuntimeHazardCollisions/PickupCollisions/RingEffectCollisions`, `hasRuntimeHazard`, `consumeRuntimeHazard`, `applyGarbageImpact`, `addRuntimePickup`, `initialRuntime*` helpers, `stepRuntimeHazard`, `activeRuntimeHazards/Pickups/RingEffects`. |
| `gameplay/damage.zig` | Damage gauge + warning actor: `applyDamageGaugeDelta`, `updateDamageGaugeController`, `updateDamageWarning`, `updateDamageWarningActor`, `startDamageWarningActor`, `stopDamageWarningActor`, `damageGaugeWarningOverlayAlpha`, `damageWarningActorAlpha`, `damageWarningLabel`. |
| `gameplay/jetpack.zig` | Jetpack gauge: `armJetpackGauge`, `disarmJetpackGauge`, `updateJetpackGauge`, `jetpackWarningLabel`, `jetpackFuelRemaining`, `rowPositionNearRouteEnd`. |
| `gameplay/attachment.zig` | Attachment follow + entry + exit: `tryPrimeCurrentRowAttachmentEntry`, `endAttachmentIfNeeded`, `stepAttachmentExitState`, `activeTrackAttachmentExitRetires`, the `attachmentExit*`/`attachmentFollow*`/`attachmentLocal*`/`attachmentLateral*`/`attachmentTemplate*` geometry helpers, `advanceAttachmentFollow`, `stepAttachmentFollowAtRate`, `updateAttachmentFollowPosition`, `updateAttachmentFollowCameraOrientations`, `beginAttachmentExitState`, `tryBeginCurrentRowInstalledAttachmentFollow`, `tryBeginInstalledAttachmentFollowForSlot`, `attachmentShouldSideExit`, `currentAttachmentBuilt`. |
| `gameplay/turret.zig` | Turret fire lanes, projectile spawn/update, weapon cooldown selector: `updateTurretFire`, `updateProjectiles`, `spawnProjectile`, `stepMovementFireCooldown`, `advanceMovementFlagSelector`. |
| `gameplay/motion.zig` | Lane-lean + row advancement: `maybeArmLaneLean`, `stepLaneLean`, `applyLaneDelta`, `applyTargetLaneCenter`, `advanceMovement`, `advanceTrackMovementByRows`, `syncRowPosition`, `laneLeanDirectionForRuntimeTile`, `sampleRow`, `currentRuntimeSample`, `refreshSample`, `applyReplayDirective`, `applyReplayMovementFlagProgress`, `currentReplayWorldX`. |
| `gameplay/phase.zig` | Phase + handoff + completion: `updatePhaseController`, `advanceCutsceneTicks`, `deathUsesFinalLoss`, `beginFallState`, `updateFallEntry`, `maybeBeginCompletionCutscene`, `completionHandoff*` helpers, `applyRespawn`, `applyCompletionBonus`. |
| `gameplay/score.zig` | Scoring glue: `recordScore`, `recordPowerupRing`, `recordGameplayEvent`, `recordNativeRingEffect`, `applyRingEffect`, `applyNativeNegativeVelocityRing`, `defeatSlug`/`defeatSlugSilent`/`markSlugDefeated`, `isSlugDefeated`. |
| `gameplay.zig` (remaining) | The `Runner` struct definition itself (fields), `init`, `reset`, `step`, `stepWithReplay`, `refreshBlockedStartupState`, `stepIntroStartupBlock`, `refreshCameraState`, camera getters (`worldPosition/Forward/Up`, `cameramanMatrix`, etc), top-level test fixture, re-exports from every subsystem. |

## `zig/src/main.zig` split plan

Proposed end-state: `main.zig` stays the program entry point. The `AppState` struct stays but its methods move into focused sub-modules that take `*AppState` as first argument.

| Target file | Content |
| --- | --- |
| `app/frontend_flow.zig` | Frontend phase and menu flow: `enterGamePhase`, start-phase setup, main/new-game/challenge/options/pause/help/exit/route-map/high-score action dispatch, post-level high-score entry routing, frontend level launch, selected-record launch, route-map entry, and active route action selection. |
| `app/frontend_input.zig` | Frontend input and activation state: hover target updates, queued activation dispatch, pending fade/activation handoff, widget shortcut code mapping, shortcut activation handling, frontend keyboard navigation/value stepping, and widget animation/snap state. |
| `app/frontend_mouse.zig` | Frontend mouse hit-testing: menu row hover selection, slider arrow hit regions, route-map card/back/replay hit regions, high-score replay/footer actions, completion/exit/help buttons, and mouse-driven activation queueing. |
| `app/route_map_state.zig` | Route-map card state: open/close gating, active route index tracking, route action index sync, and route highlight target/animation stepping. |
| `app/render_phase.zig` | Shared render phase policy: frontend canvas eligibility, gameplay-backdrop detection, light-streak visibility, and live subgame camera handoff for background streaks. |
| `app/subgame_camera.zig` | Shared subgame camera state: live/cutscene source handoff, snap/blend policy, Raylib camera conversion, and mouse-to-lane steering target mapping. |
| `app/outer_bridge.zig` | Outer bridge owner/opcode policy: abandon/respawn/pending-run owner selection and selected-replay context clearing rules. |
| `app/return_flow.zig` | Outer bridge execution: bridge teardown, respawn resume, and owner-state dispatch back into frontend/gameplay entry points. |
| `app/selected_replay.zig` | Selected replay helpers: high-score entry lookup by source, playback-active checks, replay input directives, selected replay launch return targets / owners, post-run opcode selection, and replay marker owner selection. |
| `app/run_result.zig` | Pending run result data and helpers: `Result`, `Persistence`, `Outcome`, `CompletionFlowOwner`, `RespawnBridgeState`, `StandalonePostLevelHighScoreEntry`, summary conversion, completion-owner return targets, postal unlock/return helpers, high-score rank preview, selected-replay result cleanup, completed/failed-run construction, high-score persistence commits, and completion-screen reveal/visibility state. |
| `app/level_loader.zig` | Level + segment loaders: `loadGameLevel`, `reloadLevel`, `reloadLevelSegment`, `syncActiveLevelSegment`, run-tuning helpers, track-build seed helpers, and row-message prompt dispatch. |
| `app/audio.zig` | Audio helpers: `playMusicByPath`, `playGameplayEffect`, `stopAudioPreview`, `stopVoicePlayback`, `applyAudioConfigVolumes`, `playGameplayRunnerAudio`, `playLevelSegmentSample`, `updateGameplayAmbientVoices`, plus private native/gameplay voice routing helpers. |
| `gameplay/effects.zig` | Transient gameplay effect controller: `Controller`, `Effect`, `Kind`, update/clear/spawn helpers, and runner-driven smoke/explosion/slug goo emission. `main.zig` keeps texture selection and billboard drawing because it owns loaded Raylib resources. |
| `gameplay/hud.zig` | Gameplay HUD renderer with explicit render context: score/best/parcel widgets, progress bar, lives, damage gauge, warning icon, and row-event world widget. |
| `gameplay/presentation.zig` | Gameplay presentation latches that are driven by runner state but do not own loaded models: `JetpackVisualState`, `WeaponVisualState`, and `nativeJetpackVisualPresentationActive`. |
| `frontend/art.zig` | Frontend and route-map resource holders/loaders: `SliderArt`, `FrontendWidgetArt`, `FrontendSoundFx`, `RouteMapArt`. |
| `gameplay_art.zig` | Gameplay art, sound-fx, and model holders/loaders: `SpriteArt`, `SoundFx`, `WeaponModelSet`, `InvincibleModelSet`, `JetpackModelSet`, plus their load/unload helpers. |
| `gameplay/resources.zig` | Gameplay resource state and static gameplay asset lifetime helpers: Turbo animation/model selection, barrier/lazer/salt/actor model loading, sprite/sound-fx ownership, and explicit tutorial animation sync context. |
| `app/screenshots.zig` | Screenshot request + capture path: `Request`, auto-screenshot queueing, capture/export, and frontend-canvas flip handling. |
| `app/runtime_config.zig` | Runtime config (`SnailMail.cfg`), high-score overlays, score persistence, `applyConfig*` / `loadConfig*` / `saveConfig*`. |
| `gameplay/barrier_render.zig` | Gameplay barrier renderer: recovered tutorial/NoFall visibility, native additive blend state, depth-mask/culling policy, and object-space barrier placement. |
| `gameplay/billboard.zig` | Gameplay billboard quad renderer: camera-facing textured quads, optional roll, alpha-cutout shader scope, depth-mask handling, and texture UV mapping. |
| `gameplay/model_render.zig` | Gameplay model render helpers: model-space offsets, basis transforms, tint/outline draw wrappers, Turbo pose construction, and local attachment positioning. |
| `gameplay/projectile_render.zig` | Gameplay projectile renderer: projectile basis construction, laser/vapour fallback object drawing, rocket model drawing, and projectile tint/scale policy. |
| `gameplay/render_policy.zig` | Gameplay renderer policy helpers: visible row/window gates for static actors, runtime hazards, pickups, ring effects, salt slots, and static-ring ownership. |
| `frontend/render.zig` | Shared frontend render primitives: app-font text measurement/drawing, aligned headings, status/notice overlays, and the custom frontend cursor overlay. |
| `frontend/screens.zig` | Frontend screen composition: boot/title crawl wrappers, menu draw dispatch, challenge setup labels, high-score draft text, route-map notices, exit prompt heading, help, and thanks screen. |
| `main.zig` (remaining) | `pub fn main`, CLI parsing, render loop, top-level init/teardown, `AppState` struct definition with field declarations plus a thin dispatch layer that delegates to the above modules. |

## Execution order

One commit per phase; each ends green (zig build test + health checks + no user-visible behavior change).

1. Phase A1 — **done**. `gameplay/runner_state.zig` owns the remaining cross-subsystem value types (`RunnerInput`, `ReplayDirective`, `AttachmentHint`, `MovementMode`, `SessionMode`, `DeathCause`, cutscene-id constants, `RunnerHandoff`, `Projectile`, `RecentEvent`, `EncounterCounters`, `ScoreTotals`, `RowEventDisplayState`, `RowEventDisplayController`, `Stopwatch`, `SnailSkinTransition`, `WeaponChannelStates`, `FallState`, `RunnerPhase`, attachment-follow / launch / world-frame data).
2. Phase A2 — **done**. `gameplay/jetpack.zig` owns `Gauge` (previously `JetpackGauge`) with `arm()`/`disarm()`/`update()`/`fuelRemaining()`/`WarningBand`. Runner methods collapse to 3-line delegates.
3. Phase A3 — **done**. `gameplay/damage.zig` owns a single `Controller` that consolidates 5 previous Runner fields (`damage_gauge`, `damage_gauge_runtime`, `damage_warning_state`, `damage_warning_actor`, `slug_hit_active`) plus `WarningState`, `WarningActorState`, `Runtime`, `WarningActor` types. `applyDelta`, `updateController`, `update`, `overlayAlpha`, `actorAlpha`, `displayFill`, `warningLabel` live on the controller; Runner delegates. External call sites now read `runner.damage.gauge` / `runner.damage.warning_state` etc.
4. Phase A4 — **done**. `gameplay/hazards.zig` owns `Runtime { hazards, pickups, rings }` — three `HazardPool` / `PickupPool` / `RingPool` structs collapsing 10 previous flat Runner fields into one composed `runner.runtime` entry with `reset()` / `active()` / `contains` / `countOfKind` primitives. Cross-cutting collision logic stays on Runner for now; it reaches through the pools.
5. Phase A5 — **done**. `gameplay/parcel.zig` owns `Pool { home_anchor, slots[50], last_scan_end, collected_rows[1024], collected_row_count }` with `findSlotIndex`, `allocateSlot`, `isCollected`, `markCollected`. Runner helpers delegate.
6. Phase A6 — **done**. `gameplay/combat.zig` owns `Combat { projectiles: ProjectilePool, turrets: TurretPool }` grouping the 4 weapon-pool fields.
7. Phase A7 — cutscene + handoff state (`cutscene_id`, `cutscene_ticks`, `cutscene_camera`, `pending_handoff`, `completion_handoff_*`, `completion_screen_init_sent`) → `gameplay/cutscene.zig`. Medium churn (external call sites in `gameplay/camera.zig`).
8. Phase A8 — attachment state + entry + exit + carryover + camera orientations (~16 fields) → `gameplay/attachment.zig`. Big churn because `gameplay/camera.zig` reaches into `attachment_follow` / `launch` / orientations.
9. Phase A9 — motion (lane lean, row advance, replay, sample, runtime tile hint) → `gameplay/motion.zig`.
10. Phase A10 — presentation (snail_skin, weapon flags, movement timers, invincible/slow/shot cooldowns) → `gameplay/presentation.zig`.
11. Phase A11 — score + counters + defeated slugs + visible lives + recent events (~10 fields, 80+ external call sites) → `gameplay/scoring.zig`. Highest external-churn; defer until the more self-contained subsystems are done.
12. Phase B0 — **done**. `gameplay/effects.zig` owns transient gameplay effect state and runner-driven effect emission. `AppState` now owns a `gameplay_effects.Controller`, and `main.zig` only renders the effect list with loaded sprite assets.
13. Phase B1 — **done**. `frontend/art.zig` owns frontend/route-map art and sound holders/loaders. `gameplay_art.zig` owns gameplay art/model/sound holders/loaders. `gameplay/resources.zig` owns static gameplay resource lifetimes. `app/audio.zig` owns audio dispatch and `app/screenshots.zig` owns screenshot capture.
14. Phase B2 — **done**. `app/level_loader.zig` owns level/segment loading, active segment sync, row-message prompt dispatch, run-tuning helpers, track-build seeds, and mode-to-runtime helpers. `app/run_result.zig` owns run-result data plus summary/ranking/completion-flow helpers, selected-replay result cleanup, completed/failed-run construction, high-score persistence commits, and completion-screen reveal state. `app/outer_bridge.zig` owns owner/opcode selection. `app/selected_replay.zig` owns selected-replay launch/context policy and replay directives. `app/return_flow.zig` owns final return transition execution.
15. Phase B3 — **done**. `app/frontend_flow.zig` owns frontend phase entry, start-phase setup, menu action dispatch, high-score screen entry, exit prompt routing, frontend level launch, selected-record launch, route-map entry, and route-map action/route stepping helpers. `app/frontend_input.zig` owns hover/activation queue state, widget shortcut dispatch, frontend keyboard navigation/value stepping, and widget animation/snap state. `app/frontend_mouse.zig` owns frontend mouse hit-testing. `app/route_map_state.zig` owns route-map card open/close and highlight state.

## Refactor pattern that worked

For each subsystem:
1. Create `gameplay/<subsystem>.zig` with a `Controller` or `Pool`/`Runtime` struct owning the subsystem's fields.
2. Move subsystem-only methods onto the controller; inline-pass-through the few fields the Runner cross-reads (snail_skin, preview).
3. Drop the 5–10 loose Runner fields and add a single composed field: `<subsystem>: <module>.Controller = .{}`.
4. Bulk-rename internal accesses via a Python script: `self.damage_gauge → self.damage.gauge` etc.
5. Rewrite the Runner wrappers (applyDamageGaugeDelta etc.) as 1–3 line delegates to the controller.
6. Move constants into the module; keep `const X = <module>.X` at the top of `gameplay.zig` where the `Runner` struct still uses bare names.
7. Run `zig build test` and fix external call sites (main.zig / gameplay/hud.zig / gameplay/audio_cues.zig / debug/).

Each phase ended with zero behavior change (tests green) and meaningful structural clarity (pool + controller types live with their logic).

## Executing Runner-method extraction (Phases A2+)

The tricky part for every remaining gameplay phase is: most `Runner` methods call other `Runner` methods, share private constants in `gameplay.zig`, and touch many Runner fields at once. Moving each subsystem out takes this shape:

1. Copy the subsystem's constants and helper free functions into the new module.
2. Convert the Runner methods into free functions that take `*Runner` (or `*const Runner`) as the first arg.
3. In `gameplay.zig`, replace each moved body with a one-line wrapper method that delegates to the sub-module. Tests + external call sites stay unchanged.
4. Remove the now-duplicated constants from `gameplay.zig`.
5. After the phase lands, consider collapsing the wrappers into a `usingnamespace` or importing them directly at the Runner struct level.

Keep each phase to a single coherent subsystem so diff review stays tractable.

## Non-goals (for now)

- Splitting `track.zig` (3700 lines). Already single-purpose; defer unless it grows again.
- Splitting `frontend/widget.zig` (802 lines). Clean and cohesive.
- Introducing a new build graph. Stay on the existing `build.zig`.
- Renaming public Runner/AppState methods. Only relocating method bodies.
