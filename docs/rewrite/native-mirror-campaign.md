# Native-Mirror Campaign

The standing plan for converging the gameplay simulation on matched native
code. Update the board when a stage completes; this page is the cross-session
source of truth for "where are we and what's next".

Goal: every gameplay-sim cluster goes through the loop below until the
invented model is gone. Rendering, platform, audio backend, and asset code
are explicitly out of scope — that layer is the modern-engine upgrade and
stays idiomatic Zig.

## The loop

For each cluster, in order:

1. **Match** the cluster's functions (`tools/match`, rules in its README).
   100% or pinned-with-NOTES both count; semantics must be unambiguous.
2. **Mirror**: transcribe into `zig/src/gameplay/native/<cluster>.zig` —
   one Zig function per native function, native names and statement order,
   recovered struct layouts, documented seams. Transcription tests pin the
   behaviors that differ from the old model.
3. **Route**: switch runner call sites to the mirror module.
4. **Collapse**: delete the invented model, write the invalidation-ledger
   entry for every overturned assumption, update the checklist.

A cluster is **done** when the old code path no longer exists.

## Cluster board

Stages: `match` → `mirror` → `route` → `collapse`. ✅ done, 🚧 in progress,
· not started.

| # | cluster | key functions | match | mirror | route | collapse |
|---|---------|---------------|-------|--------|-------|----------|
| 1 | attachment follow | begin @ 0x420c40 (94.6%), swept entry @ 0x42c770 (79.8% pinned), **update @ 0x420cb0 pinned 06-12 (semantics complete, golf parked)**, project_position @ 0x4444b0 (56%) | 🚧 | 🚧 begin+swept+update stepping/gates + full pose-math chain (`native/matrix_math.zig`) | 🚧 follow update ROUTED 06-12: `stepAttachmentFollowAtRate` calls the mirror (stepping, exhaust/launch lanes, side-exit gate, vertical clamp); `endAttachmentIfNeeded` consumes the returned mode like update_subgoldy's switch; pose interpolation routed into worldPoseForTemplate | 🚧 invented stepping loop + `shouldSideExit` predicate deleted 06-12; entry-height + pose-lerp collapses ledgered; named seams: side_exit_mode (template+0x40) not surfaced on built templates, milestone row writes, voice 15, motion.y lane |
| 2 | player motion / exit lanes | update_subgoldy @ 0x43b120 dossiered with motion core + all five exit lanes specified 06-12 (gravity corrected to rate^2, +0x1e4 bounce byte decoded); carryover @ 0x43af60 (100%) | 🚧 | 🚧 motion core + grounding/trampoline lanes in `native/player_motion.zig` | · | · |
| 3 | collisions | handle_subgoldy_collisions @ 0x444cf0 — dossier + contact table done, all Zig gates verified clean 06-12 (match = proof-polish); remaining gaps are motion-slice consumers | 🚧 | · | · | · |
| 4 | hazard pools | salt quartet + sub-lazer trio ALL pinned 06-12 (spawn 98.4%, shoot/emitter/update structure-exact; update-state +0x38 vs free-flag +0x80 disambiguated, y-stagger and 4% fire gate recovered) | 🚧 | ✅ salt consolidated 06-12 (`gameplay/hazards.zig` sole home; tick integrates position per pinned asm; OB-1 fixed) | ✅ salt live with native exit set in `retireSaltHazards` | ✅ salt (`native/salt_pool.zig` deleted; containment-probe seam named) |
| 5 | damage / warning | apply_damage_gauge_delta @ 0x4413f0, update_damage_gauge @ 0x440fd0 (audit findings recorded), update_warning @ 0x446f80 | · | · | · | · |
| 6 | golb / projectiles | search_path + init_path_follow 100%; update_golb_ai dossier complete 06-12 (path-follow entry, riding via calc_path_length_z — a boss sibling — rocket homing, trail dispatch); spec is mirror-ready | 🚧 | · | · | · |
| 7 | cameraman | update_cameraman @ 0x4461d0 full pipeline recorded + Zig camera verified clean 06-12 (match = proof-polish, deprioritized); initialize_cameraman @ 0x446160 | 🚧 | n/a (camera verified in place) | · | · |
| 8 | row events / tips | update_row_event_display @ 0x404cf0 (78.5% WIP) | 🚧 | · | · | · |
| 9 | snail skin / presentation seams | all three skin functions (100%); renderer-side consumer still missing | ✅ | · | · | · |
| 10 | outer bridge / subgame state machine | update_subgame @ 0x438b90 (3.8KB), update_frontend_state_machine @ 0x4107d0, complete_subgame @ 0x438700 | · | · | · | · |

Order rationale: 1–2 are the historical churn bog (35+ fix commits) and
block the attachment-exit checklist items; 3–4 are next by audit-finding
density; 10 is last because the bridge spans app/runtime ownership and
benefits from everything below it being trustworthy first.

## Matching arc complete (2026-06-12)

Every important gameplay-sim function is matched, pinned, or fully
specified; clusters 3 and 7 verified clean; the motion port verifies
clean against the corrected update_subgoldy spec. Remaining named
residuals: ~~the +0x41c boost producer hunt~~ (RESOLVED 06-12: dead code,
no producer in the binary — see the ledger), the grounded-snap rotation
reset, the trampoline cell-y proxy, the orientation_a builder scalars,
the duplicate salt pools, and the deferred bridge cluster (10).

**Player-block unification (2026-06-12):** the "FollowState global at
game+0x430100" is the Player's embedded follow sub-struct at +0x384
(0x42fd7c + 0x384 = 0x430100). Its mystery tail fields are adjacent
Player fields: +0x90 = velocity.y, +0x94 = velocity.z, +0x99 =
attachment_exit_pending. Headers, the swept scratch (re-verified 79.80%),
and `native/attachment_follow.zig` renamed; full entry in the
invalidation ledger.

## Next actions (keep this list short and current)

1. ~~Route the follow update~~ DONE 06-12: `stepAttachmentFollowAtRate` now
   calls the mirror's `updateTrackAttachmentFollowState` (stepping, exhaust
   step, launch lanes, side-exit gate, vertical clamp); the invented stepping
   loop and `shouldSideExit` predicate are deleted; `endAttachmentIfNeeded`
   switches on the returned mode. Follow-up seams to close: surface
   side_exit_mode (template+0x40) on built templates, the milestone row
   writes, voice 15 on supertramp launch, and the motion.y vertical lane
   (checklist Phase 3 motion slice).
2. 🚧 Route runner begin/swept call sites: swept entry ROUTED 06-12
   (`installedAttachmentEntryForSweep` calls the mirror's
   `tryEnterTrackAttachmentFromSweptMotion`; the invented scan probed the
   center_x-shifted pose with deltas clamped ≥ 1.0 — native probes the raw
   sample origin with raw deltas and a strict local-z window; the runner's
   lateral lane derives from the mirror's `entry_local_x` minus center_x).
   Remaining: the direct begin lane (`currentRowInstalledAttachmentEntry` +
   `beginInstalledAttachmentFollow` are a faithful field-for-field
   transcription of the begin mirror but don't call it yet — converge when
   the cluster-2 entry conditions route).
3. Finish `try_enter_track_attachment_from_swept_motion` register alignment
   on standard flags (NOTES has the dual-slot source-shape lead).
4. ~~Consolidate the duplicate salt pools~~ DONE 06-12: `native/salt_pool.zig`
   deleted, its tests folded into `gameplay/hazards.zig`; the tick now
   integrates position per the pinned asm (the Android-cross-port anchored
   model is overruled), OB-1 fixed to a plain 0.0, and `retireSaltHazards`
   carries the native exit set (kill-plane proxy, y < 0, wall2 floor).
   Remaining named seam: the attachment containment probes need an
   `is_point_inside_track_attachment` port.
5. Finish `update_row_event_display` (78.5%) and
   `project_position_onto_track_attachment` (56%).

## Supporting workstreams

- **Matching queue discipline**: pick targets by (active churn × audit
  findings × cluster order above); record residuals in scratch NOTES;
  no-fakematching rules are in tools/match/README.md.
- **Verify/collapse passes**: after each cluster's matches land, diff the
  existing Zig model against matched truth before mirroring — confirmed-
  correct models (mirror coin, warning zones) get cited, wrong ones get
  ledgered (entry height). Every collapse gets an invalidation-ledger entry.
- **Original bugs**: proven native bugs go in
  [original-bugs.md](original-bugs.md); the port fixes them by default and
  `--preserve-bugs` restores original behavior for differential testing
  (switch in `zig/src/gameplay/native/original_bugs.zig`).
- **Harness upkeep**: bump `CACHE_VERSION` in `src/snail/match.py` whenever
  the normalizer changes; keep STATUS.md regenerated, never hand-edited.
- **Endgame instrumentation** (after clusters 1–4): per-tick state dump of
  the mirrored FollowState/Player fields on both native (frida) and Zig
  sides — the lockstep replay oracle becomes mechanical once layouts agree.
