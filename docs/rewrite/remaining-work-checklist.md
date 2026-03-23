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
- `29/30` are the Thanks For Playing owner, and `uninit_thanks_screen` hands that owner off to state `0x0e` (credits init)
- BN disassembly confirms the bridge destination is a dedicated front-end controller slot, not just the same active-state lane
- tutorial completion and ordinary postal final loss both use the `26 -> 2` return-to-New-Game lane

Practical impact:

- final loss vs successful completion and the remaining post-run owners still cross the app/runtime boundary too loosely; respawn now routes through the explicit opcode-`28` rebuild lane
- challenge, time-trial, and replay-sensitive return routing are still not literal
- the current completion/death work now runs through one explicit app-side bridge request lane, but the full set of preserved-owner producers and the literal Windows outer controller are still missing

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
  - earlier shallow dead end: a front-end-cluster BN sweep only exposed that read, and the earlier `0x40775c` hit was just data
  - newer whole-image narrowing: `update_subgame` state `2` copies the current owner from `app + 0x1b8` into `app + 0x1bc` before setting state `0x1a` for persistent selected-record startup or `0x1b` for transient startup
  - stronger remaining gap: `update_new_game_menu`, `update_main_menu`, `update_high_score_screen`, and `exit_high_score_screen` still write active-state or replay-launch scratch globals without exposing another direct preserved-owner store, so the missing part is now which other helper-driven producers exist beyond the confirmed gameplay-side writers
  - newer replay-launch narrowing: `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch both seed the same app-side replay scratch (`+119190`, `+4299515`, `+4299516`, `+17198056`, `+17198057`) before state `10`, and later consumers now line up too: `initialize_click_start`, `update_pause_menu`, and `update_completion_screen`
  - stronger replay-return narrowing: that `+4299516` / `app + 0x1066bf0` dword is not just a generic replay-side scratch slot; high-score replay rows seed it to `0x12`, the menu replay branch seeds it to `2`, and `update_completion_screen` state `3` later restores it directly
  - newer menu-attract narrowing: `update_new_game_menu` rotates a menu-local cursor through `0..4`, but only values `0/1/3` probe replay banks, write `app + 0x74658 = 0/1/4`, and seed the persistent replay scratch; that probe loop reuses the same `0x1fac0` bank stride, caps out after `1000` attempts, and is gated by menu-local float accumulator / step fields at `data_4df904 + 0x4f2dc + 0x10/+0x14`
  - newer startup-side narrowing: `initialize_game_assets_and_world` clears app bytes `+17198056/+17198057` at boot, `initialize_subgoldy` unconditionally calls `initialize_click_start`, `initialize_click_start` hides its prompt when `+17198056` is already set, and `update_subgame` later clears the menu-local hide latch only after `data_4df904 + 0x4f2e4` exceeds `1.0`, so persistent replay starts own that suppression path directly instead of inheriting stale global state
  - newer controller-layout narrowing: the same menu-local object at `data_4df904 + 0x4f2dc` now has a firmer partial shape: cursor `+0x0`, likely hide latch `+0x4`, secondary startup suppressor timer `+0x8/+0xc`, and attract accumulator/step `+0x10/+0x14`
  - likely next step: trace `[controller + 0x98]`, `data_4df904 + 110`, `+119190`, `+4299515`, `+4299516`, and `+17198056/+17198057` together in one Windows session
- [x] Port rebuild/teardown/return ownership into one explicit boundary instead of distributing it across runner and app helpers
  - current port shape: result exits and abandon exits now route through one `OuterBridgeRequest` lane with native opcode names plus a preserved launch-surface owner captured on level entry
- [ ] Finish moving any remaining post-overlay/final-loss/thanks-for-playing updates onto that same explicit bridge
  - current narrowing: respawn now follows the confirmed `update_subgoldy_resurrect -> save current owner -> state 0x1c` bridge lane instead of an app-local reload helper
  - newer narrowing: selected-level-record final loss is no longer lumped into opcode `28`; BN disassembly now shows `complete_subgame(game, 1)` followed by `save current owner -> state 0x1a`
  - newer narrowing: selected-level-record completion is also no longer lumped into opcode `28`; `update_subgoldy` now shows the persistent branch using `state 0x1a`, while the non-persistent branch still uses `state 0x1b`
  - stronger launch-side narrowing: BN plus IDA now show `update_galaxy` and `update_challenge_setup_screen` only arming `selected_level_record_active`, while `initialize_subgame` / `update_subgame` / `destroy_subgame` treat `selected_level_record_persistent` as a separate lifecycle lane
  - stronger replay-side narrowing: high-score replay rows and the menu replay attract path write `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0` before state `10`, and `update_frontend_state_machine` initializes subgame at `data_4df904 + 0x74618`, so those app offsets alias `game + 0xff25d0/+0xff25d1/+0xff25d4/+0xff25d8` directly
  - newer static negative result: whole-image disassembly still shows no direct nonzero store to `game + 0xff25d1`; the only direct store is the teardown clear in `destroy_subgame`, because the nonzero writer reaches the same byte through the overlapping app-base address
  - newer mode narrowing: `initialize_subgame` and `update_subgame` both treat `level_mode == 7` as tutorial mode, so the special `0x1a -> owner 2` completion override is the already-ported tutorial-completion lane rather than a separate missing route
  - newer app-side narrowing: `add_arcade_high_score` / `add_survival_high_score` set app byte `+0x30d = 1`, `destroy_high_score_screen` clears it, and `update_completion_screen` also branches on it; this looks like a high-score-entry / high-score-screen continuation flag rather than a generic gameplay mode byte
  - newer failure-side narrowing: on ordinary postal/challenge failure, `complete_subgame` can leave owner `0x14` armed through `add_arcade_high_score` / `add_survival_high_score`, and `update_subgoldy_resurrect` then preserves that `0x14` high-score owner in `app + 0x1bc` before setting state `0x1b`
  - newer selector narrowing: app dword `+0x12e55e0` is not a clean replay-only source candidate for `selected_level_record_persistent`; it now lines up better with `game + 0x1270fc8` as the ordinary rebuild selector, with selector `1` on the postal post-completion reopen and selector `2` on ordinary `update_new_game_menu` postal launch, `exit_high_score_screen`, and transient pause-abandon rebuild flow
  - newer pause-abandon narrowing: `update_pause_menu` copies the current owner into the completion-screen saved-owner slot, picks completion state `3` when `app + 0x1066be9 == 1`, and `update_completion_screen` state `3` destroys subgame then restores `app + 0x1066bf0`; persistent replay-backed abandon therefore uses the same destroy-return saved-owner lane as persistent result exits, not opcode `28`
  - newer transient-abandon narrowing: when `app + 0x1066be9 == 0`, `update_pause_menu` falls through to completion state `2`; `update_completion_screen` case `2` then destroys subgame and, for `level_mode == 4`, reinitializes subgame directly without using frontend state `0x1c`, while `initialize_subgame` rebuilds the route-map owner from the preserved continuation selector
  - newer overlay-side narrowing: `update_subgoldy` also consumes selected-record sample bit `0x8` directly; that branch writes `app + 0x1b8 = 0x1a`, `app + 0x1bc = 10`, sets app byte `+0x30c = 1`, and calls `begin_frontend_fade_in`, so replay-tail marker exit loops back through frontend state `10 -> initialize_subgame` rather than returning to the launch surface
  - newer non-replay failure narrowing: `update_subgoldy_resurrect` sends ordinary non-postal failures through state `0x1b`, and `initialize_subgame` consumes that continuation selector by mode: `level_mode == 1` rebuilds the challenge-setup owner and `level_mode == 4` rebuilds the galaxy owner
  - current Zig consequence: high-score replay launches now map postal/challenge result exits through the confirmed persistent `0x1a` destroy-return lane, route-map best-trial replay launches stay on the transient `0x1b` rebuild-return path, high-score replay pause abandon stays on the persistent destroy-return lane, transient route-map replay pause abandon now also stays on the non-clear rebuild lane, selected replay marker bit `0x8` now restarts the current replay through the confirmed destroy-return `state 26 -> owner 10` lane instead of jumping straight back to the route/high-score UI, persistent replay launches now also carry explicit saved return targets in Zig instead of inferring those returns from `SelectedLevelRecordSource` alone, ordinary non-replay challenge failures now return through the literal challenge-setup owner, ordinary non-replay Time Trial failures now return to the replay Star Map, ordinary failed postal/challenge score entry now captures its post-entry return owner as soon as the shared high-score screen takes over instead of staying on the completion-screen result path, ordinary pause-menu abandon score entry now returns through the same mode-owned failure lane after the shared high-score screen exits instead of the preserved gameplay launch surface owner, and transient postal replay final loss still follows the native `0x1a -> owner 2` New Game override because `complete_subgame` never seeds app byte `+0x30d` while `selected_level_record_active` is set
  - remaining gap: the current port still models the bridge as an explicit request dispatcher instead of a literal rebuilt outer-controller object, the full set of saved-owner producers behind native `26/27/28` is still incomplete beyond the now-confirmed `update_subgame` startup plus completion/failure/respawn lanes, and the New Game random replay attract launcher itself is still missing even though its bank rotation, persistent scratch lane, startup clear, click-start suppressor, `update_subgame` hide-latch consumer, `return_state = 2` write, and selector-`2` ordinary-launch split are now modeled; the remaining native questions there are the writer for the menu-local timer-step field at `data_4df904 + 0x4f2dc + 0x14`, the updater or reseed path for the `+0x8/+0xc` secondary suppressor lane, and whether any non-startup front-end helper seeds a different saved owner before `26/27/28`

### Phase 2. Finish cutscene and handoff runtime fields

- [ ] Find the writer(s) for the hotspot source matrices consumed by `update_snail_skin` and `update_cutscene`
- [ ] Capture intro, completion, and death hotspot-source values from Windows
- [ ] Confirm the exact failure selector and visible-life decrement commit point
- [ ] Confirm the exact completion-screen init, voice gate, and late finalize timings
- [ ] Replace any remaining handoff timers or anchor producers that still use Zig-side fallback values
  - current narrowing: non-random `course_end_threshold` now comes from the recovered final-`Last:` block boundary in `populate_runtime_track_cells_from_segments`, and random challenge-style previews now use the recovered `Length` / challenge-difficulty threshold producer; the remaining gap is that the preview still concatenates every candidate middle segment instead of the native generated random strip

### Phase 3. Finish attachment follow as a native runtime

- [ ] Recover the full installed-bank ownership and row-slot pairing rules
- [x] Finish the swept local-frame entry owner strongly enough to gate it behind the native `attachment_exit_pending` branch instead of the current broader gameplay trigger
  - current port shape: the live current-row prime path now owns both direct `29/30` begin and swept re-entry, so visited-row processing no longer opportunistically arms installed re-entry from older rows, the current row gates the swept probes through the recovered live owner bits (`0x40` first, then `0x80`), and raw BN plus IDA now show the first swept helper does not directly retire `attachment_exit_pending` before that `0x80` gate check
- [ ] Recover the real consumers and semantics of `attachment_exit_value_a` / `attachment_exit_value_b`
- [ ] Recover milestone semantics in `update_track_attachment_follow_state`, especially the missing voice-4 milestone lane
  - current narrowing: raw BN plus IDA now agree the `voice 4` call at `0x420d30` sits behind `sample_index + 1 == template->sample_count << 1`, while `begin_track_attachment_follow_state` seeds `sample_index = 0` and the same helper retires follow at `sample_index == template->sample_count`
  - consequence: do not port that cue until live tracing or stronger type recovery explains the counter mismatch
- [ ] Separate nonlinear kind-`42` behavior into real family semantics instead of one shared placeholder story
  - newer static narrowing: `attachment_exit_pending` is no longer a generic open search
  - BN field xrefs now show it is only written by `initialize_subgoldy_fall_state` plus five clear sites inside `update_subgoldy` (`0x43bcb3`, `0x43bf6f`, `0x43c06d`, `0x43c3ea`, `0x43ce75`)
  - the paired `attachment_exit_progress` lane is only written by the fall-state initializer and the single update store at `0x43ce96`, so there is no separate helper-side or plain progress-expiry clear in current static RE
  - stronger late-clear narrowing: `0x43ce75` sits behind `jetpack_gauge.state == 1` at `0x43ce23`, so it is not the generic/common retirement lane
  - stronger special-lane narrowing: `0x43bcb3` sits inside the non-follow floor-cache/slide motion block (runtime tiles `0x0f/0x10/0x12/0x13`, plus slide-family cells when `damage_gauge.state == 2`)
  - current Zig consequence: the old `progress >= 1.0` timeout clear is gone; active-phase retirement now only uses the confirmed jetpack clear plus a conservative grounded/trampoline settle proxy until the missing carryover owner is recovered
  - next narrowing: identify which later `update_subgoldy` clear wins after swept re-entry, especially whether it routes through `0x43bcb3` or the grounded/floor-snap lanes, then confirm with a live overlap whether two geometrically valid probes can overwrite each other in one tick

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
