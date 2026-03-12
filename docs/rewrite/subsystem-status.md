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
- preserve opaque compact-record tails for loaded entries instead of flattening everything to header-only rewrites
- inline name-entry flow inside the shared high-score screen

Still missing or approximate:

- full replay payload synthesis for new or replaced score entries
- exact meanings of many compact-record fields
- full runtime parity for replay-bearing score writes

Best next work:

- keep preserving unknown compact-record data
- avoid inventing replay-capable save records until the full replay serializer is understood

## Track Build And Runtime Grid

Status: `partial`

Implemented now:

- parse `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- preserve row annotations like `Path`, `Parcel`, `3DModel`, `JetPack=Off`, `NoFall`, `Sample`, and `Message`
- rebuild a normalized runtime grid with the current known runtime tile families and floor-height sampling
- reuse the recovered gameplay build preset `0x00f5cfff`
- derive a first installed attachment-row map from runtime attachment tiles for gameplay/template entry

Still missing or approximate:

- the exact Windows installed attachment bank and owner-record installer
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
- the normal gameplay path no longer renders the old debug HUD shell; it now keeps only gameplay-facing HUD elements like title, score/time, parcel progress, lives, damage, and jetpack state
- authored tutorial/message prompts now use compact stacked gameplay tip cards, with up to three timed entries active at once instead of the old footer debug text block or the earlier invented Turbo speaker panel
- tutorial mode now also draws the real `Objects/Barrier` side-rail object from the archive instead of only relying on generic edge/fringe visuals

Still missing or approximate:

- the full Windows `cameraman` controller
- full cutscene camera ownership and transition behavior
- exact completion/death cutscene handoff
- the exact gameplay model anchor/orientation and state-specific animation switching for Turbo
- the original row-event/tip actor/controller that owns tutorial dialogue timing and presentation
- the exact owner/update semantics for `cRBarrier`; the current tutorial barrier pass uses the real barrier mesh plus the recovered fixed height, but still anchors it conservatively from the live track row instead of the original owner/update path

Best next work:

- keep the attachment-driven camera path aligned with the same pose data gameplay uses
- revisit the broader cameraman/cutscene split once the outer subgame bridge is ported

## Hazards, Pickups, Parcels, And Score Events

Status: `partial`

Implemented now:

- deterministic parcel, ring, health, jetpack, slug, garbage, and salt gameplay counters
- authored and ambient garbage/salt seeding into an 8-row live strip
- row-event and prompt metadata surface into the default level path
- live gameplay now renders visible tutorial/runtime actors for slug, garbage, salt, health, jetpack, rings/powerups, and parcels instead of leaving them as logic-only counters or debug markers
- postal bonus now lands on the final parcel event instead of being delayed to a generic end-of-run fallback
- partial `ScoreAdd`-based totals instead of the older penalty-only fallback score

Still missing or approximate:

- the original suppressor bits and neighbor/mode gates for ambient spawns
- the `Wall2` `+0.02` ambient pool
- exact actor ownership, animation/state switching, and any non-billboarded object/model presentation the original runtime uses
- parcel flight/runtime-object behavior and timing
- missing score events tied to replay, jetpack, slug kills, and other unresolved gameplay branches

Best next work:

- keep porting spawn/collision behavior through the gameplay runtime, not the viewer
- avoid treating UI score presentation as proof that the underlying runtime event is already ported

## Damage Gauge, Jetpack, And Lives

Status: `partial`

Implemented now:

- separate damage and jetpack controllers on the Zig side, matching the current Windows split
- damage-gauge fill, warning, and drain behavior on the right general path
- slug first-hit vs repeated-hit split
- visible life seed `3`, bonus-life thresholds, and postal-only consumption rules
- dedicated HUD damage gauge and postal life strip
- jetpack countdown, warning band, route-end shutoff, and gameplay HUD presentation

Still missing or approximate:

- exact warning actor presentation and remaining sprite-driven behavior
- runtime-cell `0x80` jetpack warning/shutoff branch
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
- lives are consumed at respawn rebuild commit time instead of during the earlier runner-local phase
- app-level reload is closer to the Windows rebuild split than the old hidden in-place runner reset

Still missing or approximate:

- the real frontend bridge around Windows states `26/27/28/29/30`
- the outer subgame controller that owns rebuild/teardown/return
- exact final-loss and replay-sensitive return routing
- completion overlay ownership that matches the Windows cutscene path instead of the current simplified screen routing

Best next work:

- port the outer subgame/frontend bridge before doing more local runner-phase surgery
- treat `26/27/28` as bridge opcodes and `29/30` as the post-run Thanks For Playing owner instead of folding them into a generic completion screen
- treat this as the biggest remaining gameplay architecture gap outside attachment follow

## Replay

Status: `scaffold`

Implemented now:

- enough score/config structure to preserve replay-bearing records
- route-map and high-score UI have the right broad replay concepts in place

Still missing or approximate:

- actual replay launch in route map
- actual replay launch in high scores
- the replay-backed rebuild path
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
