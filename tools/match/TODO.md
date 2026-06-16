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
- Treat a normalized 100% as proof-grade only when the masked-operand audit is
  clean. If `ADDR` hides an unresolved target reference or mismatched candidate
  relocation/string/global, keep the scratch audit-pending and document the
  real owner before counting it as matched.
- Clear masked-audit debt with curated entries in
  `analysis/symbols/gameplay-references.json` only after independent evidence
  names the target address. `.rdata` constants may clear by exact bytes; dummy
  externs or convenience aliases may not.
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
| `spawn_garbage_smoke_particle` | `0x43d5a0` | 76.82%, source-shaped | Smoke-effect producer called by `update_garbage_hazard`; owns render/effects gate, sprite setup, subgame-rate lifetime lanes, and velocity scaling. | Semantics are mapped; remaining residual is color/velocity copy scheduling and ignored byte-return shape documented in NOTES. |
| `append_subgame_contact_target` | `0x415ef0` | 100% | Called by garbage and slug AI; exact match confirms it appends `{kind, position, radius, object}` to a per-frame registry, not a bob mutator. | Done; use as the exact contact-target registry helper for garbage and slug AI. |
| `kill_golb` | `0x414670` | 100% | Exact Golb projectile teardown helper used by impact, wall, speed, and terminal cleanup paths. | Done; use as the source-of-truth for Golb primary/secondary/tertiary BOD unlinking and kind-specific sprite cleanup. |
| `update_player_movement_flags` | `0x43a1a0` | 93.75%, source-shaped | Maps the movement selector to the Golb/fire movement flag mask, fire cadence step, and presentation refresh gate. | Selector table, cadence constants, and `set_snail_weapon` gate are pinned; remaining residual is equal-branch tail merging plus jump-table symbol-shape probes documented in NOTES. |
| `update_movement_flag_emitters` | `0x43a300` | 100% | Exact player emitter dispatcher that maps movement flag families to one, two, or three inactive Golb slots before calling `create_golb`. | Done; use as the source-of-truth for Golb spawn budget and slot scan order before expanding `create_golb`. |
| `update_golb_ai` | `0x414820` | 49.63%, structure complete | Projectile flight, path entry, homing, trails, slug/garbage hit gates, wall impact. | Treat as a pinned semantic map for breadth-first work unless a specific localized lead appears. Live-state gate, path-follow output copies, non-follow position pointer staging, kind-0 gravity ordering, direction delta locals, horizontal slug-deflection normalization, slug kind compare order, homing pull/keep `Vec3` temporaries, homing current-position pointer use, homing target-delta/result stack staging, slug reflected-velocity staging, typed transform copy/member calls, and trail dispatch now better match native; remaining residuals are homing y/z velocity-owner operands, path-output stack staging, collision probe scheduling, and duplicated returns documented in NOTES. |
| `spawn_golb_trail_sprite` | `0x415bb0` | 100% | Exact short-lived trail sprite producer used by straight-flight Golb projectiles behind `update_golb_ai`. | Done; use as the trail sprite lane/order anchor before expanding projectile presentation slices. |
| `spawn_golb_smoke` | `0x415c60` | 82.27%, pinned | Smoke sprite producer used by the rotating/smoke Golb presentation path; confirms sprite id, lifetime/rate lanes, scale, velocity scaling, and position copy. | Semantics are pinned; remaining residual is sprite-base lifetime and x87/store scheduling documented in NOTES. |
| `spawn_golb_impact_sprite` | `0x415d80` | 63.64%, structure-first | Impact sprite producer used when Golb shots are killed or hit terminal collision points. | Semantics are mapped; remaining residual is native stack-vector and saved-`esi` scheduling around the impact velocity copy documented in NOTES. |
| `calc_path_length_z` | `0x4217b0` | 40.58%, structure complete | Golb path-follow riding; sibling of `update_track_attachment_follow_state`. | Scalar/base declaration-order trials are exhausted; continue only with stronger evidence around overflow block placement, matrix-copy layout, and terminal/side-exit shot-position ownership documented in NOTES. |
| `create_golb` | `0x415280` | 28.63%, structure complete | Seeds projectile kind, velocity/spread, homing target, and RNG stream consumers. | Pointer lifetimes, movement-flag reloads, previous-output whole-copy, and the shared `(flags & 5)` movement-source label now better match native setup; continue around remaining movement-flag branch sharing, direction copy staging, and kind-specific setup locals documented in NOTES. |

### P1 - Player Motion And Attachment Exit

These govern the broadest wrong-assumption surface in `update_subgoldy`.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `update_subgoldy` | `0x43b120` | 72.44%, structure complete | Master player motion, replay codec, fire lane, completion handoff, attachment-exit clears. | Continue slice-first: grounded/trampoline clear lanes, projectile/replay consumers, then residual register-shape cleanup. |
| `set_backdrop_progress_fraction` | `0x410c30` | 100% | Exact backdrop progress setter driven by `update_subgoldy` from the active row payload ratio. | Done; pins backdrop `+0x6c8` as a plain float progress lane. |
| `advance_timer_counters` | `0x441b90` | 100% | Exact shared stopwatch accumulator used by `update_subgame` and `update_subgoldy` for elapsed seconds, frame rollover, and display hundredths/thousandths. | Done; use with exact `zero_timer_counters` as the timer-record source of truth. |
| `format_time_trial_string` | `0x448960` | 95.89%, pinned | Shared Time Trial HUD formatter for `initialize_subgame`, `update_subgame`, and challenge setup route records. | Semantics are pinned against exact `TimerCounters`; remaining residual is cdecl stack-cleanup coalescing across adjacent `sprintf` calls, documented in NOTES. |
| `initialize_subgoldy_death` | `0x446e30` | 100% | Exact selector for respawn versus final-loss entry by gameplay mode and visible life stock. | Done; use with exact `initialize_subgoldy_resurrect` and `update_subgoldy_resurrect` as the death/resurrection source of truth. |
| `update_subgoldy_resurrect` | `0x441fd0` | 100% | Exact death/resurrection bridge: freezes z velocity, drives fade-out, spends arcade life stock, calls `complete_subgame(1)` on final loss, and routes frontend state. | Done; use with exact `initialize_subgoldy_resurrect` as the respawn/final-loss source of truth. |
| `play_movement_state_sound` | `0x43afd0` | 89.13%, pinned | Shared RNG draw and fire/movement sound variant cadence. | Semantics are pinned; remaining clamp-tail duplication is documented in NOTES. |
| `calc_subgame_rate` | `0x4404d0` | 84.52%, source-shaped | Per-frame subgame rate composer used by the outer subgame update; ties base rate, completion ramp, bonus-rate phase, and nuke-rate overlay together. | Struct lanes are mapped; continue only around bonus-envelope x87/source scheduling and branch label distance documented in NOTES. |
| `update_squidge` | `0x4449c0` | 84.15%, source-shaped | Damped y/z presentation spring driven by exact `start_squidge_y` and `start_squidge_z`, used by the player motion presentation. | Spring math, constants, output lanes, and zeroing thresholds are pinned; remaining residual is duplicated x87 local reload scheduling documented in NOTES. |
| `begin_track_attachment_follow_state` | `0x420c40` | 94.55%, pinned | Direct attachment begin seed. | Semantics and offsets are pinned; remaining table-base folding residual is documented in NOTES. |
| `try_enter_track_attachment_from_swept_motion` | `0x42c770` | 79.80%, pinned | Swept re-entry gates and player y/lateral seed. | Finish dual-slot source-shape lead in NOTES; do not disturb pinned semantics. |
| `update_track_attachment_follow_state` | `0x420cb0` | 46.44%, semantics pinned | Attachment stepping, natural end, side exit, supertramp launch. | Golf only with source-plausible staging; do not regress routed mirror semantics. |
| `project_position_onto_track_attachment` | `0x4444b0` | 81.16%, source-shaped | Shared projection for garbage/slug/parcel and attachment-row actors. | Kind-42 helper is now exact as a `PathTemplate` member call; continue only around branch-label/local-transform offsets and non-kind42 stack-slot/register residuals documented in NOTES. |
| `compute_kind42_attachment_transform` | `0x42b920` | 100% | Exact kind-42 half-pipe transform helper used by projection, live attachment follow, and constructor-side strip generation. | Done; keep the named `angle` local because it preserves the native x87 schedule around the `atan2_positive` result and output-pointer loads. |
| `get_path_position_at_node` | `0x42b9c0` | 41.12%, source-shaped lead | Primary-sample local x/y projection used by parcel placement and challenge parcel placement on attachment rows. | Native prologue/frame/local-pointer lifetime are recovered; remaining duplicated-x87-lane scheduling is documented in NOTES. Resume only with a source-idiom lead, not volatile/asm/dummy aliasing. |
| `find_segment_path_index_by_name` | `0x429ae0` | 100% | Exact `Path=` name-table lookup used by segment/path-template setup before attachment runtime use. | Done; keep the first-entry symbol plus bounded cursor loop shape that avoids VC6's first-comparison peel. |

### P2 - Collision And Runtime Pools

These should turn current verified port behavior into matched proof.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `handle_subgoldy_collisions` | `0x444cf0` | 45.15%, structure complete | Contact gates for salt, sub-lazer, garbage, slug, rings, health, jetpack, parcel. | Proof-polish: local staging, mask register reuse, per-loop delta/probe shape. |
| `recycle_bod_to_free_list` | `0x447290` | 100% | Exact shared active-list teardown/free-stack helper for BOD nodes used by runtime pickup, projectile, salt, garbage, fringe, and subgame teardown paths. | Done; use as the source-of-truth anchor before consolidating duplicated inline list-removal blocks in larger scratches. |
| `update_active_bod` | `0x433e80` | 100% | Exact default active-bod updater: culls nodes once `world_z + 24.0f` falls behind the live threshold and recycles them through the shared active/free list. | Done; use with exact `recycle_bod_to_free_list` and `refresh_fringe_object_draw_list` as the active/free-list lifecycle anchor. |
| `apply_bod_position` | `0x42f680` | 100% | Exact object-geometry vertex transform loop for BOD/object presentation paths, using exact `multiply_vector_by_matrix_copy`. | Done; keep `END=0x42f6d9` because the manifest gap includes seven nops plus an adjacent uncurated thunk. |
| `health_collect_particles` | `0x43a010` | 43.56%, source-shaped | Health pickup collection burst; confirms Player velocity carry-through into eight Sprite particles and pickup sprite position ownership. | Semantics and shared `TrackHealthPickup`/`Sprite` fields are mapped; remaining residual is stack-frame/register scheduling around loop index, angle, and velocity temp placement documented in NOTES. |
| `update_track_health_pickup` | `0x43ecc0` | 71.88%, source-shaped | Health pickup runtime update: source-cell hidden gate, state-1 cull, state-2 teardown, and sprite-only sine bob lane. | Semantics are mapped against exact `update_track_speedup`; remaining state-1 bob-tail placement and x87/epilogue scheduling residuals are documented in NOTES. |
| `add_subgoldy_score` | `0x4402c0` | 89.66%, source-shaped | Shared score award helper for collisions, hazards, row-event parcels, bonus payouts, life thresholds, and score sound gating. | Semantics and arithmetic prefix are pinned; remaining residual is saved-register epilogue scheduling at the final sound gate, documented with `gated-tail-member-*` idiom probes in NOTES. |
| `uninit_nuke` | `0x4470e0` | 100% | Exact teardown for the 25-sprite ring/special-effect controller armed by ring and special-effect collisions. | Done; use as the lifecycle anchor before matching `initialize_nuke` and `update_nuke`. |
| `initialize_nuke` | `0x447110` | 93.75%, source-shaped | Initializes the 25-sprite ring/special-effect controller, seeds orbit phase/rate state, and immediately dispatches the first update. | Semantics and layout are pinned; remaining residual is flag-temp register choice plus neighboring size-constant scheduling documented in NOTES. |
| `update_nuke` | `0x4471e0` | 89.83%, source-shaped | Advances the 25-sprite nuke/ring controller while active: updates the orbit z-axis, wraps phase, and writes radius-7 sine/cosine positions into each sprite slot. | Semantics are pinned against exact `uninit_nuke` and source-shaped `initialize_nuke`; remaining state-gate residual is documented in NOTES. |
| `initialize_jet_particles` | `0x43a5b0` | 86.49%, source-shaped | Seeds the 15x2 jetpack hover-particle sprite grid used by the gauge hover effect. | Slot stride and Sprite field writes are mapped; remaining residual is register/zero-lane scheduling documented in NOTES. |
| `spawn_track_ring_or_special_effect` | `0x43df10` | 36.83%, evidence-first | Parent allocator/spawner for track ring and special-effect records; seeds parent position, active phase, active phase step, owner context, active list, and child particles. | Native has per-kind RNG tags (`RR..RR13`) and duplicated switch paths, but split-source forms fail to emit `scratch.obj`; keep grouped compilable source and use NOTES as the exact case map. |
| `initialize_ring_or_special_effect_particles` | `0x43e470` | 96.42%, pinned | Allocates and seeds the ten child halo sprites for ring/special-effect parents, including particle phase/radius and star sprite kind. | Semantics and child/parent layouts are pinned; remaining residual is child-pointer scheduling around the state stores documented in NOTES. |
| `emit_ring_star_shower` | `0x43e690` | 58.54%, source-shaped | Small star burst producer called by the child halo updater; confirms parent star sprite id and particle sprite/phase/radius lanes. | Direct trig-call argument spelling plus separate unscaled X/Y velocity temps now matches native ordering better; remaining stack-frame/zero-lane/position-copy residual is documented in NOTES. |
| `update_ring_or_special_effect_particle` | `0x43e780` | 96.36%, pinned | Child halo updater for ring and special-effect sprites, including phase advance, sprite orbit position, and star-shower cadence dispatch. | Semantics are pinned; remaining residual is one parent-position address materialization ordering difference documented in NOTES. |
| `update_subgoldy_bullet` | `0x43e830` | 69.77%, source-shaped | Parent virtual updater for ring/special-effect records: cadence, normal orbit, collapse/expand transitions, active-list removal, and child sprite teardown. | State-3 collapse now uses a real `Vector3 delta`; remaining residual is direct 0..5 switch shape plus native's larger stack-temp frame documented in NOTES. |
| `wall2_emitter_maybe_fire_sub_lazer` | `0x439d50` | 42.34%, pinned | Wall2 fire cadence and 4% RNG gate. | Semantics are pinned; RNG tags, emitter cadence, and source-shape residuals are documented in NOTES. |
| `spawn_sub_lazer_projectile` | `0x441670` | 98.41%, pinned | SubLazer body/sprite spawn and y stagger. | Semantics and instruction count are pinned; remaining residual is store scheduling around velocity z versus bob phase, documented in NOTES. |
| `update_track_jetpack_pickup` | `0x43efb0` | 72.44%, pinned | Jetpack pickup parent teardown and nested sprite bob. | Vtable ownership is pinned to `initialize_track_jetpack_pickup_runtime`; remaining register/layout residuals are documented in NOTES. |
| `shoot_subgoldy` | `0x441ad0` | 49.46%, pinned | Weapon/sub-lazer spawn callsite and audio cue. | Semantics are pinned; free-scan loop residual and unstaggered audio origin are documented in NOTES. |
| `explode_slug_hazard` | `0x43f680` | 73.22%, structure-first | Slug death particle burst spawned by the exact `kill_slug_hazard` helper. | Semantics are mapped; remaining frame/register/x87 scheduling residuals are documented in NOTES. |
| `initialize_blink_random` / `advance_blink_random` | `0x4408c0` / `0x4408a0` | 100% | Exact 24-entry blink cadence table initialization and advance helper used by slug hazard AI. | Done; use as the RNG cadence source-of-truth before expanding `update_slug_hazard_ai`. |
| `spawn_salt_hazard` | `0x441560` | 74.07%, pinned | Salt slot layout, velocity byte-poke bug, yaw RNG. | Semantics are pinned; free-scan layout residual and velocity.z byte-poke finding are documented in NOTES. |
| `update_sub_lazer_projectile` | `0x4417d0` | 48.39%, pinned | Sub-lazer projectile integrate/removal state and attachment containment probes. | Semantics are pinned; velocity, bob phase, and probe residuals are documented in NOTES. |
| `deactivate_sub_lazer_projectile` | `0x441740` | 62.79%, pinned | Sub-lazer collision/removal edge. | Semantics are pinned; duplicated error-block and register residuals are documented in NOTES. |
| `update_salt_hazard` | `0x441c10` | 62.96%, pinned | Salt fade/update state installed by `initialize_salt_hazard_runtime`. | Field offsets are pinned; remaining residual is the state-2 error-string tail merge documented in NOTES. |

### P3 - Damage, Warning, Camera, And Presentation Control

These are medium blast-radius systems already partly understood.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `apply_damage_gauge_delta` | `0x4413f0` | 60.32%, pinned | Hit-flash gate, damage/recovery clamp, side effects. | Semantics are pinned; corrected voice-failure animation nesting, constant relocation mismatch, and rejected local-shape probes are documented in NOTES. |
| `update_damage_gauge` | `0x440fd0` | 80.60%, source-shaped | Drain, state transitions, warning interaction. | State block placement and warning call ownership now match native shape; remaining residual is x87/local scheduling documented in NOTES. |
| `update_warning` | `0x446f80` | 78.85%, source-shaped | Warning actor loop, stop sample handle, global gates. | State-2-first source now matches native shape better; dispatch-ladder regression and residuals are documented in NOTES. |
| `enqueue_tip_message` | `0x448d30` | 100% | Exact three-slot gameplay tip allocator used by `update_subgoldy` row-event and tutorial prompt paths. | Done; keep the `while (1)` scan idiom with exact tip manager init/update/uninit helpers as the tip slot lifecycle anchor. |
| `update_tip` | `0x448c40` | 73.08%, pinned | Tip slot runtime: suspend hide/unhide, OK/Disable click consumption, auto-dismiss, widget teardown, and frontend owner restore. | Semantics are pinned; remaining residual is button flag pointer ownership and two address-materialization instructions documented in NOTES. |
| `initialize_tip` | `0x448a40` | 75.00%, source-shaped | Tip slot initializer: allocates the main text widget, optional OK/Disable buttons, default tip definition, dismiss timing, and frontend owner capture. | Shared `TipSlot` fields and default definition are mapped; remaining residual is widget field-load and stack-local scheduling documented in NOTES. |
| `update_cameraman` | `0x4461d0` | 92.55%, pinned | Camera matrix blend and attachment-exit roll. | Treat as pinned unless exact register allocation becomes obvious. |
| `initialize_cameraman` | `0x446160` | 100% | Camera init baseline. | Done; keep as dependency. |
| `initialize_snail_skin` / `update_snail_skin_transition` / `change_snail_skin` | `0x445f60` / `0x445f80` / `0x445fd0` | 100% | Skin state is matched; renderer consumer still missing. | No matching work unless renderer callsites demand more. |
| `initialize_anim_manager` / `update_anim_manager` | `0x4447c0` / `0x4447d0` | 100% / 43.68% | Presentation animation manager reset/update pair used by player, weapon, jetpack, and cutscene animation channels. | Init is exact and pins the prefix; update maps queue and target animation ownership, with remaining zero-lane/register scheduling documented in NOTES. |
| `get_or_create_texture_ref` | `0x44e810` | 76.07%, source-shaped | Shared texture-reference list lookup/allocator behind sprite texture registration, mesh/path textures, and sprite runtime texture refs. | `TextureRefList` and `TextureRef` stride/name/slot fields are corrected; remaining residual is scan-found return block layout and final count-increment scheduling documented in NOTES. |

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
| `allocate_path_template_samples` | `0x41b0a0` | 100% | Exact allocator for primary/secondary `PathTemplateSample` arrays used by every authored path-template constructor. | Done; pins `segment_count`, `primary_samples`, `secondary_samples`, and the `0xa8` sample stride before expanding constructor or projection/follow paths. |
| `request_object_vertices` | `0x42f710` | 100% | Exact strip/object vertex allocator used by path-template mesh builders and X-mesh loading; calls exact vertex-colour allocation after seeding vertices. | Done; use with exact facequad/colour helpers as the object mesh layout anchor (`vertex_count +0x2c`, vertices `+0x38`, colours `+0x48`). |
| `request_object_vertex_colours` | `0x42f850` | 100% | Exact vertex-colour allocator for strip/object meshes; initializes RGB to `1.0f` while leaving alpha untouched. | Done; keep `END=0x42f89d` because the manifest gap includes padding plus an adjacent uncurated thunk. |
| `request_object_facequads` | `0x42f8c0` | 100% | Exact facequad allocator/capacity helper used by path-template strip builders and X-mesh loading. | Done; pins `facequad_count +0x54`, capacity `+0x58`, and facequad pointer `+0x5c`. |
| `request_object_facequad_normals` | `0x42f800` | 100% | Exact toon-normal support allocator used by facequad-normal calculators and object animation loading. | Done; pins vertex normals `+0x44`, facequad normals `+0x60`, and the `0x18` facequad-normal pair stride. |
| `request_object_texture_groups` | `0x42f930` | 96.55%, pinned | Facequad texture-group allocator/capacity helper used by `calc_object_texture_groups`. | Semantics are pinned; remaining residual is one load-order difference in the fixed-buffer branch, documented in NOTES. |
| `rstrcpy_checked_ascii` / `strings_equal_case_insensitive` / `find_case_insensitive_substring` / `parse_next_signed_int` | `0x44e5b0` / `0x431dc0` / `0x44e600` / `0x44e710` | 100% / 29.13% / 25.71% / 28.87% | Shared resource string and parser helpers used by texture, object, X-mesh, level, segment, landscape, and voice loaders. | Copy helper is exact and pins the high-bit diagnostic; other three are relationship-first scratches with prefix/tag/number semantics and residual register/control-flow shape documented in NOTES. |
| `populate_runtime_track_cells_from_segments` | `0x435eb0` | 7.13%, structure-first | Runtime glyph normalization, digit-on-attachment voiding, row ownership. | Scratch now covers setup, row-count seeding, clear pass, and visited reset; expand next through row-selection/row-flag copy before tackling the glyph switch. |
| `mark_track_warning_zones` | `0x4354f0` | 32.51%, pinned | Warning footprint and hazard suppression. | Semantics are pinned; tile seed set, 6x2 footprint, bounds, and register-layout residuals are documented in NOTES. |
| `build_track_fringe_objects` | `0x434be0` | 49.44%, structure-first | Allocates directional fringe objects after runtime-cell build; useful for separating renderer-only edge data from gameplay grid state. | Register/local ownership is the next blocker: native keeps game in `ebp`, family in `edi`, edge-a in `ebx`, then reuses/restores `ebp` for edge-b; residual bool probes and skirt-color copy scheduling are documented in NOTES. |
| `is_neighbor_cell_solid` | `0x434b60` | 68.82%, source-shaped lead | Shared fringe-build predicate for lateral/row neighbor solidity, open-neighbor tile families, and tile-id exclusions. | Semantics are recovered; remaining residual is folded neighbor-base address plus tile-id register ownership documented in NOTES. Resume only with a source-shape lead, not volatile/dummy aliasing. |
| `allocate_fringe_object` | `0x4470a0` | 100% | Exact allocator for the 7000-entry fringe-object pool used by `build_track_fringe_objects`. | Done; use as the pool cursor/overflow anchor for fringe build and renderer assumptions. |
| `refresh_fringe_object_draw_list` | `0x439b00` | 100% | Exact fringe draw-list refresher: copies the live skirt colour, culls by fringe z threshold, and recycles the BOD node through the shared active/free list. | Done; use with exact `recycle_bod_to_free_list` as the active/free-list source-shape anchor for fringe lifecycle cleanup. |
| `switch_track_mirror` | `0x435e60` | 91.23%, pinned | Runtime mirror state and builder row convention. | Semantics are pinned; remaining duplicate-tail layout residual is documented in NOTES. |
| `update_row_event_display` | `0x404cf0` | 99.53%, pinned | Parcel home anchor, row-event widget, prompt ownership. | Semantics are pinned; the only accepted residual is bonus sound thiscall setup order, documented in NOTES. |
| `register_parcel_delivery` | `0x405040` | 100% | Exact parcel-delivery score/audio/state handoff into the row-event display. | Done; use as the delivery-side anchor for parcel collision and row-event state transitions. |
| `flush_row_event_display` | `0x404830` | 89.39%, source-shaped | Forces pending row-event parcel payouts and tears down widgets during completion/destruction. | Semantics are pinned; remaining residual is the post-bonus count increment spelling documented in NOTES. |
| `add_time_trial_high_score` | `0x4178b0` | 83.67%, pinned | Time Trial result persistence helper called by `complete_subgame`; owns scratch copy versus persistent route-record replacement. | Semantics are pinned; remaining residual is selected route-record base materialization/register scheduling documented in NOTES. |
| `display_score_stats` | `0x4403c0` | 90.28%, pinned | Completion score-bucket report helper called by `complete_subgame` before final result snapshot. | Semantics are pinned; remaining residual is the native batched cdecl cleanup for the stripped debug-report calls, documented in NOTES. |
| `complete_subgame` | `0x438700` | 75.28%, pinned | Completion bridge producer. | Semantics are covered; remaining direct-memory byte-OR and result-snapshot register scheduling residuals are documented in NOTES. Do not force them with volatile, raw offset macros, or fake aliasing. |
| `get_track_skirt_color` | `0x442120` | 100% | Shared skirt RGBA producer for fringe/render-cache paths. | Done; keep the direct aggregate assignment from `set_color_rgba`, which is the source idiom that preserves native copy scheduling. |
| `update_subgame` | `0x438b90` | no scratch | Outer gameplay state machine, active row scan, bridge opcodes. | Defer until lower-level runtime functions are trustworthy. |
| `update_frontend_state_machine` | `0x4107d0` | 58.12%, structure-first | Frontend/subgame bridge and return owners. | Block-local game owners now recover the native `lea ecx, [base+offset]` call shape for most dispatch bodies; continue only around register allocation, shared-exit label distance, and jump-table/data extent residuals documented in NOTES. |

### P5 - Math Helpers That Block Cleaner Mirrors

These are not gameplay owners, but several mirrors depend on them.

| function | address | current | why it matters | next matching move |
|---|---:|---|---|---|
| `convert_math_type32_to_16` | `0x44c890` | 100% | Exact float-to-signed16 replay quantizer used by `update_subgoldy` for replay and ghost motion samples. | Done; keep with exact reverse conversion as the replay quantization source of truth. |
| `convert_math_type16_to_32` | `0x44c8b0` | 100% | Exact signed16-to-float replay decoder used by `update_subgoldy`, including native expression order for `scale / 65536.0f`. | Done; keep with exact forward conversion as the replay quantization source of truth. |
| `initialize_global_identity_matrix` | `0x44c880` | 100% | Exact constructor-table wrapper that initializes the shared identity transform through uniform scale `1.0f`. | Done; use with exact `initialize_uniform_scale_matrix` as the global identity-matrix source of truth. |
| `initialize_math_random_table` | `0x44c8d0` | 100% | Byte-exact 0x1fff-entry gameplay random-table initializer and cursor reset before `next_math_random_value` consumption. | Done; the masked audit uses the sized `g_math_random_table` range to distinguish the one-past compare at `0x78ff88` from the next global without a fake alias. |
| `initialize_trigonometry_tables` | `0x44c930` | 100% | Exact startup sine/cosine table builder that also resets the gameplay random table. | Done; keep the two `float` scale multiplies before the native `fcos`/`fsin` sequence. |
| `cosine` | `0x44c980` | 100% | Exact cosine lookup wrapper used by attachment, camera, projectile, nuke/ring, and path-template math. | Done; keep the CRT validation as a `float` local before the masked table lookup so the native x87/dword compare shape stays intact. |
| `sine` | `0x44c9d0` | 100% | Exact sine lookup wrapper used by pickup bobbing, projectile halos, damage flash, nuke/ring presentation, and camera paths. | Done; keep the explicit scaled-angle intermediate so VC6 preserves the native two-multiply table-index shape. |
| `arccosine` | `0x44ca00` | 100% | Exact CRT arccos wrapper used by quaternion and attachment/camera math. | Done; keep the explicit result local that prevents tail-call lowering. |
| `atan2_positive` | `0x44ca10` | 100% | Exact quadrant-aware positive arctangent helper used by kind-42 attachment transforms and sprite-facing angle updates. | Done; keep the sign-normalization/quadrant-id source shape and `atan(y / x)` spelling. |
| `square_root` | `0x44cab0` | 100% | Exact CRT square-root wrapper used by vector, attachment, projection, and renderer math. | Done; use as the source-of-truth callee for vector length and projection helpers. |
| `multiply_vector_by_matrix_copy` | `0x44cac0` | 100% | Exact out-of-place affine vector transform used by attachment, camera, object, and render-cache math. | Done; keep the stack-result aggregate initialized from `this` before writing the caller output. |
| `multiply_vector_by_matrix` | `0x44cb90` | 85.00%, pinned | In-place affine vector transform with a by-value matrix ABI and source-vector preservation. | Semantics and ABI are pinned; remaining residual is first matrix load/source-copy x87 scheduling documented in NOTES. |
| `rotate_vector_by_matrix` | `0x44cc20` | 100% | Exact in-place rotation-only vector transform through the 3x3 matrix basis. | Done; keep the stack source-vector copy before destination overwrite. |
| `vector_magnitude` | `0x44ccf0` | 94.74%, pinned | Shared 3D vector length helper used by Golb spawn, track parcels, star-field entries, object geometry helpers, and positional audio. | Semantics are pinned; the only residual is `add esp, 0x4` versus `pop ecx` cleanup after the exact `square_root` call. |
| `normalize_vector` | `0x44cca0` | 100% | Exact in-place vector normalization helper used by path construction, collision probes, projectile steering, sprite-facing math, and presentation systems. | Done; use with exact `dot_vectors` and `square_root` as the vector-length source of truth. |
| `cross_vectors` | `0x44cd40` | 100% | Exact 3D cross-product helper used by path-template basis construction, matrix orthogonalization, object normals, and track/fringe geometry. | Done; keep the function-local static `Vec3` temporary and explicit target end before the adjacent static destructor stub. |
| `initialize_uniform_scale_matrix` | `0x44cde0` | 100% | Exact full 4x4 uniform-scale initializer for transform matrices. | Done; use as the matrix constructor source of truth for global identity setup and scale-only transforms. |
| `rotate_matrix_world_x` | `0x44ce30` | 100% | Exact in-place world-X basis rotation used by camera/object/attachment transform paths. | Done; keep the shared sine/cosine helper calls and lane-local temporaries. |
| `rotate_matrix_world_y` | `0x44cec0` | 100% | Exact in-place world-Y basis rotation used by camera/object/attachment transform paths. | Done; keep the right/forward basis mix order. |
| `rotate_matrix_world_z` | `0x44cf50` | 100% | Exact in-place world-Z basis rotation used by sprite/object/camera transform paths. | Done; keep the right/up basis mix order. |
| `initialize_matrix_from_values` | `0x44cfe0` | 100% | Exact full 16-float transform initializer used by explicit matrix construction sites. | Done; preserves right/up/forward/position row order. |
| `multiply_matrix_in_place` | `0x44d1a0` | 100% | Exact in-place postmultiply wrapper around `multiply_matrices` with a stack-saved left operand. | Done; keep the explicit end before the adjacent uncurated thunk at `0x44d1d0`. |
| `premultiply_matrix_in_place` | `0x44d1e0` | 100% | Exact in-place premultiply wrapper around `multiply_matrices` with a stack-saved destination operand. | Done; keep the output-member call shape. |
| `invert_matrix_in_place` | `0x44d280` | 100% | Exact in-place affine inverse helper for transform matrices, including source-preserving basis transpose and inverse-position dot products. | Done; keep the stack source-matrix copy and native expression order for `position.x`. |
| `invert_matrix_from_source` | `0x44d330` | 100% | Exact out-of-place affine inverse helper used when a destination matrix is rebuilt from a source transform. | Done; keep the destination-member thiscall shape and null return. |
| `orthogonalize_matrix` | `0x44d3d0` | 92.31%, pinned | Small basis repair helper that normalizes right/up/forward and rebuilds two axes through exact `cross_vectors`. | Semantics are pinned; the only residual is thiscall setup order for the two cross-product calls. |
| `set_matrix_z_direction` | `0x44d410` | 100% | Exact basis builder for look/z-direction transforms used by camera/object/attachment math. | Done; keep the persistent `basis_up` pointer that preserves the native saved-`edi` cross-product call shape. |
| `initialize_quaternion_from_axis` | `0x44d530` | 77.78%, pinned | Axis-angle to quaternion conversion through exact sine/cosine helpers. | Semantics are pinned; residual is x87 operand order for live sine scaling documented in NOTES. |
| `initialize_axis_from_quaternion` | `0x44d580` | 100% | Exact quaternion to axis-angle conversion through exact arccosine/sine helpers. | Done; keep repeated `sine(half_angle)` calls, matching native source shape. |
| `initialize_matrix_from_quaternion` | `0x44d820` | 73.05%, source-shaped | Quaternion to matrix conversion used by rotation interpolation and transform setup. | Semantics are mapped; remaining stack-slot, doubled-expression, and zero-store scheduling residuals are documented in NOTES. |
| `interpolate_matrix_rotation` | `0x44d920` | 71.89% | Native rotation interpolation for attachments/camera. | Improve only with plausible x87/source staging. |
| `linear_interpolate_matrix` | `0x44da90` | 49.57% | Matrix-space interpolation; already invalidated old pose lerp. | Match enough to confirm normalization/orthogonalization call shape. |

## Already Matched Or Pinned Dependencies

- Exact helpers to keep using as anchors: `search_path_for_golb`,
  `allocate_path_template_samples`,
  `initialize_path_follow_golb`, `begin_post_follow_carryover`,
  `compute_kind42_attachment_transform`,
  `get_track_grid_cell_at_world_position`, `sample_track_floor_height_at_position`,
  `initialize_subgoldy_ghost`, `update_track_speedup`,
  `apply_bod_position`,
  `update_subgoldy_resurrect`,
  `set_backdrop_progress_fraction`,
  `destroy_garbage_hazard`, `hit_slug_hazard`, `kill_slug_hazard`,
  `initialize_blink_random`, `advance_blink_random`,
  `append_subgame_contact_target`, `kill_golb`,
  `update_movement_flag_emitters`,
  `initialize_array_with_constructor`,
  `request_object_vertices`, `request_object_vertex_colours`,
  `request_object_facequad_normals`, `request_object_facequads`,
  `spawn_track_parcel`, `noop_runtime_ai`,
  `convert_math_type32_to_16`, `convert_math_type16_to_32`,
  `initialize_global_identity_matrix`, `initialize_math_random_table`,
  `initialize_trigonometry_tables`, `cosine`, `sine`, `arccosine`, `atan2_positive`,
  `square_root`, `multiply_vector_by_matrix_copy`,
  `rotate_vector_by_matrix`, `normalize_vector`, `cross_vectors`,
  `initialize_uniform_scale_matrix`, `rotate_matrix_world_x`,
  `rotate_matrix_world_y`, `rotate_matrix_world_z`,
  `initialize_matrix_from_values`, `multiply_matrix_in_place`,
  `premultiply_matrix_in_place`, `invert_matrix_in_place`,
  `invert_matrix_from_source`, `set_matrix_z_direction`,
  `initialize_axis_from_quaternion`,
  voice helpers,
  and the small runtime initializer family in `tools/match/STATUS.md`.
- Pinned-enough functions should not be churned for percentage alone:
  `update_cameraman`, `begin_track_attachment_follow_state`,
  `try_enter_track_attachment_from_swept_motion`,
  `spawn_sub_lazer_projectile`, `update_row_event_display`,
  `vector_magnitude`, `multiply_vector_by_matrix`,
  `initialize_quaternion_from_axis`, `orthogonalize_matrix`, and any scratch
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
