# Gameplay Matching Todo

Created: 2026-06-13

Goal: match or pin every gameplay-simulation function that can overturn port
semantics, then mirror/route/collapse the old Zig model. This is not a byte
golf scoreboard: a lower honest match with documented residuals is better than
a fake 100%.

## Rules

- Use the fixed project toolchain: `msvc6.5 /O2 /G5 /W3`.
- Do not use inline asm, naked functions, dummy externs, or constants whose
  only purpose is normalizer masking.
- Do not change compiler flags to chase a function unless there is independent
  Rich/header evidence for a different object family.
- Keep source plausible as original 2004 C++: real structs, real control flow,
  real helper calls, and native offset names.
- Record every residual in `tools/match/scratches/<function>/NOTES.md`.
- A function is good enough to port when semantics are unambiguous, even if the
  remaining diff is register allocation, x87 scheduling, or duplicated epilogue
  shape. Mark that as pinned instead of contorting the source.

## Priority Queue

### P0 - Current Oracle Frontier

These directly affect the postal replay lockstep frontier around the t~153
garbage/projectile divergence.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `update_garbage_hazard` | `0x43f200` | 66.96%, source-shaped | Owns garbage active/burst states, smoke cadence, nuke reaction, and the final live body position that collision/projectile probes sample. | Continue source-shaping around the remaining `0x1c` frame gap, burst x87 staging slots, and case-1 vector-copy register order; semantics are documented in NOTES. |
| `destroy_garbage_hazard` | `0x43f130` | 100% | Confirms live-list teardown and whether any collision-side or sprite state survives after hit. | Done; use as the exact kill/unlink reference for `update_garbage_hazard`. |
| `spawn_track_garbage_hazard` | `0x43da80` | 91.87%, source-shaped | Seeds garbage scale, sprite variant, projected body position, active list link, and slot owner. Recent port fix depends on this path. | Pool scan, setup, and staged x/z load order now match native shape; remaining gap is projection x87/register order. |
| `append_subgame_contact_target` | `0x415ef0` | 100% | Called by garbage and slug AI; exact match confirms it appends `{kind, position, radius, object}` to a per-frame registry, not a bob mutator. | Done; use as the exact contact-target registry helper for garbage and slug AI. |
| `update_golb_ai` | `0x414820` | 21.39%, structure complete | Projectile flight, path entry, homing, trails, slug/garbage hit gates, wall impact. | Path-follow switch block order now matches native layout; finish staging-local shape and duplicated returns while keeping NOTES semantics authoritative. |
| `calc_path_length_z` | `0x4217b0` | 32.17%, structure complete | Golb path-follow riding; sibling of `update_track_attachment_follow_state`. | Continue source-shaping around overflow block placement, terminal staging, and matrix-copy locals; semantics are documented in NOTES. |
| `create_golb` | `0x415280` | 27.21%, structure complete | Seeds projectile kind, velocity/spread, homing target, and RNG stream consumers. | Continue source-shaping around movement-flag branch sharing, vector staging, and kind-specific setup locals; semantics are documented in NOTES. |

### P1 - Player Motion And Attachment Exit

These govern the broadest wrong-assumption surface in `update_subgoldy`.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `update_subgoldy` | `0x43b120` | 72.30%, structure complete | Master player motion, replay codec, fire lane, completion handoff, attachment-exit clears. | Continue slice-first: grounded/trampoline clear lanes, projectile/replay consumers, then residual register-shape cleanup. |
| `play_movement_state_sound` | `0x43afd0` | 89.13% | Shared RNG draw and fire/movement sound variant cadence. | Finish register/branch residuals; preserve the variant-draw semantics already routed. |
| `begin_track_attachment_follow_state` | `0x420c40` | 94.55% | Direct attachment begin seed. | Finish only if source shape is clear; otherwise keep pinned. |
| `try_enter_track_attachment_from_swept_motion` | `0x42c770` | 79.80%, pinned | Swept re-entry gates and player y/lateral seed. | Finish dual-slot source-shape lead in NOTES; do not disturb pinned semantics. |
| `update_track_attachment_follow_state` | `0x420cb0` | 46.44%, semantics pinned | Attachment stepping, natural end, side exit, supertramp launch. | Golf only with source-plausible staging; do not regress routed mirror semantics. |
| `project_position_onto_track_attachment` | `0x4444b0` | 56.00% | Shared projection for garbage/slug/parcel and attachment-row actors. | Match helper after garbage spawn confirms all call-side expectations. |

### P2 - Collision And Runtime Pools

These should turn current verified port behavior into matched proof.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `handle_subgoldy_collisions` | `0x444cf0` | 44.58%, structure complete | Contact gates for salt, sub-lazer, garbage, slug, rings, health, jetpack, parcel. | Proof-polish: local staging, mask register reuse, per-loop delta/probe shape. |
| `wall2_emitter_maybe_fire_sub_lazer` | `0x439d50` | 40.43% | Wall2 fire cadence and 4% RNG gate. | RNG tags are documented; continue cadence locals and emitter-origin call shape. |
| `spawn_sub_lazer_projectile` | `0x441670` | 98.41% | SubLazer body/sprite spawn and y stagger. | Finish small residual if source remains plausible; otherwise pin. |
| `update_sub_lazer_projectile` | `0x43efb0` | 41.73% | SubLazer body flight, nested sprite bob, teardown. | Use recovered slot layout; separate body position from visual bob. |
| `shoot_subgoldy` | `0x441ad0` | 49.46% | Weapon/sub-lazer spawn callsite and audio cue. | Match after sub-lazer pool helpers stabilize. |
| `spawn_salt_hazard` | `0x441560` | 74.07% | Salt slot layout, velocity byte-poke bug, yaw RNG. | Finish source shape if possible; keep OB notes explicit. |
| `update_salt_hazard` | `0x4417d0` | 48.04% | Salt integrate/removal state. | Focus on state switch and list teardown shape. |
| `deactivate_salt_hazard` | `0x441740` | 41.46% | Salt collision/removal edge. | Match with the same list helper style as `destroy_garbage_hazard`. |

### P3 - Damage, Warning, Camera, And Presentation Control

These are medium blast-radius systems already partly understood.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `apply_damage_gauge_delta` | `0x4413f0` | 58.20%, pinned finding | Hit-flash gate, damage/recovery clamp, side effects. | Finish after warning/update damage owner fields settle. |
| `update_damage_gauge` | `0x440fd0` | 65.92%, structure-first | Drain, state transitions, warning interaction. | Continue source-shaping around state block placement and x87/local scheduling; semantics are documented in NOTES. |
| `update_warning` | `0x446f80` | 57.69% | Warning actor loop, stop sample handle, global gates. | Align state/timer locals and handle-release semantics. |
| `update_cameraman` | `0x4461d0` | 92.55%, pinned | Camera matrix blend and attachment-exit roll. | Treat as pinned unless exact register allocation becomes obvious. |
| `initialize_cameraman` | `0x446160` | 100% | Camera init baseline. | Done; keep as dependency. |
| `initialize_snail_skin` / `update_snail_skin_transition` / `change_snail_skin` | `0x445f60` / `0x445f80` / `0x445fd0` | 100% | Skin state is matched; renderer consumer still missing. | No matching work unless renderer callsites demand more. |

### P4 - Track Build, Row Events, And Outer Bridge

These are large but important once the immediate lockstep frontier moves.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `place_parcels_on_track` | `0x4438e0` | 23.40%, structure-first | Parcel RNG stream, placement banks, attachment-row projection. | Continue bank layout and ordered-compaction shape. |
| `populate_runtime_track_cells_from_segments` | `0x435eb0` | NOTES only | Runtime glyph normalization, digit-on-attachment voiding, row ownership. | Promote scratch/status entry if not already manifest-backed. |
| `mark_track_warning_zones` | `0x4354f0` | 32.51% | Warning footprint and hazard suppression. | Match after runtime grid roles settle. |
| `build_track_fringe_objects` | `0x434be0` | no scratch | Allocates directional fringe objects after runtime-cell build; useful for separating renderer-only edge data from gameplay grid state. | Defer until runtime grid and warning footprints are pinned. |
| `switch_track_mirror` | `0x435e60` | 91.23% | Runtime mirror state and builder row convention. | Finish if simple; otherwise pin. |
| `update_row_event_display` | `0x404cf0` | 85.06% | Parcel home anchor, row-event widget, prompt ownership. | Finish state-machine source shape; likely high leverage for parcel collapse. |
| `complete_subgame` | `0x438700` | 59.89%, structure-first | Completion bridge producer. | Continue source-shaping around result-record store order and high-score dispatch register allocation; semantics are documented in NOTES. |
| `update_subgame` | `0x438b90` | no scratch | Outer gameplay state machine, active row scan, bridge opcodes. | Defer until lower-level runtime functions are trustworthy. |
| `update_frontend_state_machine` | `0x4107d0` | no scratch | Frontend/subgame bridge and return owners. | Defer; match as bridge cluster with `update_subgame`. |

### P5 - Math Helpers That Block Cleaner Mirrors

These are not gameplay owners, but several mirrors depend on them.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `interpolate_matrix_rotation` | `0x44d920` | 71.89% | Native rotation interpolation for attachments/camera. | Improve only with plausible x87/source staging. |
| `linear_interpolate_matrix` | `0x44da90` | 49.57% | Matrix-space interpolation; already invalidated old pose lerp. | Match enough to confirm normalization/orthogonalization call shape. |

## Already Matched Or Pinned Dependencies

- Exact helpers to keep using as anchors: `search_path_for_golb`,
  `initialize_path_follow_golb`, `begin_post_follow_carryover`,
  `get_track_grid_cell_at_world_position`, `sample_track_floor_height_at_position`,
  `initialize_subgoldy_ghost`, `update_track_jetpack_pickup`,
  `destroy_garbage_hazard`, `append_subgame_contact_target`, voice helpers,
  and the small runtime initializer family in `tools/match/STATUS.md`.
- Pinned-enough functions should not be churned for percentage alone:
  `update_cameraman`, `begin_track_attachment_follow_state`,
  `try_enter_track_attachment_from_swept_motion`,
  `spawn_sub_lazer_projectile`, and any scratch whose NOTES identify only
  register-allocation or x87 scheduling residuals.

## Operating Plan

1. Work top-down from P0 unless a new oracle trace moves the frontier.
2. For each function: create/update scratch, run `tools/match/match.sh`,
   document residuals, then refresh `tools/match/STATUS.md`.
3. After a function is exact or pinned, mirror it into the relevant
   `zig/src/gameplay/native/<cluster>.zig` module before adding more logic to
   `gameplay.zig`.
4. Route one caller slice at a time and add a regression test or replay-oracle
   ratchet before deleting the old scaffold path.
5. Commit each coherent match/mirror/route/collapse step with a conventional
   commit message.
