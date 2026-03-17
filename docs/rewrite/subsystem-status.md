# Subsystem Status

This page is the detailed working tracker for the Zig port.

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
- main menu, new-game menu, help, options, route map, high-score screen, pause overlay, and a shared exit prompt
- direct menu transitions for the paths the Windows code handles directly, instead of forcing everything through the black overlay
- route-map post-completion mode with the special `Exit` label and locked-open selected route behavior

Still missing or approximate:

- owner-specific exit-prompt layouts beyond the currently recovered menu and route-map cases
- remaining pause-menu ownership details
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
- simple fringe skirts and back plane

Still missing or approximate:

- `select_track_tile_edge_variants`
- `promote_track_tiles_to_fringe_variants`
- `harmonize_center_lane_floor_slide_variants`
- `merge_track_tile_runs` beyond the currently ported conservative ownership slice
- `mark_track_warning_zones`
- real directional fringe objects and cache families
  - the underlying Windows pool is clearer now: `initialize_fringe_manager` + `allocate_fringe_object`
- exact warn-family routing

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
- natural-end exit now uses template progress and template end pose
- elevated side exits preserve airborne height instead of snapping straight to the floor
- `SUPERTRAMP` has a dedicated launch exit path
- a geometric installed-entry attempt now runs before the old source-row fallback
- source-row installed-entry fallback remains in place for stability where the geometric entry is not yet strong enough

Still missing or approximate:

- full Windows installed runtime bank and owner-record semantics
- the full swept local-frame entry test
- exact family-specific entry/exit behavior for the nonlinear kind-`42` family
- exact side-exit/natural-end return values and post-follow accumulator semantics

Best next work:

- keep tightening entry against built geometry until the old source-row fallback can be removed safely
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
- tutorial mode now also draws the real `Objects/Barrier` side-rail object from the archive instead of only relying on generic edge/fringe visuals
- tutorial `VOICE/TUT*.OGG` samples now play on a dedicated voice channel, separate from gameplay effect sounds and the debug audio-preview path
- tutorial tips no longer tick down while hidden under pause/overlay; they resume when gameplay is visible again instead of expiring under menus
- the tutorial startup prompt now goes through the same shared type-20 prompt/widget layout path as the other tutorial prompts instead of a custom HUD text path

Still missing or approximate:

- the remaining Windows `cameraman` lift/attachment semantics beyond the current roll-order port
- the exact `build_snail_hotspots` source-matrix split beyond the current body-frame approximation for hotspots `12/17/18`
- any still-missing `cRCutScene::AI()` branches outside the now-ported intro `1 -> 2 -> 8 -> 9`, completion `5 -> 6 -> 7`, and death `10 -> 11 -> 12` lanes
- the exact gameplay model anchor/orientation and the rest of Turbo's state-specific animation switching beyond the current gameplay/talk split
- the original row-event/tip actor/controller that owns tutorial dialogue timing and presentation
- the exact owner/update semantics for `cRBarrier`; the current tutorial barrier pass now uses the real barrier mesh, fixed `y = 0.4`, and an owner-like forward anchor from live gameplay `z`, but it still does not port the original owner object or render mode `7`

Best next work:

- keep the attachment-driven camera path aligned with the same pose data gameplay uses
- tighten the remaining cutscene-anchor and attachment-exit semantics now that the override camera lives on the runner instead of in app-side helpers

## Hazards, Pickups, Parcels, And Score Events

Status: `partial`

Implemented now:

- deterministic parcel, ring, health, jetpack, slug, garbage, and salt gameplay counters
- authored and ambient garbage/salt seeding into an 8-row live strip
- row-event and prompt metadata surface into the default level path
- live gameplay now renders visible tutorial/runtime actors for slug, garbage, salt, health, jetpack, rings/powerups, parcels, and `=` turret rows instead of leaving them as logic-only counters or debug markers
- salt now uses the shipped `X/SALT.X2` model path, while slug and garbage still use sprite-based presentation that matches the recovered asset split better than the earlier generic placeholders
- Turbo now carries visible gameplay weapon tiers and an invincible shell using the shipped `BLASTERTOP`, `LASERLEFT`, `LASERRIGHT`, `ROCKETLAUNCHER`, `ROCKET`, and `INVINCIBLE` model families
- gameplay now plays dedicated tutorial/combat SFX for weapon fire, pickups, invincible/slow powerups, explosive rings, and basic impact feedback instead of leaving those moments silent apart from segment voice samples
- weapon fire now uses the recovered multi-sound families (`TurboFire1/2`, `Laser1/2/3`, `Rocket1/2/3`) instead of one fixed shot sound per weapon tier
- weapon upgrades now play the recovered shared select/change cue instead of changing tiers silently
- explosive rings now clear nearby garbage and defeat nearby slugs instead of staying score-only scaffolding
- projectile fire now stops on salt without consuming it, so the tutorial “avoid salt” rule is no longer contradicted by the current port
- `=` rows now act as visible lethal turret obstacles with per-row fire state and short `BLASTERTOP-FIRE` flashes instead of invisible debug-only tiles or one shared timer
- garbage collisions now apply the missing tutorial “Asteroids slow me down” behavior by shaving forward speed and kicking Turbo sideways instead of only incrementing damage/score
- garbage and salt aftermath now spawn from the hazard positions instead of the player position, so tutorial combat feedback is no longer centered on Turbo when those hazards are hit
- postal bonus now lands on the final parcel event instead of being delayed to a generic end-of-run fallback
- challenge runtime parcel targeting now comes from the live preview path instead of the dead `Parcels:` metadata lane, and challenge loads prune the active parcel annotations down to the recovered speed/difficulty target using the shared gameplay RNG lane seeded after track build
- parcel pickup no longer consumes authored row annotations directly; the runner now matches `handle_subgoldy_collisions` by collecting only from the live 50-slot parcel runtime with the recovered `delta_z < 1.0` and normalized-distance `< 1.24` checks
- parcel pickup no longer collapses directly into parcel delivery score/count; collected parcels now stay inside the live runtime slot for the recovered `state 4/5` home leg, and the row-event controller now stages a fresh `state 6/7` delivery parcel before `parcel_register` lands
- parcel delivery state `7` now homes to the controller-owned `row_event_display.widget_world` anchor using the recovered local offset `(right=7.3, up=2.0, forward=6.0)` without the older camera fallback, and seeds the shipped per-flight arc coefficients from the carried gameplay LCG instead of the old fixed `{0, 1, 0}` offset
- parcel runtime states `4/5/6/7` now reuse a cached game-owned home anchor instead of resampling the live player position during flight, which matches the current recovered native consumer shape more closely than the old player-anchor shortcut
- parcel runtime states `4` and `6` now fall through into their flight updates on the same tick like `update_track_parcel`, parcel rendering now keeps the recovered sprite-only presentation position/scale separate from the base parcel world position during states `5` and `7`, and the home-flight arc now lifts along the live `basis_up` vector instead of hard-coding world `y`
- collected parcel rows now stay consumed across respawn and stop rendering as live world pickups instead of reappearing until the row scrolls away
- visible world parcels now come from a runner-local 50-slot live runtime scaffold with the shipped state-`1` bobbing and expiry rules instead of static annotation billboards
- the visible parcel-progress counter now advances on pickup like `handle_subgoldy_collisions`, while the live parcel-flight controller owns register score payout and the final postal bonus
- parcel register score and the final-delivery handoff no longer hang off loose runner fields; the port now keeps a runner-local `row_event_display` controller with the recovered target, delivered-count, bonus, and state lanes, including live `staging`, `hold`, `final_delivery_delay`, and the proven `state 3 -> 4 -> 5` finish path
- row-event bonus-prompt completion no longer keys off the authored `'_'` proxy; gameplay now consumes the recovered `TrackRowCell.flags_b & 0x40` lane rebuilt on the preview from the shipped cell-population and `CondenseTrack` follower-clear pass instead of the older "any populated tile" shortcut
- route-end completion can now arm from a dedicated `course_end_threshold` field instead of only the older final-row heuristic; the current producer is still provisional, so the preview seeds that field from a last-row fallback until the native source is recovered
- route-end completion can now arm while a collected parcel is still in flight, but the runner-local completion handoff no longer returns early; it waits for the row-event controller to settle before the app-level completion bridge fires
- completion handoff no longer collapses straight into one delayed app return; the runner now emits an early completion-screen init handoff once cutscene state `6` is active, then keeps the recovered `2.5s` voice / `5s` finalize controller alive until the late frontend exit can fire
- completion camera no longer uses the older handcrafted anchor formulas; the override lane now rebuilds world hotspots from the live body frame, snaps intro onto hotspot `18`, uses the recovered `12 -> 18` completion blend lane, and keeps spare-life death converging toward hotspot `18` instead of forcing hotspot `17`
- partial `ScoreAdd`-based totals instead of the older penalty-only fallback score

Still missing or approximate:

- the original suppressor bits and neighbor/mode gates for ambient spawns
- the `Wall2` `+0.02` ambient pool
- exact actor ownership, animation/state switching, turret-specific controller behavior, and any non-billboarded object/model presentation the original runtime uses
- original combat VFX ownership/presentation beyond the current placeholder explosion/goo billboards
- the unresolved `gate_18` writer path that Windows uses to snap the late completion handoff forward before the row-event controller reaches its terminal state
- exact parcel flight/runtime-object behavior, especially row-event widget ownership before the recovered target offset is computed and the remaining timing details
- missing score events tied to replay, jetpack, slug kills, and other unresolved gameplay branches

Best next work:

- keep porting spawn/collision behavior through the gameplay runtime, not the viewer
- avoid treating UI score presentation as proof that the underlying runtime event is already ported

## Damage Gauge, Jetpack, And Lives

Status: `partial`

Implemented now:

- separate damage and jetpack controllers on the Zig side, matching the current Windows split
- damage-gauge fill, warning, and drain behavior on the right general path
- shipped `DamageGuage`, `DamageGuageFull`, `DamageGuageBright`, and `Warning` HUD art in live gameplay instead of the old generic gauge block
- once-per-second postal warning sound playback while the warning actor is active
- slug first-hit vs repeated-hit split
- visible life seed `3`, bonus-life thresholds, and runner-owned Postal respawn consumption in the death/resurrect path
- dedicated HUD damage gauge and postal life strip
- jetpack countdown, warning band, `JetPack=Off` runtime warning snap from the recovered `flags_b & 0x80` lane, route-end shutoff, and gameplay HUD presentation

Still missing or approximate:

- exact warning owner/controller object behavior beyond the current art/audio presentation
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
- app-level reload is closer to the Windows rebuild split than the old hidden in-place runner reset
- final postal completion no longer fakes a normal Star Map return; it now routes through the recovered `BACKGROUNDS/SPLASH.TXT` Thanks For Playing owner with the shipped three-message sequence before returning to the shell

Still missing or approximate:

- the real frontend bridge around Windows states `26/27/28/29/30`
- the outer subgame controller that owns rebuild/teardown/return
- exact final-loss and replay-sensitive return routing
- the remaining owner/controller details around the Windows completion overlay and post-overlay bridge

Best next work:

- port the outer subgame/frontend bridge before doing more local runner-phase surgery
- treat `26/27/28` as bridge opcodes and `29/30` as the post-run Thanks For Playing owner instead of folding them into a generic completion screen
- treat this as the biggest remaining gameplay architecture gap outside attachment follow

## Replay

Status: `scaffold`

Implemented now:

- enough score/config structure to preserve replay-bearing records
- route-map and high-score UI have the right broad replay concepts in place
- selected replay actions now launch the recovered selected-level-record path instead of dead-end stubs
- replay-backed rebuilds now reuse the compact record's saved mode, route index, runtime build flags, build seed, challenge tuning, and ambient hazard scalars
- selected replay runs now preserve the exact saved score entry as a live replay source, decode the compact secondary lane once into a runner-facing cache, and feed those replay samples into gameplay instead of dropping the payload on launch
- replay playback now consumes the recovered lateral `i16` lane as direct world-`x` motion and suppresses live steering/fire input while a selected-record replay is active
- replay flag bits `0x1/0x2` now drive the grounded replay-latch movement-progress substitutions instead of being preserved as dead metadata during selected playback
- selected replay sessions no longer feed completion or failure back into live high-score persistence, and they now return to the launch surface instead of staying on the generic run-result path
- replay flag bit `0x8` now routes selected playback through the shared fade overlay at the recorded tail instead of swapping phases immediately or letting the sim run past the saved sample stream

Still missing or approximate:

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

1. Finish attachment entry/exit against built geometry and reduce the remaining source-row fallback.
2. Port more of the outer subgame/frontend bridge (`26/27/28/29`, completion vs final-loss vs respawn ownership).
3. Recover the remaining track render-normalization passes (`mark_track_warning_zones`, fringe solidity, directional fringe ownership).
4. Revisit nonlinear kind-`42` family semantics once there is enough evidence to separate `HALFPIPE`, `WARP`, and any sibling families more cleanly.
