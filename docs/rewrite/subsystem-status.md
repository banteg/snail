# Subsystem Status

This page is the detailed working tracker for the Zig port.

Reference only:
- not default loop context
- use the active dossier or packet first
- keep transient narrowing in focused notes or runtime packets instead of appending every micro-finding here

Use it when picking the next task. [`port-status.md`](port-status.md) stays the short ledger; this page is the fuller subsystem-by-subsystem read of what is implemented now, what is still approximate, and what the next grounded work should be.

## Status Legend

- `verified`: backed strongly enough by Windows static RE or runtime capture to treat the current behavior as ported
- `partial`: on the right architecture or semantics, but still missing important coverage or family-specific behavior
- `fallback`: deliberate approximation that keeps the game moving without claiming Windows parity
- `scaffold`: structural placeholder that exists to support later port work
- `debug`: tooling or inspection surface, not the shipping game path

## Frontend Shell And Transitions

Status: `partial`

Implemented now:

- archive-backed loading screen, intro crawl, credits crawl, menu backdrops, and front-end music
- main menu, new-game menu, challenge setup, help, options, route map, high-score screen, pause overlay, and a shared exit prompt
- the recovered New Game tutorial gate: default `SnailMail.cfg` keeps `Postal Mode`, `Time Trial`, and `Challenge Mode` hidden, and the `Tutorial` launch path flips the same config byte so later New Game visits expose the full menu without collapsing the native layout gaps
- direct menu transitions for the paths the Windows code handles directly, instead of forcing everything through the black overlay
- route-map post-completion mode with the special `Exit` label and locked-open selected route behavior
- recovered widget shortcut dispatch for the screens that actually seed shortcut keys in Windows: pause-menu `Esc`/`O`/`Enter` and post-level high-score `Esc`/`Enter`

Still missing or approximate:

- owner-specific exit-prompt layouts beyond the currently recovered menu and route-map cases
- remaining pause-menu owner/controller details beyond the recovered shortcut keys
- some widget effects and shared widget-controller behavior
- remaining front-end return-state subtleties around replay and post-run owners

Best next work:

- tighten the shared widget controller only when a screen-level mismatch is clearly driven by that path
- keep front-end work focused on ownership/transition correctness, not more screenshot tuning in isolation

## Runtime Files And Persistence

Status: `partial`

Implemented now:

- explicit runtime root at `artifacts/runtime`
- load and save `SnailMail.cfg`
- preserve and expose the recovered `SnailMail.cfg +0xc0` New Game tutorial gate instead of leaving it buried inside the raw blob tail
- load and save compact `ScoreA.dat`, `ScoreB.dat`, and `ScoreC.dat`
- preserve the recovered compact-record replay-mode (`0x30`), runtime-build-flags (`0x38`), challenge-speed raw/scalar (`0x4c/0x48`), challenge-difficulty raw/scalar (`0x50/0x54`), runtime-build-seed (`0x70`), and ambient hazard scalar (`0x78/0x7c`) lanes, and write the current gameplay values into new score records
- source the current challenge replay speed and difficulty from the recovered gameplay-tuning bytes in `SnailMail.cfg` instead of fixed placeholder defaults
- preserve opaque compact-record tails for loaded entries instead of flattening everything to header-only rewrites
- expose the recovered 5-byte replay payload lanes (`lateral`, neutral secondary lane, `flags`) from loaded compact records instead of treating the saved replay tail as a totally opaque blob
- inline name-entry flow inside the shared high-score screen

Still missing or approximate:

- full replay payload synthesis for new or replaced score entries
- exact meanings of many compact-record fields
- full runtime parity for replay-bearing score writes beyond the recovered build-seed lane

Best next work:

- keep preserving unknown compact-record data
- avoid inventing replay-capable save records until the full replay serializer is understood

## Track Build And Runtime Grid

Status: `partial`

Implemented now:

- parse `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- preserve row annotations like `Path`, `Parcel`, `3DModel`, `JetPack=Off`, `NoFall`, `Sample`, and `Message`
- rebuild a normalized runtime grid with the recovered `normalize_segment_glyph_for_track_flags` helper shape, the shared math-RNG seed lane, and the current known runtime tile families and floor-height sampling
- reuse the recovered mode-specific gameplay build presets (`0x00f5cfff`, `0x0075cfff`, `0x00e4cfff`) instead of forcing every mode through one shared flag set
- derive installed attachment-row ownership from runtime attachment tiles and now choose the mirrored installed-template half from the recovered builder-state lane instead of always using one canonical template
- preserve the chosen gameplay build seed across app-side respawn rebuilds instead of silently rebuilding the same route from seed `0`
- feed the live garbage/salt gameplay scalars from the recovered mode-dependent runtime lane instead of always falling back to raw level metadata

Still missing or approximate:

- the exact replay-seed handoff and any remaining non-track consumers that advance the shared math RNG before a level rebuild
- the exact active-row band selection that feeds the `_` normalization helper lane
- the full render-normalization chain between runtime tiles and final cache/object ownership
- some unresolved runtime tile families and late render passes

Best next work:

- keep the normalized runtime grid as the common substrate
- avoid adding new gameplay/render behavior straight from authored glyphs when there is already a runtime-grid analogue

## Track Rendering

Status: `partial`

Implemented now:

- textured track scene for supported `Track:` sets `0..3`
- world-UV top-surface rule for the flat cache families
- ramp UVs kept off the flat world-UV rule
- fixed 8-lane-style strip rendering instead of path-only top-surface trimming
- run-aware top-surface ownership for the recovered floor and slide families
  - the merge lane now follows the native family split more closely: real floor-family runs condense, while warn-promoted and corner-marked heads stay separate
- the runtime edge-mask lane now carries the native corner bit on `5/6/9/10` masks, so later passes can distinguish corner heads from plain open edges
- native-shaped warn-surface promotion for open-below floor and slide cells
  - static asset-init recovery now confirms both recovered replacement tables route into the shared `TRACKWARN` asset family, so the remaining gap is exact BOD-object matching rather than a missing texture-family split
- native-shaped center-seam floor/slide family swaps on the recovered seam lanes
- recovered `mark_track_warning_zones` footprint grid in the runtime preview and debug path
  - that warning-footprint lane now also drives one recovered gameplay consumer: it suppresses generic ambient garbage/salt fallback spawns in `update_subgame`
- simple fringe skirts and back plane
  - the fringe pass now also mirrors two native suppressors from `build_track_fringe_objects`: no fringe on marked rows and no fringe on explicit runtime warn tile `0x20`
  - the simple fringe pass now uses the native solid-neighbor rule from `is_neighbor_cell_solid`, including the special non-solid treatment for runtime tile `0x16`
  - the simple fringe pass now also uses the recovered shared skirt tint shape: white RGB with the native fixed `0.4` alpha from `get_track_skirt_color`

Still missing or approximate:

- `select_track_tile_edge_variants`
- exact BOD-table matching inside `promote_track_tiles_to_fringe_variants`
- `merge_track_tile_runs` beyond the currently ported ownership slice
  - marked-row suppression and the remaining low-bit flag semantics are still unresolved
- the final warn-cache consumer for the recovered `mark_track_warning_zones` footprint beyond the now-ported fallback-hazard suppressor
- real directional fringe objects and cache families
  - the underlying Windows pool is clearer now: `initialize_fringe_manager` + `allocate_fringe_object`

Best next work:

- recover the remaining render-normalization passes before guessing more texture ownership
- prefer improving ownership and geometry over cosmetic texture tweaks

## Attachment Builder Registry

Status: `partial`

Implemented now:

- a shared public `Path=` registry in [`attachment_builders.zig`](../../zig/src/attachment_builders.zig)
- all `51` public authored path names are represented
- every public path now builds a Zig-side template through one of the builder families
- neutral runtime-family treatment for the nonlinear kind-`42` branch instead of overnaming it as `WARP`
- the nonlinear kind-`42` viewer/gameplay pose now uses the recovered transform-helper shape instead of a separate circle-height approximation

Still missing or approximate:

- the exact Windows installed-bank pairing rules
- the exact authored-name-to-constructor split inside the nonlinear kind-`42` family
- remaining family-specific fields that belong on installed runtime records instead of templates

Best next work:

- keep the public-name registry authoritative on the Zig side
- avoid baking speculative Windows pair-slot assumptions into the builder scaffold

## Attachment Geometry In The Segment Viewer

Status: `partial`

Implemented now:

- `Segments` game render draws built attachment geometry instead of only showing path labels
- ordinary families render as sampled strip meshes
- the nonlinear kind-`42` family renders as a curved strip mesh
- attachment strips are explicitly double-sided
- the segment HUD and inset now expose authored path rows, family, and status

Implemented families:

- all public attachment names build and render through the scaffold
- `START`, loop families, hill/valley, hump/dump, loopout, turnover, turnunder, `WIBBLE`, `INVERT`, `SUPERTRAMP`, the `P` family, twisters, and the current nonlinear kind-`42` family are all represented

Still missing or approximate:

- exact inside/outside material pairing for attachment strips
- the full Windows installed-bank ownership for mirrored halves
- path-family-specific mesh details that depend on still-missing constructor/install evidence

Best next work:

- keep using the segment viewer as the validation sandbox before widening a family change into gameplay

## Attachment Gameplay Follow

Status: `partial`

Implemented now:

- gameplay can follow built attachment templates instead of only row-midpoint hints
- built templates drive live attachment progression, world pose, camera forward/up, and lane-center output
- generic non-installed attachment begin now seeds progress from live player `z` relative to the source-row anchor and seeds local height from live player `y - 0.49`, instead of the older row-fraction and zero-height shortcut
- natural-end exit now uses template progress and template end pose
- elevated side exits preserve airborne height instead of snapping straight to the floor
- `SUPERTRAMP` has a dedicated launch exit path
- normal gameplay entry now mirrors the native split between current-cell begin and swept re-entry: current row tiles `29/30` go through the direct begin helper when `attachment_exit_pending` is clear
- current-row and visited-row attachment-entry handling no longer fall back to a synthetic generic source-row begin when the installed-owner map is empty; rows without installed owners now stay inert instead of fabricating follow state
- swept installed re-entry now also stays on that same native owner boundary: the Zig runner only probes the live current row while `attachment_exit_pending` is armed instead of letting the later visited-row pass opportunistically arm it
- those swept probes now also use the live current-row owner bits in native order: `flags_b & 0x40` first, then `flags_b & 0x80` only if the first probe leaves `attachment_exit_pending` armed
- raw BN plus the checked-in IDA export now narrow one more gate detail: the primary swept helper path does not show a direct early clear of `attachment_exit_pending`, and the caller re-tests the same byte immediately before the `0x80` probe, so overlapping rows still leave that secondary callsite reachable in the same tick
- the geometric installed-entry attempt now mirrors the recovered tail-to-head sample sweep and skips upside-down samples without falling back to a synthetic current-row sweep result
- the attachment-exit seed/value lanes now keep neutral placeholder names in the port instead of overclaiming their native semantics
- the port also no longer clears `attachment_exit_pending` from a fake `progress >= 1.0` timeout; active-phase retirement now uses the confirmed jetpack clear plus a conservative grounded/trampoline settle proxy. The proxy currently fires whenever the current runtime tile is `0x16` (trampoline) or is not in the open-neighbor family (`{0x00, 0x0e, 0x1c, 0x1d, 0x23}`), which is broader than all three recovered grounded-snap lanes combined — the native `0x43bf6f`, `0x43c06d`, and `0x43c3ea` clears each gate on `!follow_state.active`, y-position, velocity.y, or tile envelope that the proxy ignores

Still missing or approximate:

- full Windows installed runtime bank and owner-record semantics
- the later controller that finally retires `attachment_exit_pending` after swept re-entry
  - five clear sites inside `update_subgoldy` are now fully identified:
    - `0x43bcb3` — non-follow floor-cache/slide block, fires on runtime tiles `0x0f/0x10/0x12/0x13` or slide-family cells when `damage_gauge.state == 2`, mutually exclusive with swept-reentry path (sibling of the `_pad_41c == 0` branch)
    - `0x43bf6f` — **swept re-entry failed → grounded snap**, the common late retirement after swept re-entry: `!follow_state.active && y<0.49 && y≥-0.163 && !is_open_neighbor(cell) && cell->tile_id != 0x16 && velocity.y<-0.03 && velocity.y<0`
    - `0x43c06d` — tile-flags grounded re-snap: `velocity.y ≥ threshold(tile_flags_3d)` + `(runtime_flag & 4) != 0` + `(global & 2) == 0` + `y<0.49`
    - `0x43c3ea` — trampoline (tile `0x16`) bounce: `|y - cell_y| < 0.49` envelope, then squidge + velocity flip + `position.y = cell_y + 0.49` + `play_sound_effect(0x29)`
    - `0x43ce75` — jetpack altitude cap: `jetpack_gauge.state == 1 && position.y < 1.0`
  - `attachment_exit_progress` itself only has the one progress-update store at `0x43ce96`, which runs as the `else` of the five clear lanes (no progress-timeout clear exists in native)
- the follow-milestone lane behind the static `voice 4` callsite is **dead code**: the field at `[esi+0x44]` is `PathTemplate::segment_count` (not `sample_count` — the HLIL `_pad_3c[8].d` is a char-pad byte index). The gate `sample_index+1 == segment_count * 2` at `0x420d1d` is unreachable because the helper terminates at `sample_index == segment_count` first, with `sample_index` starting at 0 and advancing by 1. Do not port.
- exact family-specific entry/exit behavior for the nonlinear kind-`42` family
- exact side-exit/natural-end return values and the native meaning of the attachment-exit seed/value lanes

Best next work:

- recover the later controller that finally retires `attachment_exit_pending` after swept re-entry, then live-check whether two valid overlapping probes can overwrite each other in one tick
- then port the missing family-specific exit behavior, especially for the nonlinear branch

## Gameplay Camera

Status: `partial`

Implemented now:

- default gameplay camera follows the runner instead of reusing the debug orbit camera
- attachment follow and launch states feed the camera with built template forward/up vectors
- textured gameplay rendering is now used in actual play for supported track sets
- the gameplay viewport now also draws a live Turbo model from the runner's current world frame, so the player is finally visible in the actual level path instead of only in the debug model viewer
- active tutorial prompts now also switch Turbo into the shipped `turbo-talk` animation family instead of leaving gameplay guidance as UI/voice-only
- the normal gameplay path no longer renders the old debug HUD shell; it now keeps only gameplay-facing HUD elements like title, score/time, parcel progress, lives, damage, and jetpack state
- authored tutorial/message prompts now use the single-owner gameplay tip path instead of the older debug footer/banner scaffolding or the earlier custom `Turbo` dialogue card, and the common tutorial row-event guidance now behaves like interactive `cRTip`-style prompts with an `OK` button instead of passive banners
- logical tutorial/message row entry now comes from a runner-owned row-message token instead of frontend segment-sync, so prompt/audio dispatch follows live gameplay row ownership more closely than the older app-side helper path
- tutorial mode now also draws the real `Objects/Barrier` side-rail object from the archive instead of only relying on generic edge/fringe visuals
- tutorial `VOICE/TUT*.OGG` samples now play on a dedicated voice channel, separate from gameplay effect sounds and the debug audio-preview path
- tutorial tips no longer tick down while hidden under pause/overlay; they resume when gameplay is visible again instead of expiring under menus
- the tutorial startup prompt now goes through the same shared type-20 prompt/widget layout path as the other tutorial prompts instead of a custom HUD text path

Still missing or approximate:

- the remaining Windows `cameraman` lift/attachment semantics beyond the current roll-order port
- the exact gameplay roles of the two `build_snail_hotspots` source matrices beyond the currently consumed `12/17/18` camera slots
- any still-missing `cRCutScene::AI()` branches outside the now-ported intro `1 -> 2 -> 8 -> 9`, completion `5 -> 6 -> 7`, and death `10 -> 11 -> 12` lanes
- the exact gameplay model anchor/orientation and the rest of Turbo's state-specific animation switching beyond the current gameplay/talk split
- the original row-event/tip actor/controller and payload-table path that own tutorial dialogue timing and presentation beyond the now-runner-owned row-message entry
- the exact owner/update semantics for `cRBarrier`; the current tutorial barrier pass now uses the real barrier mesh, fixed `y = 0.4`, and an owner-like forward anchor from live gameplay `z`, but it still does not port the original owner object or render mode `7`

Best next work:

- keep the attachment-driven camera path aligned with the same pose data gameplay uses
- tighten the remaining unresolved hotspot/source-matrix roles and attachment-exit semantics now that the override camera lives on the runner instead of in app-side helpers

## Hazards, Pickups, Parcels, And Score Events

Status: `partial`

Implemented now:

- deterministic parcel, ring, health, jetpack, slug, garbage, and salt gameplay counters
- authored and ambient garbage/salt seeding into an 8-row live strip
- row-event and prompt metadata surface into the default level path
- live gameplay now renders visible tutorial/runtime actors for slug, garbage, salt, health, jetpack, rings/powerups, parcels, and `=` turret rows instead of leaving them as logic-only counters or debug markers
- salt now uses the shipped `X/SALT.X2` model path through a slot-owned runtime transform, while garbage keeps the recovered sprite-based asset split but now renders from its live runtime slot instead of a static row billboard
- Turbo now carries visible gameplay weapon channels and an invincible shell using the shipped `BLASTERTOP`, `BLASTERLEFT`, `BLASTERRIGHT`, `LASERLEFT`, `LASERRIGHT`, `ROCKETLAUNCHER`, `ROCKET`, and `INVINCIBLE` model families
- gameplay now plays dedicated tutorial/combat SFX for weapon fire, pickups, invincible/slow powerups, explosive rings, and basic impact feedback instead of leaving those moments silent apart from segment voice samples
- weapon fire now uses the recovered multi-sound families (`TurboFire1/2`, `Laser1/2/3`, `Rocket1/2/3`), the recovered `movement_flags`-driven channel layout, and the native 3-shot turbo spread plus laser/rocket speed ratios instead of one fixed shot sound or fire pattern per coarse weapon tier
- weapon fire cadence now follows the native selector-owned cooldown lane, including the startup cooldown reseed window, explicit live press-vs-held input lanes, the slower fresh-press delay, faster held-repeat cadence, the runtime fire feature flag, replay raw-bit gating, and attachment-exit suppression instead of the old coarse `4/7` tick gate
- ring and collision pickup audio now uses the recovered native ring-kind ladder for `1`, `2/6`, `3/7`, and `4/5/8`, so `PW1`, `PW1..PW7`, `SLOWRING`, `EXPLODERING`, and the `Powerup` voice no longer all key from generic pickup progression
- native runtime ring kinds `3/7` no longer reuse the long authored slow-timer status; collision now seeds the recovered backward `velocity.z = -0.1` shove and short zero-crossing recovery from `update_subgoldy` before handing motion back to the current forward-speed scaffold
- weapon upgrades now play the recovered shared select/change cue instead of changing tiers silently
- explosive rings now clear nearby garbage and defeat nearby slugs instead of staying score-only scaffolding
- projectile fire now stops on salt without consuming it, so the tutorial “avoid salt” rule is no longer contradicted by the current port
- `=` rows now act as visible lethal turret obstacles with per-row fire state and short `BLASTERTOP-FIRE` flashes instead of invisible debug-only tiles or one shared timer
- garbage collisions now apply the recovered hazard-to-player direction vector, the native invincible motion guard, and a decaying track-mode `velocity.x` shove instead of only incrementing damage/score, and the garbage slot now survives into a visible burst state after contact
- garbage and salt aftermath now spawn from the hazard positions instead of the player position, so tutorial combat feedback is no longer centered on Turbo when those hazards are hit
- postal bonus now lands on the final parcel event instead of being delayed to a generic end-of-run fallback
- challenge runtime parcel targeting now comes from the live preview path instead of the dead `Parcels:` metadata lane, and challenge loads prune the active parcel annotations down to the recovered speed/difficulty target using the shared gameplay RNG lane seeded after track build
- parcel pickup no longer consumes authored row annotations directly; the runner now matches `handle_subgoldy_collisions` by collecting only from the live 50-slot parcel runtime with the recovered `delta_z < 1.0` and normalized-distance `< 1.24` checks
- health and jetpack pickup no longer consume authored rows directly; the runner now keeps live runtime pickup slots, renders those slots instead of static row billboards, and resolves collection from the recovered `handle_subgoldy_collisions` distance gates before exact row crossing
- health pickup presentation now follows the recovered runtime slot phase lane instead of staying static: the live sprite bobs with the native `phase += 1/60` and `base_y + (sin(phase * tau) + 1.0) * 0.3` update, while collision still reads the slot's base world position
- jetpack pickup spawn now uses the recovered ramp-side lateral bias from `spawn_track_jetpack_pickup` instead of always centering on the source cell
- ring and special-effect pickups no longer resolve from `processRow()` row traversal; the runner now keeps live runtime ring slots, renders those slots instead of static runtime-handled ring billboards, resolves collection from the recovered `handle_subgoldy_collisions` `delta_z < 1.0` and normalized-distance `< 0.98` gate before exact row crossing, keeps the recovered post-hit `2 -> 3` collapse lane alive instead of deleting the slot immediately, and now constrains that bank to the native `2` live slots instead of a widened port-only pool
- health pickup no longer lands silently; the app now uses the shared `SMOKE.TGA` effect lane with the recovered `health_collect_particles` packet shape: 8 world-axis burst velocities, the live runner-motion carryover, the native pink tint, the `0.1 x 0.5` sprite size, and the small downward drift
- parcel pickup no longer collapses directly into parcel delivery score/count; collected parcels now stay inside the live runtime slot for the recovered `state 4/5` home leg, and the row-event controller now stages a fresh `state 6/7` delivery parcel before `parcel_register` lands
- parcel delivery state `7` now homes to the controller-owned `row_event_display.widget_world` anchor using the recovered local offset `(right=7.3, up=2.0, forward=6.0)` without the older camera fallback, and seeds the shipped per-flight arc coefficients from the carried gameplay LCG instead of the old fixed `{0, 1, 0}` offset
- parcel runtime states `4/5/6/7` now reuse a cached game-owned home anchor instead of resampling the live player position during flight, which matches the current recovered native consumer shape more closely than the old player-anchor shortcut
- parcel runtime states `4` and `6` now fall through into their flight updates on the same tick like `update_track_parcel`, parcel rendering now keeps the recovered sprite-only presentation position/scale separate from the base parcel world position during states `5` and `7`, and the home-flight arc now lifts along the live `basis_up` vector instead of hard-coding world `y`
- collected parcel rows now stay consumed across respawn and stop rendering as live world pickups instead of reappearing until the row scrolls away
- visible world parcels now come from a runner-local 50-slot live runtime scaffold with the shipped state-`1` bobbing and expiry rules instead of static annotation billboards
- the visible parcel-progress counter now advances on pickup like `handle_subgoldy_collisions`, while the live parcel-flight controller owns register score payout and the final postal bonus
- parcel register score and the final-delivery handoff no longer hang off loose runner fields; the port now keeps a runner-local `row_event_display` controller with the recovered target, delivered-count, bonus, and state lanes, including live `staging`, `hold`, `final_delivery_delay`, and the proven `state 3 -> 4 -> 5` finish path
- row-event bonus-prompt completion no longer keys off the authored `'_'` proxy; gameplay now consumes the recovered `TrackRowCell.flags_b & 0x40` lane rebuilt on the preview from the shipped cell-population and `CondenseTrack` follower-clear pass instead of the older "any populated tile" shortcut
- route-end completion now arms from a dedicated `course_end_threshold` field seeded more like the Windows builder: non-random level previews use the recovered start of the final `Last:` block from `populate_runtime_track_cells_from_segments`, and random challenge-style previews now build a seeded middle strip using the recovered `floor((difficulty * 0.65 + 0.35) * Length) - last_block_len` target, challenge candidate-pool scalar, and segment-overrun extension instead of concatenating every candidate
- route-end completion can now arm while a collected parcel is still in flight, but the runner-local completion handoff no longer returns early; it waits for the row-event controller to settle before the app-level completion bridge fires
- completion handoff no longer collapses straight into one delayed app return; the runner now emits an early completion-screen init handoff once cutscene state `6` is active, then keeps the recovered `2.0s` voice / `5s` finalize controller alive until the late frontend exit can fire
- completion camera no longer uses the older handcrafted anchor formulas; the override lane now rebuilds the camera-relevant hotspots through the recovered source-matrix split, snaps intro onto hotspot `18`, uses the recovered `12 -> 18` completion blend lane, and keeps spare-life death converging toward hotspot `18` instead of forcing hotspot `17`
- partial `ScoreAdd`-based totals instead of the older penalty-only fallback score

Still missing or approximate:

- the original mode gates for ambient spawns and any remaining non-horizontal suppressor details
- the recovered horizontal neighbor gate is now ported for generic garbage fallback spawns (`0x01/0x15` only spawn when immediate left/right runtime tiles stay inside the native allowed set `0x01/0x14/0x15/0x20`)
- literal native ownership for the now-present SubLazer projectile pool (`cRSubLazerManager` @ `game + 0x356b00`, 20 slots stride 0xb0, fired by Wall2 AI via `shoot_subgoldy` for the `+0.02` damage lane) — historically misnamed "Wall2 ambient pool" in these docs; the Wall2 tile is the *emitter*, the slots themselves are projectiles
- the broader native forward-speed controller behind `Player.velocity.z` once negative-velocity rings or garbage hits hand control back, plus the still-unported attachment-follow consumers of that same velocity block
- exact actor ownership, animation/state switching, turret-specific controller behavior, and any non-billboarded object/model presentation the original runtime uses
- the remaining dedicated health-collect sprite-bod ownership and the surrounding `cRSubHover` behavior beyond the now-ported ramp-bias spawn lane and `JETPACKTHRUST` pre-warning visual channel
- original combat VFX ownership/presentation beyond the current placeholder explosion/goo billboards, including the exact pre-hit ring bod anchor/layout and child orbit packet
- the exact input-controller bit source behind `gate_18`; the port now arms the row-event confirm gate from gameplay confirm input and preserves the late completion fast-forward lane, but the original controller-owner split is still not named literally
- exact parcel flight/runtime-object behavior, especially row-event widget ownership before the recovered target offset is computed and the remaining timing details
- missing score events tied to replay, jetpack, slug kills, and other unresolved gameplay branches

Best next work:

- keep porting spawn/collision behavior through the gameplay runtime, not the viewer
- avoid treating UI score presentation as proof that the underlying runtime event is already ported

## Damage Gauge, Jetpack, And Lives

Status: `partial`

Implemented now:

- separate damage and jetpack controllers on the Zig side, matching the current Windows split
- native-shaped damage-gauge display fill, pulse, warning-transition, and drain behavior
- runner-owned warning actor cadence and `sfx 50` loop ownership instead of the old app-side `1.0s` timer
- shipped `DamageGuage`, `DamageGuageFull`, `DamageGuageBright`, and `Warning` HUD art in live gameplay instead of the old generic gauge block
- slug first-hit vs repeated-hit split
- visible life seed `3`, bonus-life thresholds, and runner-owned Postal respawn consumption in the death/resurrect path
- dedicated HUD damage gauge and postal life strip
- jetpack countdown, warning band, `JetPack=Off` runtime warning snap from the recovered `flags_b & 0x80` lane, route-end shutoff, and gameplay HUD presentation

Still missing or approximate:

- the remaining global-flag exits and `stop_warning_sample` handle semantics from `update_damage_gauge`
- remaining hazard deltas and presentation details
- full death/fall timing around these controllers

Best next work:

- keep these controllers separate in code and docs
- only pull in more presentation work once the underlying runtime branch is actually understood

## Completion, Death, Respawn, And The Outer Bridge

Status: `partial`

Implemented now:

- distinct respawn vs final-loss handoffs
- postal completion no longer blindly inserts an arcade high score on every route clear
- successful completion is now split into an early in-level completion overlay init and a later finalize transition into the full completion screen
- lives are now consumed inside the runner's respawn branch before the app rebuild, matching the recovered `update_subgoldy_resurrect` ownership better than the old app-side decrement
- respawn now stores the direct `0x1c` rebuild selector as authoritative bridge state and uses the shared rebuild effect endpoint only to restore the saved owner after the rebuild finishes
- final postal completion no longer fakes a normal Star Map return; it now routes through the recovered `BACKGROUNDS/SPLASH.TXT` Thanks For Playing owner with the shipped three-message sequence before handing off into the credits crawl
- the outer bridge opcodes are now narrowed more concretely:
  - `26`: destroy subgame, then jump to the saved outer owner without reinitializing subgame
  - `27`: destroy subgame, reinitialize subgame, then jump to the saved outer owner
  - `28`: destroy subgame, clear `replay_active`, reinitialize subgame, then jump to the saved outer owner
  - `29/30`: Thanks For Playing owner init and update; `uninit_thanks_screen` then writes state `0x0e`, the credits-screen init lane
- BN disassembly now confirms the bridge destination is a dedicated front-end controller slot (`update_frontend_state_machine` reads active state from `[controller + 0x94]` and the bridge jump target from `[controller + 0x98]`)
- a whole-image BN instruction sweep plus a checked-in IDA export disambiguated the saved-owner (`+0x1bc`) writer set: the post-run branches at `update_subgame` `0x439994`/`0x4399b2` preserve `+0x1b8` into `+0x1bc` before forcing state `0x1a`/`0x1b`; `update_subgame` state `2` at boot only sets active state `+0x1b8 = 2` and does not touch `+0x1bc`. Known direct `+0x1bc` writers: `destroy_subgame` (→`0x12`), the two `update_subgame` post-run preserve ops, six sites in `update_subgoldy`, four in `update_subgoldy_resurrect`. `update_pause_menu`, `update_completion_screen`, `add_arcade_high_score`, `add_survival_high_score`, `update_high_score_screen`, and `exit_high_score_screen` write only `+0x1b8` (active state) plus their own local scratch
- the older "saved-owner writer unresolved" claim is now too broad; the remaining gap is narrower:
  - `update_new_game_menu`, `update_main_menu`, `update_high_score_screen`, and `exit_high_score_screen` still do not expose a direct saved-owner store
  - the open question is which other helper-driven producers, if any, seed different saved owners before `26/27/28` outside the now-confirmed gameplay-side writers
- BN plus IDA now also sharpen the selected-record bridge inputs:
  - `update_galaxy` and `update_challenge_setup_screen` seed `selected_level_record_active = 1` and the selected-record pointer, but do not show a matching write to `selected_level_record_persistent`
  - the challenge setup pointer is the game-local challenge setup replay mirror at `game + 0xfb3050`, not the visible challenge score table; the port mirrors that with a separate `challenge_setup_replay` slot populated by challenge score commits
  - `initialize_subgame`, `update_subgame`, `build_subgame_level`, and `destroy_subgame` all treat `selected_level_record_persistent` as a separate lifecycle lane that survives rebuild state `7` and is cleared on teardown
- BN plus IDA also now expose a separate app-side replay-launch scratch lane that is not the same as the transient selected-record path:
  - `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch both seed `app + 0x1066bec`, `+0x1066be8`, `+0x1066be9`, `+0x1066bf0`, and `+119190` before jumping to frontend state `10`
  - `update_frontend_state_machine` initializes subgame at `data_4df904 + 0x74618`, so that app-side scratch aliases `game + 0xff25d0/+0xff25d1/+0xff25d4/+0xff25d8` directly instead of feeding a later copy step
  - `initialize_click_start`, `update_pause_menu`, and `update_completion_screen` all consume those same app fields later, which means the native saved-replay launch path already has an app-owned control lane
  - whole-image disassembly still shows no direct nonzero store to `game + 0xff25d1`; the only direct store is the teardown clear in `destroy_subgame`, because the nonzero launch-side writer reaches the same byte through the overlapping app-base address
  - app dword `+0x12e55e0` is now narrowed beyond simple false-lead rejection: it lines up with the subgame-side rebuild selector at `game + 0x1270fc8`, where selector `1` is the postal post-completion reopen and selector `2` is the ordinary rebuild/start lane used by `update_new_game_menu` `Postal Mode`, `exit_high_score_screen`, and transient pause-abandon flow
- BN plus IDA now also narrow the New Game replay attract lane further: `update_new_game_menu` rotates a menu-local cursor through `0..4`, but only cursor values `0/1/3` probe replay banks and seed the persistent scratch, mapping those lanes to postal / challenge / completion with `app + 0x74658 = 0/1/4` before state `10`; the direct `Postal Mode` button is separate and also writes selector `2`, while Challenge/Time Trial direct buttons stay on the ordinary state-`10` lane without touching replay scratch; `initialize_game_assets_and_world` clears the launch bits `+0x1066be8/+0x1066be9` at startup, `initialize_subgoldy` unconditionally creates the click-start owner, `initialize_click_start` hides its prompt when `+0x1066be8` is already set, and `update_subgame` later consumes `data_4df904 + 0x4f2e4` to clear the menu-local hide latch once that accumulator exceeds `1.0`; the menu-local controller now has a clearer partial layout (`cursor`, likely hide latch, secondary startup suppressor timer, attract accumulator/step). BN static inspection shows the attract step at `+0x14` is zero in the shipped image and has no direct absolute xrefs outside the `update_new_game_menu` read, so the port models that branch as dormant instead of seeding an invented timer; the remaining gap is the updater or reseed path for the `+0x8/+0xc` suppressor lane
- the current Zig bridge now mirrors more of that launch lane explicitly: replay rebuild targets carry `source`, `persistent`, and saved return-owner state together, and the app-side replay context now stores the raw native saved owner (`0x12` high-score / `2` New Game) instead of only a reconstructed high-level target, so persistent replay returns no longer have to be inferred from `SelectedLevelRecordSource` alone
- the port now follows the confirmed `26 -> 2` New Game return for tutorial completion and ordinary postal final loss instead of forcing those exits through the main menu
- persistent replay-backed pause abort now follows the same launch-surface destroy-return lane as persistent result-screen exits instead of reusing the respawn-only clear-replay rebuild opcode
- transient route-map best-trial pause abandon now also follows the native rebuild lane instead of the respawn-only clear-replay opcode: BN `update_pause_menu` falls through to completion state `2` when the persistent byte is clear, BN plus IDA `update_completion_screen` then destroy subgame and reinitialize it directly for `level_mode == 4`, and `initialize_subgame` rebuilds the galaxy owner from the preserved continuation selector
- replay-backed result exits no longer use opcode `28`; the current port now keeps the recovered split: high-score replay rows launch the persistent `0x1a` destroy-return lane, while route-map best-trial launches stay on the transient `0x1b` rebuild-return lane
- selected replay marker bit `0x8` no longer shortcuts straight back to the launch UI in the port: BN plus IDA now show `update_subgoldy` consuming that sample bit directly, writing `state 0x1a`, saving owner `10`, setting app byte `+0x30c = 1`, and starting the front-end fade, so the current port now restarts the active selected replay through the explicit destroy-return lane instead
- transient postal selected-record final loss now also follows the native `0x1a -> owner 2` New Game override: `complete_subgame` never arms app byte `+0x30d` while `selected_level_record_active` is set, so the postal replay-loss leg does not return through the postal high-score screen
- ordinary non-selected postal final loss is now also pinned: BN plus IDA show `update_subgoldy_resurrect` only keeps postal mode on `0x1b` while app byte `+0x30d` is still armed by the post-level high-score continuation lane, and otherwise overwrites the saved owner with `2` before forcing `0x1a`
- ordinary non-selected challenge and Time Trial failed-result exits no longer fall back to the main menu in the port: `update_subgoldy_resurrect` uses state `0x1b` for those non-postal failures, `update_frontend_state_machine` rebuilds subgame on that lane, and `initialize_subgame` then routes `level_mode == 1` back into `initialize_challenge_setup_screen` and `level_mode == 4` back into `initialize_galaxy`
- the current Zig bridge now exposes the recovered challenge-side owner as a literal challenge-setup controller, while Time Trial still maps the same rebuild lane onto the replay Star Map abstraction
- the port now keeps one explicit outer-bridge transition lane with native opcode names (`26/27/28/29`) plus explicit saved-owner, saved-replay-return, and respawn rebuild state on `AppState`, so completion, respawn, final-loss, replay-backed abandon, and replay-backed result exits all dispatch through one shared boundary instead of separate helper branches
- `initialize_subgame` plus `update_subgame` now also pin `level_mode == 7` as tutorial mode, so the special `0x1a -> owner 2` completion override is no longer a separate bridge unknown; it is the same tutorial-completion lane the port already uses
- ordinary pause-menu abandon now also stages the shared postal/challenge high-score entry path when the current partial score places, which matches the confirmed `update_completion_screen` case-`2` `complete_subgame(..., 1)` side effect better than the older direct-return shortcut
- BN plus IDA now also pin the post-entry return owner for that ordinary abandon lane: `add_arcade_high_score` / `add_survival_high_score` arm state `20`, `update_high_score_screen` later exits through `exit_high_score_screen`, and that helper returns by surviving run mode (`state 2` for postal, `state 10` for challenge) instead of by the preserved gameplay launch surface; the current Zig port now mirrors that with `New Game -> Postal Mode` plus the literal challenge-setup owner
- ordinary postal/challenge failed-result score entry now also captures that later return owner up front once the post-level high-score screen takes over, which matches the recovered `complete_subgame -> add_*_high_score -> saved owner 0x14 -> state 0x1b` bridge shape better than keeping the completion-screen result object live through name entry

Still missing or approximate:

- the full outer subgame controller that owns rebuild/teardown/return beyond the current owner-driven transition state
- the full set and exact semantics of the saved outer-owner writers behind the `26/27/28` bridge jump outside the now-confirmed selected-record startup, completion/failure, and respawn lanes
- exact replay-sensitive failure routing beyond the currently recovered transient `0x1b` selected-record completion lane and persistent `0x1a` lane in `update_subgoldy` / `update_subgoldy_resurrect`
- the remaining owner/controller details around the Windows completion overlay and post-overlay bridge

Best next work:

- port the outer subgame/frontend bridge before doing more local runner-phase surgery
- treat `26/27/28` as bridge opcodes and `29/30` as the post-run Thanks For Playing owner instead of folding them into a generic completion screen
- treat this as the biggest remaining gameplay architecture gap outside attachment follow

## Replay

Status: `partial`

Implemented now:

- enough score/config structure to preserve replay-bearing records
- route-map and high-score UI have the right broad replay concepts in place
- selected replay actions now launch the recovered selected-record families instead of one source-derived return path: route-map best-trial stays transient, while persistent replay launches carry their own saved return owner
- high-score replay rows are available for both native score banks: postal replay labels use the recovered `+125` x anchor and challenge replay labels use `+170`
- replay-backed rebuilds now reuse the compact record's saved mode, route index, runtime build flags, build seed, challenge tuning, and ambient hazard scalars
- selected replay runs now preserve the exact saved score entry as a live replay source, decode the compact secondary lane once into a runner-facing cache, and feed those replay samples into gameplay instead of dropping the payload on launch
- replay playback now consumes the recovered lateral `i16` lane as direct world-`x` motion and suppresses live steering/fire input while a selected-record replay is active
- replay flag bits `0x1/0x2` now drive the grounded replay-latch movement-progress substitutions instead of being preserved as dead metadata during selected playback
- selected replay sessions no longer feed completion or failure back into live high-score persistence; result exits still route through the recovered launch-surface bridge split instead of mutating score state in place
- replay bridge payloads now preserve explicit launch context (`source`, persistent lane, return owner) across destroy/rebuild returns instead of reconstructing that state from the source enum alone
- replay flag bit `0x8` now routes selected playback through the native destroy-return replay restart lane (`state 0x1a -> saved owner 10`) instead of swapping phases immediately, running past the sample stream, or jumping straight back to the launch surface
- the recovered New Game replay attract bank split is now pinned in the port's bridge expectations too: postal, challenge, and completion-backed launches all map their persistent return owner back onto the matching `New Game` lane instead of reusing a source-derived high-score or route-map fallback

Still missing or approximate:

- the New Game replay attract launcher is now exposed in Zig for bank probe/launch/saved-owner return ownership, but it remains dormant because the shipped menu-local attract step is zero and no static writer has been recovered
- the saved secondary-lane payload still only has neutral decode/plumbing; it does not yet drive a grounded gameplay consumer
- replay flag bits `0x1/0x2` still do not drive a grounded audio/effect parity path beyond those recovered movement-progress substitutions
- full replay payload read/write parity

Best next work:

- keep replay UI explicitly partial
- do not overfit score/config behavior to fake replay support

## Debug Tooling

Status: `debug`

Implemented now:

- split debug browser with standalone `Segments` mode
- compact overlays instead of the older giant opaque side panels
- raw/game render toggle, grid toggle, overlay toggle, track-set toggle, and attachment overlay toggle
- segment viewer is now a real sandbox for path families and textured track rendering

Still missing or approximate:

- no real pause-free “shipping” debug/storyboard around this browser
- segment viewer still skips some Windows render-normalization passes

Best next work:

- keep using the segment viewer as the proving ground for render/path families
- avoid turning debug conveniences into hidden gameplay dependencies

## Highest-Value Next Tasks

If work resumes from this page alone, the best current order is:

1. Finish attachment exit retirement and the remaining family-specific entry/exit behavior against built geometry.
2. Port more of the outer subgame/frontend bridge (`26/27/28/29`, completion vs final-loss vs respawn ownership).
3. Recover the remaining track render-normalization passes (`mark_track_warning_zones`, fringe solidity, directional fringe ownership).
4. Revisit nonlinear kind-`42` family semantics once there is enough evidence to separate `HALFPIPE`, `WARP`, and any sibling families more cleanly.
