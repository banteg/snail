# Remaining Work Checklist

This page is the current working checklist for the remaining reverse-engineering and porting work.

It is intentionally narrower than the broad rewrite plan and more action-oriented than the status ledgers:

- [port-status.md](port-status.md) says what is verified vs partial
- [subsystem-status.md](subsystem-status.md) gives the fuller subsystem read
- this page says what to do next, in what order, and what still looks underspecified or internally inconsistent

## Current Audit

The port is well past the old viewer-only stage. The repo now has a real gameplay runtime with:

- fixed-tick runner state
- row-event and parcel runtime controllers
- attachment follow from built path templates
- runner-owned cutscene/camera ownership
- separate damage and jetpack controllers
- high-score and replay plumbing
- the native-shaped `STARTAIL` star-field pass

The main remaining gaps are no longer "can the port load or draw this at all?" questions.

They are mostly ownership and exact-state questions:

- which native controller really owns a behavior
- which runtime field is authoritative instead of a fallback producer
- where app-side handoff should stop and runner-side ownership should begin
- which systems still look correct visually but are driven from the wrong source lanes

## Known Blind Spots

These are the main blind spots the repo should treat as active risks.

### 1. Outer subgame/frontend bridge

The port still lacks the real Windows ownership around states `26/27/28/29/30`.

What is now solid:

- `26` destroys the active subgame and jumps to the preserved frontend owner without reinitializing subgame
- `27` destroys, reinitializes subgame, then jumps to the preserved frontend owner
- `28` does the same as `27`, but clears `replay_active` first
- `29/30` are the Thanks For Playing owner
- BN disassembly confirms the bridge destination is a dedicated front-end controller slot, not just the same active-state lane
- tutorial completion and ordinary postal final loss both use the `26 -> 2` return-to-New-Game lane

Practical impact:

- final loss vs successful completion and the remaining post-run owners still cross the app/runtime boundary too loosely; respawn now routes through the explicit opcode-`28` rebuild lane
- challenge, time-trial, and replay-sensitive return routing are still not literal
- the current completion/death work now runs through one explicit app-side bridge request lane, but the preserved-owner writer and full Windows outer controller are still missing

### 2. Attachment follow semantics

Built-template follow is now strong enough to be useful, but the remaining gaps sit exactly where gameplay, camera, and state ownership meet:

- installed-bank ownership and pairing
- source-row installer semantics
- side-exit and natural-end return values
- family-specific nonlinear kind-`42` behavior
- the true meaning of the attachment-exit carryover lanes

### 3. Movement-state ownership

Audio RE now makes this much sharper than before: Windows still has a dedicated movement-state sound/controller layer. The port now mirrors the recovered selector-owned fire cadence, the startup cooldown reseed window, explicit live press-vs-held lanes, runtime fire feature flag, replay raw-bit gate, attachment-exit suppression, and the recovered turbo-spread plus laser/rocket shot-family ratios, but the deeper emitter owner and literal input-device source are still not ported.

### 4. Row-event/tip ownership

The port now has a runner-owned logical row-message token and runner-driven tutorial voice/prompt dispatch, but the native row-message payload tables and tip actor still are not ported literally.

Practical risk:

- tutorial and parcel behavior can look close while still being driven from the wrong control boundary
- completion fast-forward and `gate_18` style interactions remain underexplained

### 5. Warning/damage owner

The visible gauge and most voices are in, but the warning overlay still looks like a simplified gameplay helper instead of the original owned actor/controller.

### 6. Track render-normalization

This is still the biggest "quiet" rendering blind spot:

- warning-zone marking
- directional fringe ownership
- the remaining fringe-promotion BOD matching and marked-row run-merge semantics

Skipping these keeps presentation noisier than the runtime logic deserves and makes later visual audits harder.

### 7. Replay

Replay is still scaffolded. The repo can preserve and launch selected records, but the grounded gameplay consumer and full saveback parity are still not there.

### 8. Repo-doc inconsistencies

The recent star-field visibility and completion-handoff timing mismatches are now cleaned up.

Keep this as an active maintenance item anyway:

- after each parity pass, re-audit the status docs for stale claims that the code or later traces have already invalidated

## Ordered Checklist

Work this top-down unless a new runtime capture invalidates the order.

### Phase 1. Recover the outer bridge

- [x] Name or uniquely identify the real outer subgame/frontend bridge around states `26/27/28/29/30`
- [ ] Recover which fields mean fresh start, rebuild, continuation, replay-sensitive launch, and post-run return
  - current narrowing: the `26/27/28` jump target is a dedicated front-end controller slot (`update_frontend_state_machine` reads it from `[controller + 0x98]`)
  - current static dead end: a shallow BN sweep of the front-end cluster only exposed that read, not a writer, and the earlier `0x40775c` hit was just data
  - stronger narrowing: `update_new_game_menu`, `update_main_menu`, `update_high_score_screen`, and `exit_high_score_screen` all write active-state or replay-launch scratch globals, but none of them surfaced the preserved-owner writer either
  - newer replay-launch narrowing: `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch both seed the same app-side replay scratch (`+119190`, `+4299515`, `+4299516`, `+17198056`, `+17198057`) before state `10`, and later consumers now line up too: `initialize_click_start`, `update_pause_menu`, and `update_completion_screen`
  - likely next step: trace `[controller + 0x98]`, `data_4df904 + 110`, `+119190`, `+4299515`, `+4299516`, and `+17198056/+17198057` together in one Windows session
- [x] Port rebuild/teardown/return ownership into one explicit boundary instead of distributing it across runner and app helpers
  - current port shape: result exits and abandon exits now route through one `OuterBridgeRequest` lane with native opcode names plus a preserved launch-surface owner captured on level entry
- [ ] Finish moving any remaining post-overlay/final-loss/thanks-for-playing updates onto that same explicit bridge
  - current narrowing: respawn now follows the confirmed `update_subgoldy_resurrect -> save current owner -> state 0x1c` bridge lane instead of an app-local reload helper
  - newer narrowing: selected-level-record final loss is no longer lumped into opcode `28`; BN disassembly now shows `complete_subgame(game, 1)` followed by `save current owner -> state 0x1a`
  - newer narrowing: selected-level-record completion is also no longer lumped into opcode `28`; `update_subgoldy` now shows the persistent branch using `state 0x1a`, while the non-persistent branch still uses `state 0x1b`
  - stronger launch-side narrowing: BN plus IDA now show `update_galaxy` and `update_challenge_setup_screen` only arming `selected_level_record_active`, while `initialize_subgame` / `update_subgame` / `destroy_subgame` treat `selected_level_record_persistent` as a separate lifecycle lane
  - stronger replay-side narrowing: high-score replay rows and the menu replay attract path already use a separate app-side replay-launch scratch lane before state `10`; the still-missing step is the exact copy into `game + 0xff25d1`
  - newer mode narrowing: `initialize_subgame` and `update_subgame` both treat `level_mode == 7` as tutorial mode, so the special `0x1a -> owner 2` completion override is the already-ported tutorial-completion lane rather than a separate missing route
  - newer app-side narrowing: `add_arcade_high_score` / `add_survival_high_score` set app byte `+0x30d = 1`, `destroy_high_score_screen` clears it, and `update_completion_screen` also branches on it; this looks like a high-score-entry / high-score-screen continuation flag rather than a generic gameplay mode byte
  - current Zig consequence: frontend-selected replay completions now use the confirmed non-persistent `0x1b` rebuild-return path across challenge, time-trial, and postal, while transient postal replay final loss now also follows the native `0x1a -> owner 2` New Game override because `complete_subgame` never seeds app byte `+0x30d` while `selected_level_record_active` is set
  - remaining gap: the persistent-lane writer or copy site from app replay scratch into `game + 0xff25d1`, and the exact non-selected-record postal final-loss use of `data_4df904 + 0x30d`

### Phase 2. Finish cutscene and handoff runtime fields

- [ ] Find the writer(s) for the hotspot source matrices consumed by `update_snail_skin` and `update_cutscene`
- [ ] Capture intro, completion, and death hotspot-source values from Windows
- [ ] Confirm the exact failure selector and visible-life decrement commit point
- [ ] Confirm the exact completion-screen init, voice gate, and late finalize timings
- [ ] Replace any remaining handoff timers or anchor producers that still use Zig-side fallback values

### Phase 3. Finish attachment follow as a native runtime

- [ ] Recover the full installed-bank ownership and row-slot pairing rules
- [ ] Finish the swept local-frame entry test strongly enough to remove the remaining source-row fallback
- [ ] Recover the real consumers and semantics of `attachment_exit_value_a` / `attachment_exit_value_b`
- [ ] Recover milestone semantics in `update_track_attachment_follow_state`, especially the missing voice-4 milestone lane
- [ ] Separate nonlinear kind-`42` behavior into real family semantics instead of one shared placeholder story

### Phase 4. Recover the missing gameplay owners exposed by audio

- [ ] Recover the deeper movement-state emitter owner and literal input-device source behind `play_movement_state_sound`
- [ ] Finish the remaining payload-table and tip-actor semantics behind `voice 13`
- [x] Recover the real warning actor/controller behind `update_warning`
- [ ] Finish the remaining collision/powerup owner recovery beyond the now-ported native ring runtime owner, ring-kind ladder (`1`, `2/6`, `3/7`, `4/5/8`), runtime pickup collision slots, health bob lane, jetpack ramp-bias spawn lane, jetpack `JETPACKTHRUST` pre-warning visual lane, ring post-hit `2 -> 3` effect lane, and the recovered `health_collect_particles` burst packet, especially parcel, garbage-impact, the exact dedicated health-particle bod owner, the original pre-hit ring bod anchor/layout fields, the dedicated jet-particle/nozzle owner, and the remaining deeper weapon presentation owners
- [ ] Recover the remaining global-flag exits and `stop_warning_sample` handle semantics in the damage-warning owner

### Phase 5. Tighten gameplay runtime ownership

- [ ] Port the remaining ambient hazard mode gates and any non-horizontal suppressor details
- [ ] Recover the `Wall2` ambient hazard pool semantics
- [ ] Recover the exact `gate_18` input/controller source
- [ ] Recover parcel-flight and row-event widget timing details that still rely on app-side or inferred helpers
- [ ] Port the missing score events tied to replay, jetpack, slug kills, and the remaining unresolved branches

### Phase 6. Recover track render-normalization

- [ ] Recover the final render/cache consumer for the ported `mark_track_warning_zones` footprint beyond the now-ported fallback garbage/salt suppressor
- [ ] Port the remaining edge and exact BOD-table fringe-promotion passes
- [ ] Port directional fringe ownership and cache-family routing
- [ ] Re-audit gameplay and segment-view rendering only after these normalization passes are in

### Phase 7. Finish replay only after the runtime consumers exist

- [ ] Recover the grounded gameplay consumer for the saved secondary lane
- [ ] Recover the remaining replay-flag gameplay/audio/effect consumers
- [ ] Port full replay payload read/write parity
- [ ] Only then widen replay saveback behavior for new entries

### Phase 8. Tighten presentation layers last

- [ ] Finish Turbo gameplay anchor/orientation and broader state-specific animation switching
- [ ] Recover non-billboarded actor ownership where the original runtime uses real object/model controllers
- [ ] Tighten combat VFX ownership after the underlying controller is recovered
- [ ] Tighten remaining frontend widget polish only when ownership is already understood
  - current narrowing: native widget shortcut keys are now ported for pause-menu and post-level high-score flows; the remaining gap is shared widget-controller polish, not basic keyboard activation ownership

## Decompile Targets By Priority

If there is time for only one focused RE session, use this order:

1. `update_subgame` / outer bridge state machine
2. `initialize_subgame` / `build_subgame_level` rebuild ownership
3. `update_snail_skin` / `update_cutscene` hotspot-source matrix path
4. `initialize_subgoldy_death` / `update_subgoldy_resurrect`
5. `begin_track_attachment_follow_state` / `update_track_attachment_follow_state`
6. `update_row_event_display` / `flush_row_event_display`
7. `play_movement_state_sound` and `movement_flags` producers
8. `update_warning` and the damage-warning owner chain
9. track render-normalization helpers

## Checklist Discipline

While working through this list:

- do not count UI parity as proof that the owning runtime controller is ported
- prefer replacing fallback producers with recovered native fields before tuning presentation
- update the relevant status docs whenever a blind spot is closed or narrowed
- if a checklist item turns out to depend on a different upstream owner, move the checklist order instead of papering over the dependency
