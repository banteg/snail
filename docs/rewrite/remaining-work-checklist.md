# Remaining Work Checklist

This page is the long-form working checklist for remaining reverse-engineering
and porting work. Use it as the default backlog for current priorities,
known blind spots, and owner-level parity gaps.

Reference backlog:
- not default loop context
- the gameplay-sim convergence plan lives in [native-mirror-campaign.md](native-mirror-campaign.md) — start there for match/mirror/route/collapse work
- active execution should start from the current subsystem dossier or dated parity audit
- update this page when priority order changes or a blind spot materially closes, not for every local narrowing

It is intentionally narrower than the broad rewrite plan and more action-oriented than the status notes:

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

- `26` destroys the active subgame and jumps to the saved outer owner without reinitializing subgame
- `27` destroys, reinitializes subgame, then jumps to the saved outer owner
- `28` does the same as `27`, but clears `replay_active` first
- `29/30` are the Thanks For Playing owner, and `uninit_thanks_screen` hands that owner off to state `0x0e` (credits init)
- BN disassembly confirms the bridge destination is a dedicated front-end controller slot, not just the same active-state lane
- tutorial completion and ordinary postal final loss both use the `26 -> 2` return-to-New-Game lane

Practical impact:

- final loss vs successful completion and the remaining post-run owners still cross the app/runtime boundary too loosely; respawn now stores the direct `0x1c` rebuild selector and reuses only the rebuild effect endpoint
- challenge, time-trial, and replay-sensitive return routing are still not literal
- the current completion/death work now runs through one explicit owner-driven app-side bridge transition lane, but the full set of saved-owner producers and the literal Windows outer controller are still missing

### 2. Attachment follow semantics

Built-template follow is now strong enough to be useful, but the remaining gaps sit exactly where gameplay, camera, and state ownership meet:

- installed-bank ownership and pairing
- source-row installer semantics
- side-exit and natural-end return values
- family-specific nonlinear kind-`42` behavior
- the true meaning of the attachment-exit carryover lanes

### 3. Movement-state ownership

Audio RE now makes this much sharper than before: Windows still has a dedicated movement-state sound/controller layer. The emitter is exact `cRSubGoldy::Shoot`, and the live device chain is closed as mouse-left → controller slot 0 → root-owned `InputState`. The port mirrors the recovered selector-owned fire cadence, startup cooldown reseed, live press-vs-held lanes, runtime fire feature flag, replay raw-bit gate, attachment-exit suppression, and turbo-spread plus laser/rocket shot-family ratios, but still flattens the native device/controller ownership boundary.

### 4. Row-event/tip ownership

The authored ownership is closed as `cRTipData -> cRTipManager::TipNew -> cRTip`,
but the port still substitutes a runner-owned row-message token for the literal
payload tables and widget/timing behavior.

Practical risk:

- tutorial and parcel behavior can look close while still being driven from the wrong control boundary
- completion fast-forward is now closed as an authored lifecycle latch plus
  the primary-button pressed edge; remaining row-event risk is payload/widget
  timing rather than an unnamed `gate_18` controller source

### 5. Warning/damage owner

The authored `cRDamageGuage` and `cRWarning` controllers are recovered, but the
port still simplifies their exact voice-result-conditioned hit-flash timing and
has not yet wired the named invincibility capability at the Runner boundary.

### 6. Track render-normalization

This is still the biggest "quiet" rendering blind spot:

- warning-zone marking
- directional fringe ownership
- the remaining fringe-promotion BOD matching and marked-row run-merge semantics

Skipping these keeps presentation noisier than the runtime logic deserves and makes later visual audits harder.

### 7. Replay

Replay is partial rather than scaffolded now. The repo can preserve, browse, and launch selected postal/challenge/completion records through the recovered bridge lanes, and the challenge setup screen now uses the native transient challenge-setup replay mirror instead of the visible challenge score table. The New Game replay-attract probe/launch bridge is also modeled, but its native timer-step producer is still unknown/dormant. Compact replay payloads can now be synthesized in the recovered lane order, live runs now capture native-shaped samples through the gameplay update path, and live non-selected Time Trial runs now render the recovered two-sprite ghost from the completion replay's Z-delta lane; replay-side audio/effect parity, exact capture owner fields, exact ghost cursor offset around rebuilds, and full saveback parity are still not there.

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
  - stronger remaining gap: `update_new_game_menu`, `update_main_menu`, `update_high_score_screen`, and `exit_high_score_screen` still write active-state or replay-launch scratch globals without exposing another direct saved-owner store, so the missing part is now which other helper-driven producers exist beyond the confirmed gameplay-side writers
  - newer replay-launch narrowing: `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch both seed the same app-side replay scratch (`+119190`, `+4299515`, `+4299516`, `+17198056`, `+17198057`) before state `10`, and later consumers now line up too: `initialize_click_start`, `update_pause_menu`, and `update_completion_screen`
  - stronger replay-return narrowing: that `+4299516` / `app + 0x1066bf0` dword is not just a generic replay-side scratch slot; high-score replay rows seed it to `0x12`, the menu replay branch seeds it to `2`, and `update_completion_screen` state `3` later restores it directly
  - newer menu-attract narrowing: `update_new_game_menu` rotates a menu-local cursor through `0..4`, but only values `0/1/3` probe replay banks, write `app + 0x74658 = 0/1/4`, and seed the persistent replay scratch; that probe loop reuses the same `0x1fac0` bank stride, caps out after `1000` attempts, and is gated by menu-local float accumulator / step fields at `data_4df904 + 0x4f2dc + 0x10/+0x14`; BN static inspection now shows `+0x14` starts as zero and has no direct absolute xrefs outside the `update_new_game_menu` read, so the current port keeps the attract branch dormant instead of inventing a timer
  - newer startup-side narrowing: `initialize_game_assets_and_world` clears app bytes `+17198056/+17198057` at boot, `initialize_subgoldy` unconditionally calls `initialize_click_start`, `initialize_click_start` hides its prompt when `+17198056` is already set, and `update_subgame` later clears the menu-local hide latch only after `data_4df904 + 0x4f2e4` exceeds `1.0`, so persistent replay starts own that suppression path directly instead of inheriting stale global state
  - newer controller-layout narrowing: the same menu-local object at `data_4df904 + 0x4f2dc` now has a firmer shape: cursor `+0x0`, likely hide latch `+0x4`, hide-release accumulator `+0x8`, hide-release step `+0xc` reset to `1/3600` after replay-attract launch or miss, and attract accumulator/step `+0x10/+0x14`
  - likely next step: trace `[controller + 0x98]`, `data_4df904 + 110`, `+119190`, `+4299515`, `+4299516`, and `+17198056/+17198057` together in one Windows session
- [x] Port rebuild/teardown/return ownership into one explicit boundary instead of distributing it across runner and app helpers
  - current port shape: result exits and abandon exits now route through one owner-driven bridge transition lane with native opcode names plus explicit saved-owner and saved-replay-return state on `AppState`
- [ ] Mirror the `destroy_subgame → app+0x1bc = 0x12` outer-bridge safety net (native 0x438b09); current Zig paths compute the right owner via helpers, so this is defensive — defer until a repro surfaces
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
  - current Zig consequence: high-score replay launches now map postal/challenge result exits through the confirmed persistent `0x1a` destroy-return lane, route-map best-trial replay launches stay on the transient `0x1b` rebuild-return path, high-score replay pause abandon stays on the persistent destroy-return lane, transient route-map replay pause abandon now also stays on the non-clear rebuild lane, selected replay marker bit `0x8` now restarts the current replay through the confirmed destroy-return `state 26 -> owner 10` lane instead of jumping straight back to the route/high-score UI, persistent replay launches now also carry explicit saved replay return owners in Zig instead of inferring those returns from `SelectedLevelRecordSource` alone, ordinary non-replay challenge failures now return through the literal challenge-setup owner, ordinary non-replay Time Trial failures now return to the replay Star Map, ordinary failed postal/challenge score entry now captures its post-entry return owner as soon as the shared high-score screen takes over instead of staying on the completion-screen result path, ordinary pause-menu abandon score entry now returns through the same mode-owned failure lane after the shared high-score screen exits instead of the preserved gameplay launch surface owner, and transient postal replay final loss still follows the native `0x1a -> owner 2` New Game override because `complete_subgame` never seeds app byte `+0x30d` while `selected_level_record_active` is set
  - remaining gap: the current port now stores owner-driven bridge state directly on `AppState`, but the full set of saved-owner producers behind native `26/27/28` is still incomplete beyond the now-confirmed `update_subgame` startup plus completion/failure/respawn lanes, and the New Game replay attract launcher is only partially live: its bank rotation, persistent scratch lane, startup clear, click-start suppressor, `update_subgame` hide-latch consumer, `return_state = 2` write, post-probe hide-release reset, and selector-`2` ordinary-launch split are modeled, but the trigger stays dormant because the shipped menu-local timer-step field at `data_4df904 + 0x4f2dc + 0x14` is zero; the remaining open pieces are that launch-step producer and any non-startup front-end saved-owner producers

### Phase 2. Finish cutscene and handoff runtime fields

- [x] Find the writer(s) for the hotspot source matrices consumed by
  `build_snail_world_hotspots` and `update_cutscene`
  - exact-matched `update_snail_presentation` writes both each tick: `+0x1604`
    receives the final rendered `Snail::body.transform`; `+0x1684` receives
    the owner player's live body transform with its translation replaced by
    `Player::cached_camera_target_world`
  - `build_snail_world_hotspots` routes hotspot slots `0..10` through `+0x1684` and
    slots `11..18` through `+0x1604`
- [ ] Capture intro, completion, and death hotspot-source values from Windows
- [x] Confirm the exact failure selector and visible-life decrement commit point
  - exact `cRSubGoldy::DeathInit()` selects `RessurectInit(0)` for Postal
    spare-life respawn and `RessurectInit(1)` at zero lives; Challenge and Time
    Trial select final loss, while tutorial remains respawnable
  - the checked-in CDB session proves the delayed Postal decrement at
    `RessurectAI + 0x8b` (`0x44205b`) and the resulting write at `0x442061`;
    final loss does not decrement again
  - slug and floor-gap deaths have distinct entry lanes but converge on this
    selector. The `world_y < -7` check is the floor-fall entry threshold, not a
    second outcome owner, so no further selector/writer trace is needed
- [ ] Pin the exact cutscene-state-to-`cRCompletion::Init` timing with a corrected
  Windows decode
  - the arm, `2.0s` voice gate, `5.1 -> ~4.983` timer plateau, first Init call,
    and first `complete_subgame` call are already captured and statically closed
  - the remaining capture question is which decoded cutscene state owns the Init
    edge; the checked-in completion hook confirms the call but misdecodes its
    derived player/game fields
- [ ] Replace any remaining handoff timers or anchor producers that still use Zig-side fallback values
  - current narrowing: non-random `course_end_threshold` now comes from the recovered final-`Last:` block boundary in `populate_runtime_track_cells_from_segments`; random challenge-style previews now generate a seeded middle strip with the recovered `Length` / challenge-difficulty threshold producer, candidate-pool scalar, and segment-overrun extension. `SubSegment::visited` is the exact byte at `+0x08`: both Windows and Android `BuildLevel()` clear every eligible slot and set the chosen slot, but this builder does not consult it while selecting, so it is write-only bookkeeping here rather than a recovered no-repeat constraint. Remaining gap: exact row-copy source shape, not owner identity.

### Phase 3. Finish attachment follow as a native runtime

- [ ] Recover the full installed-bank ownership and row-slot pairing rules
- [x] Finish the swept local-frame entry owner strongly enough to gate it behind the native `attachment_exit_pending` branch instead of the current broader gameplay trigger
  - current port shape: the live current-row prime path now owns both direct `29/30` begin and swept re-entry, so visited-row processing no longer opportunistically arms installed re-entry from older rows, the current row gates the swept probes through the recovered live owner bits (`0x40` first, then `0x80`), and raw BN plus IDA now show the first swept helper does not directly retire `attachment_exit_pending` before that `0x80` gate check
- [x] Bound the two post-follow carryover lanes
  - `post_follow_exit_roll` is closed: while `attachment_exit_pending`,
    `update_cameraman` applies it as a world-z roll between the follow
    orientation rotations and `heading_roll`
  - `post_follow_heading_carryover` is write-only captured state in the shipped
    Windows program: exact `begin_post_follow_carryover` supplies its only two
    field references (copy or zero), while a whole-image search finds no load;
    mobile bodies corroborate the paired producer only, so do not invent a
    common gameplay consumer without new evidence
- [x] Recover milestone semantics in `update_track_attachment_follow_state`, especially the missing voice-4 milestone lane
  - resolved as dead code: the field at `[esi+0x44]` is `PathTemplate::segment_count` (not `sample_count` — the HLIL `_pad_3c[8].d` rendering is a char-pad byte index into the 0x3c-aligned block). The gate `sample_index + 1 == segment_count * 2` at `0x420d1d` is unreachable because the helper terminates at `sample_index == segment_count` first, with `sample_index` starting at 0 and advancing by 1. There is no second increment path or field aliasing that could close the gap. Do not port.
- [ ] Separate nonlinear kind-`42` behavior into real family semantics instead of one shared placeholder story
  - entry-height narrowing (2026-06-12, matched source): neither entry lane is family-dependent — direct begin seeds world `y - 0.49`, swept entry seeds `0` plus a player-y snap; whatever kind-`42` distinctness remains lives in the follow update / exit lanes, not entry seeding (see invalidation ledger)
  - `attachment_exit_pending` is no longer a generic open search: exact begin
    arms it, and `update_subgoldy` contains four distinct live retirements plus
    one dead `boost_one_tick` clear (`0x43bcb3`, with no nonzero Windows
    producer)
  - `0x43bf6f` retires the ordinary occupied, non-trampoline grounded envelope;
    the pending clear is unconditional once that envelope is reached even when
    upward velocity suppresses the accompanying y/velocity snap
  - `0x43c06d` cancels a just-armed open-edge exit in the same tick when falling
    is disabled (or cheat flag `0x2` is set), restoring the low player to
    `y=0.49`
  - `0x43c3ea` retires only after the trampoline envelope accepts the player,
    then launches vertical velocity, sets the bounce latch, and plays SFX 41;
    `0x43ce75` gives active `SubHover` authority and clears before the
    progress/voice consumer
  - retirement clears only the pending byte; there is no helper-side or plain
    `progress >= 1.0` expiry, and exact begin overwrites the lifecycle state on
    the next arm
  - current Zig consequence: the broad trampoline-or-non-open-neighbor proxy
    still fires too eagerly and should be replaced by these four authored
    outcomes when the minimum motion fields land
- [ ] Port the minimum player motion slice needed to tighten attachment-exit retirement to the native lanes (harvested from the retired 2026-04 infrastructure plan)
  - fields: `position_y` (Player+0x6c, rest value `0.49`), `velocity_y` (Player+0x414), `follow_active` derived from the existing follow state machine (Player+0x384)
  - steps (corrected 2026-06-12 from the update_subgoldy consumer read): gravity is `velocity.y += subgame_rate^2 * -0.01` inside the shared integration, with drags vz/vy *= (1 - rate*0.003), vx *= (1 - rate*0.1) and the shared acceleration quantum `2 * rate^2 * 0.004` (following non-DETOUR, slide tiles, jetpack; the +0x41c boost lane is dead — no producer in the binary, see the 06-12 ledger entry); then `position += velocity` — see tools/match/scratches/update_subgoldy/NOTES.md
  - the `attachment_exit_progress` step at 0x43ce96 is the explicit else-branch — it only runs when neither 0x43bcb3 nor 0x43bf6f fired this tick
  - `begin_post_follow_carryover` @ 0x43af60 is matched 100% in `tools/match/scratches/begin_post_follow_carryover`; port from the matched source, not HLIL
  - deferred follow-ups: 0x43c06d re-snap needs the cell `open_edge_mask` + global flag 2 mirror; 0x43c3ea trampoline needs a `cell_y` accessor (current proxy fires too eagerly; corrected 06-12: the bounce SETS vy = rate*0.3 rather than flipping velocity, snaps y to anchor+0.49, and sets the +0x1e4 bounce byte that gates the vz drag); 0x43ce75 needs `position_y` plus a native `sub_hover.state == 1` mirror; full `velocity.x/z` model and the ±4 lateral clamp come last
  - new consumer (2026-06-12, boss dossier): `update_track_attachment_follow_state` accumulates the caller's `motion.y` into `follow_state.vertical_offset` every normal-path tick and zeroes both on the negative-offset clamp — so attached riders fall onto / lift off the path through the vertical velocity lane; the Zig follow keeps the offset constant until the motion slice lands
  - new consumer: the follow update publishes the rider basis rows into the **player live_matrix** (player+0x38..0x58) each tick — the matrix is the authoritative source other native systems read; the Zig port derives poses from the template per consumer instead (wrong-source-lane class, fold into the cluster-1 mirror routing)
  - builder gap: native per-sample rotation scalars (+0x94 feeds the live orientation_a lerp; +0x98 only the dead lane) are not stored by the Zig template builder; orientation_a uses a basis-derived proxy until they are

### Phase 4. Recover the missing gameplay owners exposed by audio

- [x] Recover the literal input-device source behind
  `play_subgoldy_shoot_sfx`: mouse-left publishes `0x4000` through controller
  slot 0 into the root-owned `InputState` borrowed by Goldy. The emitter owner
  is exact `cRSubGoldy::Shoot(cRSubGoldy*)` / `shoot_subgoldy`.
- [ ] Add a projectile-specific visual smoke path for the movement-fire VAPOURLAZER trail. The current laser-shot render fix is grounded in `create_golb` / `initialize_vapour` / `update_vapour`, but the CLI smoke path still cannot script a fired shot and capture the generated trail for visual regression review.
- [ ] Port Golb shot path-follow over attachment cells. Native `update_golb_ai` @ 0x414820 switches a shot into path-follow mode (`initialize_path_follow_golb` @ 0x421770, `traverse_path_follow_golb`, `search_path_for_golb` @ 0x415e30) when it crosses a tile-`0x1e` cell, so shots ride humps/loops instead of flying level through them. The port now has the kind-0 `[0, 0.49]` level band + `subgame_rate * 0.017` gravity and the lifetime/window despawn from `create_golb`/`update_golb_ai`, but not the path-follow lane (also the rocket homing lane fed by `search_path_for_golb` at spawn). The initializer and search helper are proof-grade; `traverse_path_follow_golb` is semantics-complete at 85.82% with a documented scheduling residual. Port from those matched or pinned sources: candidate samples are gated on `0 < dz < 30` toward positive z and chosen by nearest 3D magnitude, first-best-wins.
- [ ] Port the literal `cRTipData` payload-table contents and `cRTip` widget/timing
  behavior behind `voice 13`; the actor/controller lifecycle owner is closed
- [x] Recover the real warning actor/controller behind `update_warning`
- [ ] Finish the remaining collision/powerup Zig and presentation work beyond
  the recovered primary matcher owners `cRSubHealth`, `cRSubRing`, and
  `cRSubRingStar`, the now-ported ring-kind ladder (`1`, `2/6`, `3/7`,
  `4/5/8`), runtime pickup collision slots, health bob lane, jetpack ramp-bias
  spawn lane, jetpack `JETPACKTHRUST` pre-warning visual lane, ring post-hit
  `2 -> 3` effect lane, and the recovered `health_collect_particles` burst
  packet. Remaining work includes `cRParcel` / `cRParcelManager` flight and
  delivery parity, `cRSubGarbage` impact parity, the original pre-hit ring BOD
  anchor/layout fields, the dedicated
  jet-particle/nozzle owner, and deeper weapon presentation. The health burst
  itself is closed as eight generic SpriteManager records borrowing position
  from the separate inline `cRSubHealth` actor; no dedicated particle BOD
  exists.
- [ ] Finish the remaining hit-flash presentation timing in the damage-warning
  owner.
  The `stop_warning_sample` contract is closed: Windows starts registered sample 50
  and immediately stops the returned channel handle without storing it;
  Android's helper is a no-op.
  - the entry gate is closed: exact `cRSubGoldy::SetShootFlags()` is the
    complete nonzero producer of `SUBGOLDY_SHOOT_FLAG_INVINCIBLE` (`0x80`),
    and exact `cRDamageGuage::Take(float, bool)` blocks unforced deltas while
    that capability is active. The port controller API already carries the
    force bypass and explicit unforced-delta context, but the Runner boundary
    still needs to wire the named shoot-flag producer; do not request another
    writer trace
  - the remaining hit-flash presentation question is the exact voice/animation
    timing: `change_snail_skin(slot 1, 0.2s)`, the `damage` voice with `ouch`
    fallback, then both animation `6` immediate and animation `1` queued only
    while `slug_fall_active` is clear
  - state-2 drain side effects: `change_snail_skin(slot 1, 0.2s)` each tick while draining, `postal` voice on the 1→2 transition, and the closed Windows start-then-stop sample-50 quirk on state-2 exit
  - the former accelerated-drain mystery is closed as
    `Player::completion_handoff_active`: one arming writer and three gauge
    consumers compose a 5× automatic drain; no new writer trace is needed

### Phase 5. Tighten gameplay runtime ownership

- [ ] Port the remaining ambient hazard suppressor details beyond the
  generated-garbage postal/time-trial mode gates. `DeSaltTrack` is now closed
  as a six-row, two-lane producer of the independent salt (`0x08`) and garbage
  (`0x10`) spawn-suppression bits; it has no render/cache consumer.
- [x] Recover literal authored lazer and salt ownership. The matcher now uses
  primary `cRSubLazer` / `cRSubLazerManager` and `cRSalt` / `cRSaltManager`
  owners; `SubLazer`, `SubLazerManager`, `Salt`, and `SaltManager` remain
  compatibility typedefs only.
- [ ] Port those recovered owners beyond the Zig runtime's current plain-array
  equivalents: inherited BOD/list participation, object/sprite presentation,
  suppression gates, and any remaining non-horizontal suppressor details are
  still open. Historically misnamed "Wall2 ambient pool" in these docs — the
  Wall2 tile is the *emitter*, and `cRSubLoc::AI()` fires the
  `cRSubLazerManager` slots through `shoot_sub_lazer_pool` @ 0x441ad0.
  Reference: `update_sub_loc` @ 0x439d50 (RNG gate plus
  `game+0x74668 > game+0x42fdec` cadence), `spawn_sub_lazer_projectile` @
  0x441670, `deactivate_sub_lazer_projectile` @ 0x441740,
  `update_sub_lazer_projectile` @ 0x4417d0, `cRSaltManager` at
  `game + 0x3578c0`; salt helpers: `initialize_salt_hazard_pool` @ 0x441540,
  `spawn_salt_hazard` @ 0x441560 (authored `0x22` tiles and `0x0f` with RNG
  gate `0.98 + 0.02*(1-scalar)`), and `update_salt_hazard` @ 0x441c10.
- [ ] Port jetpack state 2 from the recovered `cRSubHover` lifecycle (`Init`,
  `On`, `AI`, `Hover`, `End`, and jet-particle helpers); owner recovery is closed,
  while the broader hover-mode gameplay/presentation port remains unprioritized
- [x] Recover the completion fast-forward input/controller contract:
  `cRCompletion::Init` arms `fast_forward_enabled`, its exact AI clears the
  latch on summary activation, and the sole Goldy consumer combines it with
  `InputState::pressed_buttons & 0x4000`; the fixed player-0 UI and primary
  Goldy routes alias `game_inputs[0].input`
- [ ] Recover parcel-flight and row-event widget timing details that still rely on app-side or inferred helpers
- [ ] Port the missing score events tied to replay, jetpack, slug kills, and the remaining unresolved branches
- [ ] Port the recovered slug-hit velocity writes and sticky
  `slug_fall_active` mode (harvested from the retired 2026-04 infrastructure
  plan)
  - first hit: velocity triplet `(0, tc_x*0.2, -tc_x*0.2)` plus `begin_post_follow_carryover`, cutscene state `0xa`, `firework_shoot`, and `play_slug_voice(0x22 - rand)`
  - repeat hit: z-velocity knockback `tc_x² × 0.004 × -8`
  - garbage impact: slot `+0x88` direction-of-hit field is left when normalized collision x is negative, right otherwise
- [ ] Small recovered gates, low impact: global pause gate `data_4df904 + 0x74621` on `update_warning` / `update_damage_gauge` / the pulse lane; health and jetpack pickup per-slot `player.live_matrix.position.y >= 0.49` gate (needs `position_y`)

### Phase 6. Recover track render-normalization

- [x] Close the `mark_track_warning_zones` footprint as gameplay spawn policy:
  it stamps the salt/garbage suppression pair and has no render/cache consumer
- [ ] Port the remaining edge and exact BOD-table fringe-promotion passes
- [ ] Port directional fringe allocation and its transient cache-staging
  handoff; native ownership is closed, while broader cache-family routing is
  still open
- [ ] Re-audit gameplay and segment-view rendering only after these normalization passes are in

### Phase 7. Finish replay only after the runtime consumers exist

- [x] Hook initial runtime replay capture/saveback for new score entries using the recovered sample order and fixed-point scales
- [x] Port the recovered Time Trial ghost Z-delta consumer for saved completion records
- [x] Recover the selected-record gameplay/audio/effect multiplexer: recorded
  movement/track/end flags, Time Trial ghost suppression/pinning, and recorded
  fire bits all key off `selected_level_record_active`.
- [ ] Port full replay payload read/write parity
- [ ] Only then widen replay saveback behavior for new entries

### Phase 8. Tighten presentation layers last

- [ ] Finish Turbo gameplay anchor/orientation and broader state-specific animation switching
  - `dispatch_cutscene_animation` @ 0x444600 is authored `cRSnail::SetAnimation(animation_id, immediate, mode)`: `Snail` owns `AnimManager +0x104` and ten `RenderableBod` animation slots from `+0x14c` at 0x80-byte stride; each slot's borrowed `Object*` is at `+0x24`. `immediate=false` appends the id to `queued_animations[queue_count++]`; `immediate=true` installs the slot animation and root object, applies mode unless it is `-1`, initializes forward or reverse progress, clears the queue, and sets the target model's `BOD_FLAG_RENDER_ENABLED`
  - anim ids: `1`=base, `3`/`4`=lookback-L/R, `5`=skidstop, `6`=damaged, `7`=intoshell, `8`=fall, `9`=talk; per-clip keyframes come from the shipped `X/_ANIMATION.TXT` entries
  - replace the manual turbo-talk family switch with a real `dispatch_cutscene_animation(.talk, immediate, 0)`
- [ ] Jet-particle pool + `SPRITES/JETPACKTHRUST.TGA` / `SPRITES/SMOKE.TGA` loading (presentation polish; the sfx and mesh-swap lanes are already covered)
- [ ] Recover non-billboarded actor ownership where the original runtime uses real object/model controllers
- [ ] Tighten combat VFX ownership after the underlying controller is recovered
- [ ] Hook the snail-skin render-state material index lookup once the snail-presentation render layer is ported — native ownership is now recovered as the exact `cRSnailSkin` child, while the Zig port's `SnailSkinTransition` state still has no renderer-side consumer
- [ ] Tighten remaining frontend widget polish only when ownership is already understood
  - current narrowing: native widget shortcut keys are now ported for pause-menu and post-level high-score flows; the remaining gap is shared widget-controller polish, not basic keyboard activation ownership

## Decompile Targets By Priority

Every score-residual/non-proof scratch ledger remains formally stalled. Do not
restart a fuzzy-score sweep without a new producer, consumer, field xref, or
original-source clue. The next work is authored-owner promotion over exact
core leaves, in this evidence order:

1. Promote primary `cRFringe` / `cRFringeManager` across the exact constructor,
   callback AI, manager `Init`, and `GetFringe` leaves. The Windows pool is
   exactly `7000 * 0x38` plus its count. Keep `build_track_fringe_objects`, both
   fringe-mesh builders, and tile promotion frozen at their bounded partial
   frontiers.
2. Promote primary `cRLogo` / `cRLogoLetter` across the exact child constructor,
   `Open`, `UnInit`, parent `AI`, and child `AI` leaves. Integrate the authored
   `cRLogo::Init(char*)` name without reopening its frozen `88.89%`, `523/521`,
   prefix-`88` residual.
3. Promote primary `cRGalaxy` / `cRGalaxyStar` across the seven exact lifecycle,
   route-box, line, child-AI, and border-bound leaves. Keep the layout loader at
   `88.27%` and the outer AI at `71.01%`; this is owner routing, not another
   score sweep or a mobile-offset transplant.

Do not keep already proof-grade or evidence-closed lanes active merely because
an older plan named them. Primary `cRFade`, `cRFlash`, `cROverlay`, `cRSubPause`,
`cRVapour`, `cRSubSpeedUp`, `cRJetPack`, `cRSubRow` / `cRRowModel`,
`cRClickStart`, `cRSubHealth`, `cRSubRing` / `cRSubRingStar`, `cRSubLazer` /
`cRSubLazerManager`, `cRSalt` / `cRSaltManager`, `cRSubGarbage`, `cRSlug` /
`cRSlugVoiceManager`, `cRParcel` / `cRParcelManager`, `cRCutScene`,
`cRSubHover`, Tip-family, `cRInvincible`, `cRDamageGuage`, and `cRCompletion`
ownership, the named
invincibility capability, the death selector/life commit,
the completion fast-forward/input lifecycle, slug-hit motion and
`slug_fall_active`, the selected-record gameplay multiplexer,
directional-fringe/cache staging, Golb
trail/impact shot-slot ownership, warning sample and completion-drain gates,
random-hazard suppression, `active_window_min_z`, the live firing input chain,
health-particle ownership, and write-only SpriteExtend state are closed. The
hotspot/cutscene spill, attachment-exit clears, follow update, outer replay
bridge, fringe receiver swaps, Golb allocator schedules, and collision stack
coloring are bounded compiler residuals. Sprite `+0x20/+0x24` is dormant ABI
documentation debt: every Windows allocator call passes `-1/-1` and no shipped
renderer consumes it, so do not invent semantics or mutate exact Sprite code.

## Checklist Discipline

While working through this list:

- when an item hinges on the exact semantics of a single contested function, match it first (`tools/match`, see its README) and port from the matched C++ instead of re-reading HLIL
- the gameplay simulation core is migrating to native-mirror modules under `zig/src/gameplay/native/` — one Zig function per matched native function, native names and statement order, no invented abstraction layers; rendering/platform/asset code stays idiomatic Zig (the modern-engine layer is intentionally not a mirror)
- do not count UI parity as proof that the owning runtime controller is ported
- prefer replacing fallback producers with recovered native fields before tuning presentation
- update the relevant status docs whenever a blind spot is closed or narrowed
- if a checklist item turns out to depend on a different upstream owner, move the checklist order instead of papering over the dependency
