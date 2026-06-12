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
| 1 | attachment follow | begin @ 0x420c40 (94.6%), swept entry @ 0x42c770 (pinned), **update @ 0x420cb0 (2.7KB, unmatched — defines the FollowState contract)**, project_position @ 0x4444b0 (56%) | 🚧 | 🚧 begin+swept in `native/attachment_follow.zig` | · | 🚧 entry-height collapse ledgered 06-12 |
| 2 | player motion / exit lanes | update_subgoldy @ 0x43b120 (8.5KB boss; five retirement lanes), begin_post_follow_carryover @ 0x43af60 (100%) | 🚧 | · | · | · |
| 3 | collisions | handle_subgoldy_collisions @ 0x444cf0 (2.9KB; all contact constants, slug radius finding) | · | · | · | · |
| 4 | hazard pools | salt quartet done (100/74/48/41, quirks ledgered) and mirrored in `native/salt_pool.zig`; spawn_sub_lazer @ 0x441670 (98.4%); remaining: wall2 emitter @ 0x439d50, shoot_subgoldy @ 0x441ad0, sub-lazer update @ 0x43efb0 | 🚧 | 🚧 salt done | · | · |
| 5 | damage / warning | apply_damage_gauge_delta @ 0x4413f0, update_damage_gauge @ 0x440fd0 (audit findings recorded), update_warning @ 0x446f80 | · | · | · | · |
| 6 | golb / projectiles | search_path @ 0x415e30 (100%), init_path_follow @ 0x421770 (100%), update_golb_ai @ 0x414820 (2.7KB) | 🚧 | · | · | · |
| 7 | cameraman | update_cameraman @ 0x4461d0 (matrix constants in 06-10 audit), initialize_cameraman @ 0x446160 | · | · | · | · |
| 8 | row events / tips | update_row_event_display @ 0x404cf0 (78.5% WIP) | 🚧 | · | · | · |
| 9 | snail skin / presentation seams | all three skin functions (100%); renderer-side consumer still missing | ✅ | · | · | · |
| 10 | outer bridge / subgame state machine | update_subgame @ 0x438b90 (3.8KB), update_frontend_state_machine @ 0x4107d0, complete_subgame @ 0x438700 | · | · | · | · |

Order rationale: 1–2 are the historical churn bog (35+ fix commits) and
block the attachment-exit checklist items; 3–4 are next by audit-finding
density; 10 is last because the bridge spans app/runtime ownership and
benefits from everything below it being trustworthy first.

## Next actions (keep this list short and current)

1. Match `update_track_attachment_follow_state` @ 0x420cb0 — unlocks the
   FollowState contract, cluster 1 route/collapse, and the voice/milestone
   semantics. Signature already recovered: thiscall,
   `(float rate, int* sample_index, Vector3* position)`.
2. Route runner begin/swept call sites through `native/attachment_follow.zig`
   (map `attachment.follow` reads to FollowState fields; keep the y-snap
   seam from the module doc).
3. Finish `try_enter_track_attachment_from_swept_motion` register alignment
   on standard flags (NOTES has the dual-slot source-shape lead).
4. Route the runner's salt lanes through `native/salt_pool.zig` (replaces
   the runner-local salt live strip per checklist Phase 5), then match the
   sub-lazer trio (wall2 emitter, shoot_subgoldy, update @ 0x43efb0) and
   extend the mirror.
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
- **Harness upkeep**: bump `CACHE_VERSION` in `src/snail/match.py` whenever
  the normalizer changes; keep STATUS.md regenerated, never hand-edited.
- **Endgame instrumentation** (after clusters 1–4): per-tick state dump of
  the mirrored FollowState/Player fields on both native (frida) and Zig
  sides — the lockstep replay oracle becomes mechanical once layouts agree.
