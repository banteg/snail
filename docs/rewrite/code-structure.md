# Zig code structure

The two files that have grown past a reasonable ceiling during iterative porting:

| File | Lines | Shape |
| --- | --- | --- |
| `zig/src/main.zig` | ~10200 | `AppState` god object (≈6300 lines, ~294 methods) plus frontend art loaders, gameplay effect tables, screenshot plumbing, render entry points, test fixtures. |
| `zig/src/gameplay.zig` | ~9600 | `Runner` god object (≈4500 lines, ~300 methods) plus state type zoo (RowEventDisplayController, DamageGaugeRuntime, JetpackGauge, SnailSkinTransition, Projectile, RunnerPhase, AttachmentFollowState, LaunchState, etc.), free helpers, and test fixtures. |

Everything else is already sized sensibly (≤3700 lines each) or already split into subfolders (`zig/src/frontend/**`, `zig/src/gameplay/**`, `zig/src/debug/**`).

## Principles for the split

- **Preserve existing Runner / AppState method-call sites.** Extract helpers as free functions in sub-modules that take `*Runner` / `*AppState` as the first argument; keep thin wrapper methods on the type when there are many external call sites, or re-export pure helpers from the module.
- **Move pure data types first.** Enum and struct decls without Runner/AppState references are risk-free to relocate behind `pub const X = @import("sub.zig").X;` re-exports.
- **Keep behavior changes out of the refactor.** Each phase is move-only; no semantic edits. Tests and health checks gate every commit.
- **Prefer one-file-per-subsystem over many-mini-files.** Group by subsystem, not by function count.

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
| `app/frontend_flow.zig` | Menu transitions + frontend level launch: `enterGamePhase`, `enterChallengeSetupMenu`, `enterGameplayShell`, `enterRouteMapMenuWithScreenMode`, `enterHighScoreBrowseScreen`, `enterPostLevelHighScoreScreenWithReturn`, `enterSelectedLevelRecordSource`, `beginFrontendLevelPath`, `finishPendingRunReturn`, `finishPostLevelHighScoreReturn`. |
| `app/outer_bridge.zig` | Outer bridge transition / saved-owner machinery: `applyOuterBridgeTeardown`, `runOuterBridgeTransition`, `outerOwnerFor*` helpers, `outerBridgeTransitionClearsSelectedReplayContext`, `savedOuterOwnerForLevelLaunch`, `resumeActiveRunAfterRespawnBridge`, `beginRespawnRun`, `abandonActiveRun`, `beginFailedRun`. |
| `app/run_result.zig` | Pending run result accounting: `PendingRunResult`, `RespawnBridgeState`, `StandalonePostLevelHighScoreEntry`, `commitRunResultIfNeeded`, `applySelectedReplayResultOverrides`, `pendingRunHighScoreContext`, `standalonePostLevelHighScoreEntry`, `currentFailedRunResult`, `beginCompletedRunOverlay`, `finalizeCompletedRunScreen`, `cancelPostLevelHighScoreEntry`, `clearPostLevelHighScoreEntry`, `failedResultPostLevelHighScoreEntry`. |
| `app/level_loader.zig` | Level + segment loaders: `loadGameLevel`, `reloadLevel`, `reloadLevelSegment`, `syncActiveLevelSegment`, related catalog helpers. |
| `app/audio.zig` | Audio helpers: `playSoundByPath`, `playVoiceByPath`, `playGameplayEffect`, `tryPlayNativeGameplayVoiceSet/Played/Payload`, `tryPlayGameplayVoiceVariant`, `gameplayVoiceBusy`, `stopVoicePlayback`, `applyAudioConfigVolumes`, `playGameplayRunnerAudio`, `updateGameplayAmbientVoices`. |
| `app/frontend_art.zig` | Art + sound-fx asset holders: `SliderArt`, `FrontendWidgetArt`, `FrontendSoundFx`, `GameplaySpriteArt`, `GameplaySoundFx`, `GameplayWeaponModelSet`, `GameplayInvincibleModelSet`, `GameplayJetpackModelSet`, `GameplayJetpackVisualState`, `GameplayWeaponVisualState`, `GameplayEffect`, `RouteMapArt`, plus their load/unload helpers. |
| `app/screenshots.zig` | Screenshot request + capture path: `ScreenshotRequest`, `BillboardUv`, related capture bookkeeping. |
| `app/runtime_config.zig` | Runtime config (`SnailMail.cfg`), high-score overlays, score persistence, `applyConfig*` / `loadConfig*` / `saveConfig*`. |
| `main.zig` (remaining) | `pub fn main`, CLI parsing, render loop, top-level init/teardown, `AppState` struct definition with field declarations plus a thin dispatch layer that delegates to the above modules. |

## Execution order

One commit per phase; each ends green (zig build test + health checks + no user-visible behavior change).

1. Phase A1 — gameplay state types → `gameplay/runner_state.zig` (pure data, easiest, ~600 lines moved).
2. Phase A2 — gameplay helpers that don't touch Runner → `gameplay/damage.zig`, `gameplay/jetpack.zig` (~300 lines each).
3. Phase A3 — gameplay row event + parcel → `gameplay/row_event.zig` + `gameplay/parcel.zig` (~700 lines together).
4. Phase A4 — gameplay hazards → `gameplay/hazards.zig` (~400 lines).
5. Phase A5 — gameplay attachment + turret + motion (largest remaining, ~1500 lines combined).
6. Phase A6 — gameplay phase + score + leftover glue.
7. Phase B1 — main.zig frontend art + screenshots + audio (low-risk data / IO modules).
8. Phase B2 — main.zig run result + outer bridge + level loader.
9. Phase B3 — main.zig frontend flow.

Each phase should shrink `gameplay.zig` / `main.zig` without changing any tracked decompile or Zig test output.

## Non-goals (for now)

- Splitting `track.zig` (3700 lines). Already single-purpose; defer unless it grows again.
- Splitting `frontend/widget.zig` (802 lines). Clean and cohesive.
- Introducing a new build graph. Stay on the existing `build.zig`.
- Renaming public Runner/AppState methods. Only relocating method bodies.
