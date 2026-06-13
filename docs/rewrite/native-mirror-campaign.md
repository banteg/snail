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

Naming rule (2026-06-13): any Zig function corresponding to a native
function carries the native name camelCased (`calc_subgame_rate` ->
`calcSubgameRate`) — greppable against the decompile, mechanical to port.
Runner helpers covering a SLICE of a big native fn get region names
(`updateSubgoldyMotionCore`), never invented concepts. Rename legacy
invented names when touched.

Decomposition rule (2026-06-13): `gameplay.zig` (~12k lines) is a god
object — every route/collapse step moves the surviving slice into its
cluster module instead of leaving it inline; the end state is gameplay.zig
as a thin orchestrator over `gameplay/<area>.zig` + `gameplay/native/*`.

A cluster is **done** when the old code path no longer exists.

## Cluster board

Stages: `match` → `mirror` → `route` → `collapse`. ✅ done, 🚧 in progress,
· not started.

| # | cluster | key functions | match | mirror | route | collapse |
|---|---------|---------------|-------|--------|-------|----------|
| 1 | attachment follow | begin @ 0x420c40 (94.6%), swept entry @ 0x42c770 (79.8% pinned), **update @ 0x420cb0 pinned 06-12 (semantics complete, golf parked)**, project_position @ 0x4444b0 (56%) | 🚧 | 🚧 begin+swept+update stepping/gates + full pose-math chain (`native/matrix_math.zig`) | 🚧 follow update ROUTED 06-12: `stepAttachmentFollowAtRate` calls the mirror (stepping, exhaust/launch lanes, side-exit gate, vertical clamp); `endAttachmentIfNeeded` consumes the returned mode like update_subgoldy's switch; pose interpolation routed into worldPoseForTemplate | 🚧 invented stepping loop + `shouldSideExit` predicate deleted 06-12; entry-height + pose-lerp collapses ledgered; named seams: milestone row writes, voice 15, motion.y lane (side_exit_mode RESOLVED 06-12: all 29 constructors write 0 — blocked side exits are dead config) |
| 2 | player motion / exit lanes | **update_subgoldy @ 0x43b120 SCRATCHED 06-13 (72.30%, 2075/2091 insns, structure complete — residuals are regalloc-class, see NOTES)**; the unread track-mode slice is now pinned: steering anchor model, per-tick 16-bit lateral quantization, replay record/playback, completion handoff machine, ghost marking, fire emitters; cruise boost cadence resolved to ring/speedup collisions (NOT tiles); carryover @ 0x43af60 (100%) | 🚧 | 🚧 motion core + grounding/trampoline lanes in `native/player_motion.zig` | · | · |
| 3 | collisions | handle_subgoldy_collisions @ 0x444cf0 — dossier + contact table done, all Zig gates verified clean 06-12 (match = proof-polish); remaining gaps are motion-slice consumers | 🚧 | · | · | · |
| 4 | hazard pools | salt quartet + sub-lazer trio ALL pinned 06-12 (spawn 98.4%, shoot/emitter/update structure-exact; update-state +0x38 vs free-flag +0x80 disambiguated, y-stagger and 4% fire gate recovered) | 🚧 | ✅ salt consolidated 06-12 (`gameplay/hazards.zig` sole home; tick integrates position per pinned asm; OB-1 fixed) | ✅ salt live with native exit set in `retireSaltHazards` | ✅ salt (`native/salt_pool.zig` deleted; containment-probe seam named) |
| 5 | damage / warning | apply_damage_gauge_delta @ 0x4413f0, update_damage_gauge @ 0x440fd0 (audit findings recorded), update_warning @ 0x446f80 | · | · | · | · |
| 6 | golb / projectiles | search_path + init_path_follow 100%; update_golb_ai scratch 20.8% structure-complete (full semantics); calc_path_length_z = boss sibling | 🚧 | 🚧 `native/golb.zig` 06-13 (band gravity, homing, trails, spin, slug deflection, contact band, path-entry predicate — all tested) | 🚧 live lanes ROUTED 06-13: band gravity, 3D slug deflection (2D approximation collapsed), contact band, smoke fraction; REMAINING: homing target acquisition, golb FollowState riding (calc_path_length_z ≈ updateTrackAttachmentFollowState), trail-sprite triple | · |
| 7 | cameraman | **update_cameraman @ 0x4461d0 PINNED 06-12 (92.55%, 322/322 insns exact — register-allocation residual only)**; asm resolved the exit-roll carryover lane (+0x42c = orientation_b, Zig camera already correct) and re-confirmed the unified follow slots; initialize_cameraman @ 0x446160 | 🚧 | n/a (camera verified in place) | · | · |
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

## Oracle leads from the update_subgoldy scratch (2026-06-13)

1. **Lateral codec parity**: native quantizes `position.x` through the
   16-bit replay codec (`16.0` scale round-trip) EVERY tick before
   recording — if the port integrates unquantized x, lateral drift vs
   recordings accumulates. Audit the runner's lateral lane.
2. **Cruise cadence**: track mode has NO per-tile z boost. The 0.24-0.31
   oscillation = ring-effect collision boosts (`vz = rate*0.5`) decaying
   via `(1 - rate*0.003)` toward the `rate*0.17` window floor.
   (CORRECTED 06-13: the speedup pickup half is dead config —
   `spawn_track_speedup` @ 0x43d880 is an EMPTY STUB in the shipped
   binary, so the collisions speedup lane never fires; rings are the
   only cruise boost. Same cut-feature class as the +0x41c boost byte.) The port already models the rate*0.5 ring
   lane (`applyNativeForwardVelocityRing`), so the drag-to-floor symptom
   means rings are being MISSED or mistimed along the recorded path —
   which is exactly the grid-alignment audit's open "collision probes"
   consumer conversion. Converting those probes to containing-cell
   sampling + instrumenting ring-hit ticks vs native is the next oracle
   move.

## Level-build RNG chain verified (2026-06-13)

`build_subgame_level` draws the music pick from the global stream BEFORE
the track rebuild, but `populate_runtime_track_cells_from_segments`
re-seeds with `runtime_build_seed` at its top and
`place_parcels_on_track` runs immediately after the cell build inside
`rebuild_track_runtime_from_segments` — so the port's
seed -> build draws -> `runtime_build_final_random_state` -> parcels
chain is structurally faithful; music/backdrop draws cannot shift it.
With the parcel-pool ordered-compaction fix (ef5a3fab) the placement
stream should now be draw-for-draw native. The remaining
rebuild stages (edge variants, fringe promotion, tile-run merge,
warning zones, fringe objects) run AFTER parcels and any draws they
make land before gameplay — audit those when their scratches land.

## Oracle t=253 frontier DECODED (2026-06-13, postal[0] instrumentation)

The divergence is the **row-54 wall-14 stall**: native's ghost stops dead
at z = 53.500 (t=243-244, the trunc(z+0.49)-0.5 snap) and resumes from
the window floor (~rate*0.17 = 0.082, rate ≈ 0.48), while the port sails
through. Two layered causes:

1. ~~The port's wall probe sampled the cell under the rider~~ FIXED
   06-13 (27c115cf): native probes (x, y, z + 0.49) — a next-row
   lookahead at the live x.
2. REFINED 06-13 (second instrumentation pass): the causal chain runs
   through the t=144 ATTACHMENT EXIT — the port's natural-exit handoff
   places it **+0.27 z AHEAD of native** (dz steps 0.116 -> 0.383 at the
   mode flip; the v3 exhaust model `anchor + terminal_sample.z +
   width_or_scale + step` carries a residual). Being ahead on the same
   recorded lateral, the port then clips a garbage object native misses
   (one-tick -0.0096 vz at t≈152, `garbage_hit`), runs ~5% slow from
   there, native's faster cruise crosses it at t≈194, and the
   accumulated lag makes the port reach the row-54 wall ~2 ticks after
   the lateral leaves the wall lane. ROOT FIX: audit the exit z
   placement in `native/attachment_follow.zig` against the pinned
   terminal-segment asm (is `step` double-counted? is the terminal
   sample one spacing off?). The subgame rate itself VERIFIES CLEAN
   (port 0.481 vs native back-solved 0.479-0.482), and the t≈208 rise
   is the slide-tile quantum on both sides.
   (superseded analysis kept below)
   **the port cruises ~5% slow** —
   pvz ≈ 0.2085 vs native dz/tick ≈ 0.2197 through t=200-242, an
   accumulated ~0.44 z-lag, so the port reaches the wall ~2 ticks late,
   after the recorded lateral leaves the wall lane (x crosses from the
   wall column into lane 1 at t≈244). Suspects, now measurable: the
   subgame rate (native back-solves to ≈0.48 from the stall-exit floor;
   compare the port's rate at z≈53.6 — progress_frac/runtime_row_count
   parity), or the ring-boost magnitude/timing (both sides show a boost
   near t≈208 with different sizes). Next probe: print the port's
   subgame_rate and boost events alongside the back-solved native rate.

## OPEN: z-axis row-convention audit (found 2026-06-13, v6)

`row_position` is a HALF-SHIFTED z (world z = row_position + 0.5 via
worldPositionForLane) while native has only world z — the z-axis twin of
the lane-convention audit. The natural-exit import is fixed (7933dbea),
but other world-z producers/consumers mix spaces: the barrier-hold snap
applies trunc(z+0.49)-0.5 in row_position space (native formula is world
space — off by ~0.5 in half the fraction range), the launch branch of
worldPosition returns z = row_position WITHOUT +0.5, and any
`row_position = <world z>` assignment needs the -0.5. Audit all
assignments/conversions by space, like the lane audit.

## OPEN: attachment-phase z advance runs ~0.3% slow (refined 2026-06-13 v7)

NOT an entry-seed offset: the gap GROWS ~0.0007-0.0009/tick through the
whole start-ramp ride (0.109 by t=134). The recorded scalar reads
correctly (0.47), the progress seed formula is algebraically native
(row_position - row == world_z - anchor_z with the +0.5 anchor), and the
port's vz rides its window cap exactly. Native's ghost z advances at
~vz * k with k ≈ 1.003-1.004 — the START template's OUTPUT z mapping is
scaled: native's authored sample z spacing is not exactly 1.0 per
segment while the port's built template maps progress to z 1:1. NEXT:
diff the START ramp template's per-sample z offsets in the native
constructor (the initialize_*_path_template_pair family) against
attachment_builders' generated samples; the 0.3% should fall out of the
authored offsets. Consequences while open: a marginal garbage clip at
t~153 that native misses (one-tick -4% vz) and the hidden row-54 wall
stall (the t=254 ratchet).

## RESOLVED 06-13 (50967917): digit tiles on attachment rows

Native `populate_runtime_track_cells_from_segments` maps parcel digit
glyphs ('0'-'9') to tile 0x0f (slide family) ONLY on rows without
attachment owner flags; on rows already carrying 0x40/0x80 (set by the
'P'/'p' install walk earlier in the same pass) the digit cell becomes
tile 0 (void, no bod). The port's
`runtimeTileTransitionForNormalizedGlyph` maps digits to 0x0f
unconditionally — so on attachment spans the port has slide tiles where
native has void, granting the slide double-quantum z acceleration and a
solid floor that native doesn't have. Candidate for the oracle's t=253
frontier (the divergence sits just past an attachment exit). Fix needs
attachment-span knowledge in/after the tile pass (the scaffold collects
FROM tiles, so either a span pre-pass from 'P'/'p' rows + template row
counts, or a post-scaffold re-zero before the derived grids build).
Full glyph/anchor ground truth:
tools/match/scratches/populate_runtime_track_cells_from_segments/NOTES.md.

## Next actions (keep this list short and current)

1. ~~Route the follow update~~ DONE 06-12: `stepAttachmentFollowAtRate` now
   calls the mirror's `updateTrackAttachmentFollowState` (stepping, exhaust
   step, launch lanes, side-exit gate, vertical clamp); the invented stepping
   loop and `shouldSideExit` predicate are deleted; `endAttachmentIfNeeded`
   switches on the returned mode. Follow-up seams to close: the milestone row
   writes, voice 15 on supertramp launch, and the motion.y vertical lane
   (checklist Phase 3 motion slice). side_exit_mode RESOLVED 06-12: all 29
   native template constructors write +0x40 = 0, so every template allows
   side exits — the blocked branch is dead configuration.
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

## Grid-alignment audit (OPEN, found 2026-06-13)

The lockstep oracle's t≈204 frontier exposed a foundational convention
split. Native `get_track_grid_cell_at_world_position` maps
`column = trunc(x + 4)` on the fixed 8-lane gameplay grid (x in [-4, 4),
cell i spans [i, i+1) — in authored lane-center space that is
`floor(lane_center)`, with the 8 native columns = authored columns 1..8
when the authored width is 10). The port maps `floor(lane_center - 0.5)`
(spans [i+0.5, i+1.5)) — every off-center position in the lower half of
a lane samples the neighboring column. The recorded replay rides
off-center constantly, so the port reads void/wall cells (and falls to
its death) where native cruises on solid track.

RESOLVED in part (2026-06-13 v5): the regression hypothesis was wrong —
track_render draws column j spanning [j - w/2, j + 1 - w/2), so CONTENT
placement already matches the containing-cell convention; the earlier
blanket fix regressed through the nearest-lane STEERING consumers, which
legitimately keep the -0.5 shift. The roles are now split:
`gridColumnAtWorldX` (track.zig, the column half of native
get_track_grid_cell_at_world_position) + the runner's `gridLaneIndex`
(sampling at the LIVE world x like native — no cached lane state) serve
cell-content queries; `laneIndexForLaneCenter`/`laneIndexAtWorldX` stay
steering-only. Converted so far: the boost-tile gate and
stepActivePhaseVerticalMotion's tile fetch — oracle first_div 212 -> 253.
REMAINING: convert the rest of the cell-content consumers off
resolved_lane_index (collision probes, salt retire, row events, entry
floor sampling — audit the ~28 laneIndex* call sites + 63
resolved_lane_index uses by role), and re-check the
"world quantization" test's -3.99 -> 0 expectation (encodes the steering
shift, not the native containing-cell asm).

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

## Lockstep replay oracle (LIVE 2026-06-12)

Real Windows replays landed (tests/fixtures/replays, 25 records / 71,535
samples) and `zig/src/replay_oracle.zig` now drives a headless Runner with
the recorded lateral/flags lanes and compares the port's z trajectory
against the recording's ghost-z lane per tick — the crimson differential
pattern. Landing them immediately caught the score-bank xor mask bug
(ledger 06-12).

**Baseline (postal[0], ARCADE012, 5006 ticks):** the port survives the
full replay. The test pins the numbers as a RATCHET — tighten as motion
models collapse, never loosen.

- v1 (06-12): first divergence >1.0 units at tick 28; worst drift ~917.
- v2 (06-12): first divergence at tick 144; the start ramp tracks native
  to ~0.001/tick.
- v3 (06-12): first divergence at tick 195 — the attachment natural-exit
  +1.7 z teleport removed. The pinned boss asm shows the output position
  EXTENDS along delta_dir_to_next across the terminal segment (the port's
  pose clamped at the terminal sample, and the exit commit then jumped
  past the tail); the exhaust placement is anchor + terminal_sample.z +
  width_or_scale + step (width_or_scale = 1.0 everywhere except WORM's
  4.0 — the port's exit_tail_extra now mirrors both). Named follow-ups:
  ~~the exit-pending damping event around t=205~~ (RESOLVED in v4), and
  the follow OUTPUT rotation is identity across the terminal segment
  (set_matrix_identity at segment == count-1) — geometry consumers keep
  the sample basis, the identity lane lands with the cluster-1 output
  routing.
- v4 (06-12): first divergence at tick 212 — exit-pending no longer arms
  at natural ends. Native arms it ONLY via the four event-gated
  begin_post_follow_carryover arms (void-edge tile 0/35 window, fall
  below y=0, the wall-14 stall timer); the port's unconditional exit
  handoff armed it on every exit, so the (1-rate*0.2) damping + gravity
  sent the runner off a cliff the recorded native run cruised over.
  Also: a past-the-end re-begin guard (native's begin gate is the 29/30
  entry tile, absent past the span) and natural exits preserve the live
  x (the exhaust writes z only). Next frontier: the cruise boost cadence
  — native holds ~0.23 where the port drags toward the floor between
  boosts (tile-boost cadence trace needed). Named residual: the output-x
  model carries the terminal sample's center_x where native's
  v85-relative local-x preservation re-centers (cluster-1 output
  routing). Fixes: the 9-tick startup control-override hold (pinned
  by all 24 recordings; `update_subgoldy` IDA 275-285), the forward window
  clamp made mode-independent and gated at `completion_row_start` (IDA
  644-658 — the old port clamped only in track mode, so attachment riders
  including the START ramp integrated velocity from zero), clamp moved
  before position integration, and the negative-knockback clamp skip
  (override episodes). Worst drift ~916 persists from the steady-state
  cruise model — native's velocity oscillates 0.24-0.31 via tile boosts vs
  drag while the port decays to the window floor between boosts. That
  equilibrium (cluster-2 motion core: per-tile boost cadence + drag) is
  the next oracle target.

The recordings also decoded the native rate model
(`calc_subgame_rate` @ 0x4404d0, fully mirrored in
`updateNativeTrackCenterRate`): `rate = base + progress_frac × mode_gain`
(0.55 modes 1/3, 0.4 + 0.2 flat mode 4, 0.2 default) plus the
damage-drain sine envelope and a powerup half-add lane.
