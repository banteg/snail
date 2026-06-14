# Gameplay Matching Todo

Created: 2026-06-13

Goal: build broad, trustworthy gameplay coverage by matching exact small and
medium functions, pinning large functions once their semantics and residuals
are clear, then using those recovered C islands to mirror/route/collapse the
old Zig model. This is not a byte golf scoreboard: a lower honest match with
documented residuals is better than a fake 100%, and broad semantic coverage
beats chasing perfection on one large function.

## Rules

- Use the fixed project toolchain: `msvc6.5 /O2 /G5 /W3`.
- Do not use inline asm, naked functions, dummy externs, or constants whose
  only purpose is normalizer masking.
- Do not change compiler flags to chase a function unless there is independent
  Rich/header evidence for a different object family.
- Keep source plausible as original 2004 C++: real structs, real control flow,
  real helper calls, and native offset names.
- Keep `GAME_PTR`/`GAME_INT`-style direct offset access as scratch-only
  discovery glue. Promote stable recovered C through typed fields, shared
  headers, or generated accessors only after multiple scratches agree.
- Record every residual in `tools/match/scratches/<function>/NOTES.md`.
- A function is good enough to port when semantics are unambiguous, even if the
  remaining diff is register allocation, x87 scheduling, or duplicated epilogue
  shape. Mark that as pinned instead of contorting the source.

## Breadth Policy

- Prefer exact or near-exact small/medium helpers over prolonged large-function
  byte golf when both improve gameplay assurance.
- For large structure-complete functions, stop once the gameplay semantics,
  data owners, helper calls, and remaining residual classes are documented.
- Return to a large pinned function only with a specific lead: new oracle
  divergence, source-idiom evidence, shared-type consolidation, or localized
  diff evidence that can improve it without fakematching.
- Each pass should broaden the trusted map by adding an exact helper, pinning a
  function, improving a high-leverage scratch, or making the TODO/STATUS state
  more actionable.

## Priority Queue

### P0 - Current Oracle Frontier

These directly affect the postal replay lockstep frontier around the t~153
garbage/projectile divergence.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `update_garbage_hazard` | `0x43f200` | 80.00%, pinned | Owns garbage active/burst states, smoke cadence, nuke reaction, and the final live body position that collision/projectile probes sample. | Semantics and target extent are pinned; remaining frame, jump-table epilogue, random velocity stack-slot, side-bias compare/reload, and vector-copy register residuals are documented in NOTES. |
| `destroy_garbage_hazard` | `0x43f130` | 100% | Confirms live-list teardown and whether any collision-side or sprite state survives after hit. | Done; use as the exact kill/unlink reference for `update_garbage_hazard`. |
| `spawn_track_garbage_hazard` | `0x43da80` | 92.58%, pinned | Seeds garbage scale, sprite variant, projected body position, active list link, and slot owner. Recent port fix depends on this path. | Semantics are pinned; remaining projection x87/register residual and rejected variants are documented in NOTES. |
| `append_subgame_contact_target` | `0x415ef0` | 100% | Called by garbage and slug AI; exact match confirms it appends `{kind, position, radius, object}` to a per-frame registry, not a bob mutator. | Done; use as the exact contact-target registry helper for garbage and slug AI. |
| `update_golb_ai` | `0x414820` | 49.63%, structure complete | Projectile flight, path entry, homing, trails, slug/garbage hit gates, wall impact. | Treat as a pinned semantic map for breadth-first work unless a specific localized lead appears. Live-state gate, path-follow output copies, non-follow position pointer staging, kind-0 gravity ordering, direction delta locals, horizontal slug-deflection normalization, slug kind compare order, homing pull/keep `Vec3` temporaries, homing current-position pointer use, homing target-delta/result stack staging, slug reflected-velocity staging, typed transform copy/member calls, and trail dispatch now better match native; remaining residuals are homing y/z velocity-owner operands, path-output stack staging, collision probe scheduling, and duplicated returns documented in NOTES. |
| `calc_path_length_z` | `0x4217b0` | 40.58%, structure complete | Golb path-follow riding; sibling of `update_track_attachment_follow_state`. | Scalar/base declaration-order trials are exhausted; continue only with stronger evidence around overflow block placement, matrix-copy layout, and terminal/side-exit shot-position ownership documented in NOTES. |
| `create_golb` | `0x415280` | 28.63%, structure complete | Seeds projectile kind, velocity/spread, homing target, and RNG stream consumers. | Pointer lifetimes, movement-flag reloads, previous-output whole-copy, and the shared `(flags & 5)` movement-source label now better match native setup; continue around remaining movement-flag branch sharing, direction copy staging, and kind-specific setup locals documented in NOTES. |

### P1 - Player Motion And Attachment Exit

These govern the broadest wrong-assumption surface in `update_subgoldy`.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `update_subgoldy` | `0x43b120` | 72.44%, structure complete | Master player motion, replay codec, fire lane, completion handoff, attachment-exit clears. | Continue slice-first: grounded/trampoline clear lanes, projectile/replay consumers, then residual register-shape cleanup. |
| `advance_timer_counters` | `0x441b90` | 100% | Exact shared stopwatch accumulator used by `update_subgame` and `update_subgoldy` for elapsed seconds, frame rollover, and display hundredths/thousandths. | Done; use with exact `zero_timer_counters` as the timer-record source of truth. |
| `format_time_trial_string` | `0x448960` | 95.89%, pinned | Shared Time Trial HUD formatter for `initialize_subgame`, `update_subgame`, and challenge setup route records. | Semantics are pinned against exact `TimerCounters`; remaining residual is cdecl stack-cleanup coalescing across adjacent `sprintf` calls, documented in NOTES. |
| `initialize_subgoldy_death` | `0x446e30` | 100% | Exact selector for respawn versus final-loss entry by gameplay mode and visible life stock. | Done; use with exact `initialize_subgoldy_resurrect` and `update_subgoldy_resurrect` as the death/resurrection source of truth. |
| `update_subgoldy_resurrect` | `0x441fd0` | 100% | Exact death/resurrection bridge: freezes z velocity, drives fade-out, spends arcade life stock, calls `complete_subgame(1)` on final loss, and routes frontend state. | Done; use with exact `initialize_subgoldy_resurrect` as the respawn/final-loss source of truth. |
| `play_movement_state_sound` | `0x43afd0` | 89.13%, pinned | Shared RNG draw and fire/movement sound variant cadence. | Semantics are pinned; remaining clamp-tail duplication is documented in NOTES. |
| `begin_track_attachment_follow_state` | `0x420c40` | 94.55%, pinned | Direct attachment begin seed. | Semantics and offsets are pinned; remaining table-base folding residual is documented in NOTES. |
| `try_enter_track_attachment_from_swept_motion` | `0x42c770` | 79.80%, pinned | Swept re-entry gates and player y/lateral seed. | Finish dual-slot source-shape lead in NOTES; do not disturb pinned semantics. |
| `update_track_attachment_follow_state` | `0x420cb0` | 46.44%, semantics pinned | Attachment stepping, natural end, side exit, supertramp launch. | Golf only with source-plausible staging; do not regress routed mirror semantics. |
| `project_position_onto_track_attachment` | `0x4444b0` | 81.16%, source-shaped | Shared projection for garbage/slug/parcel and attachment-row actors. | Kind-42 helper now source-shaped as a `PathTemplate` member call from callsite evidence; continue only around branch-label/local-transform offsets and non-kind42 stack-slot/register residuals documented in NOTES. |

### P2 - Collision And Runtime Pools

These should turn current verified port behavior into matched proof.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `handle_subgoldy_collisions` | `0x444cf0` | 45.15%, structure complete | Contact gates for salt, sub-lazer, garbage, slug, rings, health, jetpack, parcel. | Proof-polish: local staging, mask register reuse, per-loop delta/probe shape. |
| `add_subgoldy_score` | `0x4402c0` | 80.62%, source-shaped | Shared score award helper for collisions, hazards, row-event parcels, bonus payouts, life thresholds, and score sound gating. | Semantics and arithmetic prefix are pinned; remaining residual is saved-register epilogue scheduling at the final sound gate, documented with `gated-tail-member-*` idiom probes in NOTES. |
| `uninit_nuke` | `0x4470e0` | 100% | Exact teardown for the 25-sprite ring/special-effect controller armed by ring and special-effect collisions. | Done; use as the lifecycle anchor before matching `initialize_nuke` and `update_nuke`. |
| `initialize_nuke` | `0x447110` | 93.75%, source-shaped | Initializes the 25-sprite ring/special-effect controller, seeds orbit phase/rate state, and immediately dispatches the first update. | Semantics and layout are pinned; remaining residual is flag-temp register choice plus neighboring scale-constant scheduling documented in NOTES. |
| `wall2_emitter_maybe_fire_sub_lazer` | `0x439d50` | 40.43%, pinned | Wall2 fire cadence and 4% RNG gate. | Semantics are pinned; RNG tags, emitter cadence, and source-shape residuals are documented in NOTES. |
| `spawn_sub_lazer_projectile` | `0x441670` | 98.41%, pinned | SubLazer body/sprite spawn and y stagger. | Semantics and instruction count are pinned; remaining residual is store scheduling around velocity z versus bob phase, documented in NOTES. |
| `update_sub_lazer_projectile` | `0x43efb0` | 41.73%, pinned | SubLazer body flight, nested sprite bob, teardown. | Semantics are pinned; body-motion ownership and register/layout residuals are documented in NOTES. |
| `shoot_subgoldy` | `0x441ad0` | 49.46%, pinned | Weapon/sub-lazer spawn callsite and audio cue. | Semantics are pinned; free-scan loop residual and unstaggered audio origin are documented in NOTES. |
| `explode_slug_hazard` | `0x43f680` | 73.22%, structure-first | Slug death particle burst spawned by the exact `kill_slug_hazard` helper. | Semantics are mapped; remaining frame/register/x87 scheduling residuals are documented in NOTES. |
| `spawn_salt_hazard` | `0x441560` | 74.07%, pinned | Salt slot layout, velocity byte-poke bug, yaw RNG. | Semantics are pinned; free-scan layout residual and velocity.z byte-poke finding are documented in NOTES. |
| `update_salt_hazard` | `0x4417d0` | 48.04%, pinned | Salt integrate/removal state. | Semantics are pinned; overlapping progress fields, velocity-z byte-poke fallout, and probe residuals are documented in NOTES. |
| `deactivate_salt_hazard` | `0x441740` | 41.46%, pinned | Salt collision/removal edge. | Semantics are pinned; duplicated error-block and register residuals are documented in NOTES. |

### P3 - Damage, Warning, Camera, And Presentation Control

These are medium blast-radius systems already partly understood.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `apply_damage_gauge_delta` | `0x4413f0` | 58.20%, pinned | Hit-flash gate, damage/recovery clamp, side effects. | Semantics are pinned; corrected voice-failure animation nesting and residuals are documented in NOTES. |
| `update_damage_gauge` | `0x440fd0` | 80.60%, source-shaped | Drain, state transitions, warning interaction. | State block placement and warning call ownership now match native shape; remaining residual is x87/local scheduling documented in NOTES. |
| `update_warning` | `0x446f80` | 57.69%, pinned | Warning actor loop, stop sample handle, global gates. | Semantics are pinned; overlay alpha state machine and residuals are documented in NOTES. |
| `update_cameraman` | `0x4461d0` | 92.55%, pinned | Camera matrix blend and attachment-exit roll. | Treat as pinned unless exact register allocation becomes obvious. |
| `initialize_cameraman` | `0x446160` | 100% | Camera init baseline. | Done; keep as dependency. |
| `initialize_snail_skin` / `update_snail_skin_transition` / `change_snail_skin` | `0x445f60` / `0x445f80` / `0x445fd0` | 100% | Skin state is matched; renderer consumer still missing. | No matching work unless renderer callsites demand more. |

### P4 - Track Build, Row Events, And Outer Bridge

These are large but important once the immediate lockstep frontier moves.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `place_parcels_on_track` | `0x4438e0` | 23.40%, structure-first | Parcel RNG stream, placement banks, attachment-row projection. | Continue bank layout and ordered-compaction shape. |
| `initialize_parcel_set_bucket_pool` | `0x443870` | 100% | Exact positive-count parcel bucket reset before authored parcel placement. | Done; use as the `place_parcels_on_track` bucket stride/count anchor. |
| `initialize_zero_parcel_bucket_pool` | `0x4438b0` | 100% | Exact zero-parcel fallback bucket reset before filler placement. | Done; use with the positive bucket initializer to separate authored parcel requests from zero-fill rows. |
| `allocate_track_parcel_slot` | `0x443190` | 100% | Exact free-slot scan for the 50-entry parcel runtime pool. | Done; use as the allocation anchor for `spawn_track_parcel`, row-event delivery parcels, and parcel-placement pool assumptions. |
| `spawn_track_parcel` | `0x443730` | 100% | Exact runtime parcel spawn helper: allocates a parcel slot, copies world position, assigns score owner/sprite, and seeds row-based bob phase. | Done; use with the exact allocator and bucket initializers before expanding `place_parcels_on_track` or parcel collision/delivery slices. |
| `rebuild_track_runtime_from_segments` | `0x437de0` | 100% | Exact bridge ordering for runtime cell population, parcel placement, tile variant passes, warnings, fringe build, and render-cache refresh. | Done; use as the call-order anchor before expanding `populate_runtime_track_cells_from_segments` or `build_track_fringe_objects`. |
| `build_track_colours` | `0x435d40` | 100% | Initializes every global track colour bank before runtime cell population. | Done; keep the byte-offset loop and duplicate J/K bank calls as the exact source shape. |
| `set_subgame_features` | `0x435df0` | 100% | Exact selected-level override and per-mode runtime flag presets before track population. | Done; use as the runtime-flag source of truth for HUD, barrier, tutorial, and track-generation gates. |
| `populate_runtime_track_cells_from_segments` | `0x435eb0` | 7.13%, structure-first | Runtime glyph normalization, digit-on-attachment voiding, row ownership. | Scratch now covers setup, row-count seeding, clear pass, and visited reset; expand next through row-selection/row-flag copy before tackling the glyph switch. |
| `mark_track_warning_zones` | `0x4354f0` | 32.51%, pinned | Warning footprint and hazard suppression. | Semantics are pinned; tile seed set, 6x2 footprint, bounds, and register-layout residuals are documented in NOTES. |
| `build_track_fringe_objects` | `0x434be0` | 49.44%, structure-first | Allocates directional fringe objects after runtime-cell build; useful for separating renderer-only edge data from gameplay grid state. | Register/local ownership is the next blocker: native keeps game in `ebp`, family in `edi`, edge-a in `ebx`, then reuses/restores `ebp` for edge-b; residual bool probes and skirt-color copy scheduling are documented in NOTES. |
| `allocate_fringe_object` | `0x4470a0` | 100% | Exact allocator for the 7000-entry fringe-object pool used by `build_track_fringe_objects`. | Done; use as the pool cursor/overflow anchor for fringe build and renderer assumptions. |
| `switch_track_mirror` | `0x435e60` | 91.23%, pinned | Runtime mirror state and builder row convention. | Semantics are pinned; remaining duplicate-tail layout residual is documented in NOTES. |
| `update_row_event_display` | `0x404cf0` | 99.53%, pinned | Parcel home anchor, row-event widget, prompt ownership. | Semantics are pinned; the only accepted residual is bonus sound thiscall setup order, documented in NOTES. |
| `register_parcel_delivery` | `0x405040` | 100% | Exact parcel-delivery score/audio/state handoff into the row-event display. | Done; use as the delivery-side anchor for parcel collision and row-event state transitions. |
| `flush_row_event_display` | `0x404830` | 89.39%, source-shaped | Forces pending row-event parcel payouts and tears down widgets during completion/destruction. | Semantics are pinned; remaining residual is the post-bonus count increment spelling documented in NOTES. |
| `complete_subgame` | `0x438700` | 75.28%, pinned | Completion bridge producer. | Semantics are covered; remaining direct-memory byte-OR and result-snapshot register scheduling residuals are documented in NOTES. Do not force them with volatile, raw offset macros, or fake aliasing. |
| `get_track_skirt_color` | `0x442120` | 100% | Shared skirt RGBA producer for fringe/render-cache paths. | Done; keep the direct aggregate assignment from `set_color_rgba`, which is the source idiom that preserves native copy scheduling. |
| `update_subgame` | `0x438b90` | no scratch | Outer gameplay state machine, active row scan, bridge opcodes. | Defer until lower-level runtime functions are trustworthy. |
| `update_frontend_state_machine` | `0x4107d0` | 58.12%, structure-first | Frontend/subgame bridge and return owners. | Block-local game owners now recover the native `lea ecx, [base+offset]` call shape for most dispatch bodies; continue only around register allocation, shared-exit label distance, and jump-table/data extent residuals documented in NOTES. |

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
  `update_subgoldy_resurrect`,
  `destroy_garbage_hazard`, `hit_slug_hazard`, `kill_slug_hazard`,
  `append_subgame_contact_target`, `initialize_array_with_constructor`,
  `spawn_track_parcel`,
  voice helpers,
  and the small runtime initializer family in `tools/match/STATUS.md`.
- Pinned-enough functions should not be churned for percentage alone:
  `update_cameraman`, `begin_track_attachment_follow_state`,
  `try_enter_track_attachment_from_swept_motion`,
  `spawn_sub_lazer_projectile`, `update_row_event_display`, and any scratch
  whose NOTES identify only register-allocation or x87 scheduling residuals.

## Operating Plan

1. Work breadth-first within the priority queue: prefer the next important
   function whose semantics can be matched, pinned, or usefully improved without
   sinking into large-function perfection.
2. Use large structure-complete scratches as semantic maps. Do not continue
   golfing them solely for percentage once NOTES identify only register/x87/
   epilogue/layout residuals.
3. For each function: create/update scratch, run `tools/match/match.sh`,
   document residuals, then refresh `tools/match/STATUS.md`.
4. After a function is exact or pinned, keep the recovered C as the source of
   truth and defer the route decision: either mirror it into Zig or expose it
   through a recovered-C gameplay library with Zig as the platform wrapper.
5. Route one caller slice at a time only after that route is chosen, and add a
   regression test or replay-oracle ratchet before deleting the old scaffold path.
6. Commit each coherent match/mirror/route/collapse step with a conventional
   commit message.
