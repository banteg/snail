# `build_subgame_level` scratch notes

## Scope

This scratch reconstructs Windows-local
`SubgameRuntime::build_subgame_level(int level_index)` at `0x437eb0` through
the shared `SubgameRuntime` and `GameRoot` owner graphs. Cross-port symbol and
body evidence identifies the authored method as `cRSubGame::StartLevel(int)`,
not `BuildLevel()`.

The source shape was recovered from both decompile exports:

- `analysis/decompile/binja/functions/00437eb0-build_subgame_level.c`
- `analysis/decompile/ida/functions/00437eb0-build_subgame_level.c`

The Binary Ninja export was used mainly for block order. The IDA export was
used for switch cases, exact offsets, and the repeated intrusive-list insertion
shape. Exact or strong neighboring scratches supplied call-signature and
ordering anchors, especially `rebuild_track_runtime_from_segments`,
`initialize_runtime_pools_and_path_template_bank`, `update_subgame`, and
`activate_landscape_entry`.

## Recovered source shape

The accepted candidate models the complete function rather than returning
early after the easier prefix. Its major phases are:

1. Unhide the starfield and select the tutorial score-widget hide state.
2. Pick one of four music files from
   `next_math_random_value() * 0.000122070312f`.
3. Reset enemy, damage-gauge, callback, sub-lazer, salt-hazard, and voice
   systems, then load the frontend level.
4. Apply selected-record replay values or normal-mode speed and difficulty
   defaults.
5. Initialize track parcel slots, honor the score-widget hide latch, and call
   the exact `rebuild_track_runtime_from_segments(level_index)` anchor.
6. Select and activate a landscape, including the four space scripts and the
   random starfield mirror byte.
7. Insert and initialize the start/completion row controllers.
8. Reset subgame latches, release the mouse cursor, and initialize Subgoldy.
9. Insert the player-side render bodies into the active list, initialize the
   slug voice manager, attach its node, update mode-zero HUD text, reset pointer
   positions, and calculate the subgame rate.

The hazard-frequency tail is now typed end to end. `garbage_frequency` and
`salt_frequency` at `SubgameRuntime +0x125ffd8/+0x125ffdc` are normalized from
the embedded level definition's authored `Garbage:`/`Salt:` percentages, or
restored from the selected `SubSolution` for replay. `update_subgame`
consumes the same floats as spawn controls and `complete_subgame` persists
them back into the working record. The typed rewrite preserves the focused
86.10% result (`560/555`, `105` clean operands and the existing table-label
mismatch).

## Source-shape decisions that improved the match

- A single `zero` local remains live from the music switch through later reset
  and list code, matching the native register lifetime better than repeated
  literal zeroes.
- The replay-selected path and normal path remain separate. The mode `0/4/7`
  speed sentinel is compared by its `-1.0f` bit pattern, while mode `1`, mode
  `2`, and mode `3` preserve their distinct conversion paths.
- The two challenge hazard scalars use separate normalized locals. Combining
  the expressions lets MSVC fold the constants to approximately `0.008f`,
  which loses the target's two-stage multiply sequence.
- The completion X/Y sources and default challenge speed are distinct fields in
  the shared `RuntimeConfig`, preserving the saved-config scalar split.
- `rebuild_track_runtime_from_segments(level_index)` stays as a member call and
  is not reimplemented inline.
- The landscape default branch reloads the incoming `level_index` through a
  volatile parameter view. This recovers the native stack reload in the random
  space-landscape switch and removes the old two-byte label drift after the
  track-rebuild call.
- Start/completion row node pointers are scoped to their individual
  `ADDafter` operations. Shortening their lifetimes delayed the EBP save and
  substantially improved the row-controller region.
- The start and completion row zero lanes use volatile stores so VC6 keeps the
  native redundant zero writes before the later position overwrite. The start
  row commits flags before alpha, and the completion row clears the low flags
  byte explicitly; together these keep the row setup closer to the target while
  preserving the later alpha local lifetime.
- The repeated active-list operations are written as explicit intrusive-list
  insertions. Extracting them into a helper changed both code size and register
  allocation.
- The visible-body `0x80` flag update is expressed through the low byte of a
  local flag value. A direct full-word OR was cleaner but shortened the
  candidate to 552 instructions and scored lower.
- 2026-06-20 shared voice-manager header pass: the local one-method
  `VoiceManager` view was replaced with `voice_manager.h`. The focused matcher
  is unchanged at `79.82%`, `555/555`, `177/555` prefix, with the same
  `99 ok / 2 unresolved / 1` masked audit, so this is accepted as a
  call-surface consolidation rather than a source-shape win.
- 2026-06-20 shared subgame runtime header pass: local one-method or prefix
  views for `StarManager`, `GolbPathBank`, `DamageGuage`,
  `SubLazerPool`, `SaltHazardPool`, `SubTracks`,
  `ParcelManager`, `FrontendWidget`, `LandscapeManager`, `BodList`,
  `BodNode`, `MouseCursorState`, and
  `Player::initialize_subgoldy` were replaced by shared headers. The focused
  matcher remains unchanged at `79.82%`, `555/555`, `177/555` prefix; the later
  config-scalar naming pass leaves this at `101 ok / 0 unresolved / 1` in the
  masked audit. The type auditor moved this
  scratch out of the `FrontendWidget`, `Player`, `GolbPathBank`,
  `SubLazerPool`, and `SaltHazardPool` rows.
- 2026-06-21 receiver cleanup: the scratch now defines
  `SubgameRuntime::build_subgame_level` directly and declares the unused-receiver
  `calc_slider_to_rate` call surface on `SubgameRuntime`. Focused Wibo stays at
  `86.10%`, `560/555`, prefix `244/555`, with the same `105 ok / 1 mismatch`
  masked audit. A trial using the standalone `__stdcall calc_slider_to_rate`
  signature regressed to `73.56%`, `557/555`, prefix `62/555`; the caller wants
  the native `mov ecx, esi` receiver setup even though the callee body does not
  consume it. `uv run snail match types --paths` now reports
  `partial-compatible Game: 2`, removing this scratch from the generic owner
  list.
- 2026-07-11 contact-registry correction: the former `GolbPathBank` view at
  `+0x1270fd4` is now the shared fixed-capacity `EnemyManager`, matching
  exact init/search/register helpers and iOS `cREnemyManager`. The focused
  result remains the honest `86.10%`, `560/555`, prefix `244/555`; no surrounding
  scheduling was reshaped to capitalize on the owner rename.

## Remaining differences

The exact prefix now reaches target instruction 244. The first remaining
source-shape difference is in the first row-controller setup: VC6 saves `ebp`
before the volatile zero stores, while native delays `push ebp` until after the
start-row flag load and player pointer materialization.

The largest later mismatch is register allocation in the repeated active-list
tail. The target keeps the player object in EDI and the `0x200` membership flag
in EBP. The candidate instead keeps `0x200` in EDI for the first repeated
insertions. Attempts to force that allocation with typed overlays, earlier
player-pointer declarations, `register`, and named flag locals did not improve
code generation.

The two compiler-generated jump tables are now content-audited. The current
masked-operand pass is clean; the ordinary instruction diff starts with label
drift in the first state dispatch. The former completion-bonus `+0x4` operands
are now resolved to `RuntimeConfig::default_challenge_speed_slider`.

## Rejected trials

| Trial | Measured reason for rejection |
|---|---|
| Combine the challenge scalar expressions | MSVC folded the two multiplies into one constant; prefix and relocation audit regressed. |
| Preinitialize `landscape_index` | Changed switch lowering and reduced the overall score. |
| Remove the landscape index alias before the volatile stack reload | Produced 556 candidate instructions and a lower score in the older 79.82% baseline. |
| Use a typed row-controller overlay | Shortened the exact prefix to 62 instructions and dropped the score to 58.99%. |
| Chain the row zero assignments | Changed scheduling and scored below the explicit stores. |
| Extract active-list insertion into a member or free inline helper | Produced 545 or 556 instructions and scored 61.45% or 75.79%. |
| Make `Player` inherit the list-node view, or keep a persistent typed player pointer | Did not recover the target's EDI/EBP assignment. |
| Replace the low-byte visible flag update with a direct word OR | Produced 552 instructions and a lower full-function score. |
| Earlier completion-row store permutations or alpha integer types | No improvement in the older 79.82% baseline; the retained low-byte clear supersedes those probes. |

## 2026-06-20 landscape and row-lifetime pass

Focused Wibo improves from `79.82%`, `555/555`, `177/555` prefix to `86.10%`,
`560/555`, `244/555` prefix, with `105 ok / 0 unresolved / 1 mismatch` in the
masked audit. The retained changes are:

- stack-reloading the random landscape default from `level_index` and removing
  the old pointer alias;
- volatile zero stores for the start/completion row position lanes;
- storing the start-row flags before the alpha lane; and
- spelling the completion-row flag clear through the low byte.

Rejected follow-ups: keeping the fallback alias was lower at `84.74%`; the
plain stack-reload alone improved prefix but dropped the full score to
`79.64%`; row zeroes without the completion low-byte clear reached only
`81.19%`; and renewed player-node / membership-flag register probes did not move
the active-list tail.

## 2026-07-10 embedded-player ownership pass

- `SubgameRuntime::embedded_player()` now returns the address of the owned
  `Player player` member at `+0x3bb764` without pretending it is heap allocated. The start row,
  completion row, Subgoldy initializer, and voice owner all point at that same
  embedded object.
- The six pre-Player active-list insertions are now spelled as embedded Player
  subobjects: the presentation controller, its three weapon channels, jetpack
  channel, and invincibility shell. These are intrusive list memberships, not
  transfers of ownership to the global BOD list.
- All typed expressions fold back to the original absolute member offsets.
  At that point, focused Wibo remained `86.10%`, `560/555`, prefix `244/555`,
  with `105 ok / 0 unresolved / 1` masked mismatch. Moving the `row_alpha`
  declaration closer to its store was codegen-neutral and was not kept.

## 2026-07-17 active-BOD ownership replay

- `GameRoot + 0x5a8` is now the canonical root-owned `BodList`, with
  `BodNode* first` and `BodNode* free_top`. The older `FrameBodList` analysis
  view had the right size but obscured gameplay ownership behind
  `FrameBodBase*`.
- The seven inlined `BodList::add_bod` sites insert, in order, the jetpack
  channel, three weapon channels, invincibility shell, presentation body, and
  Player body. These are intrusive memberships of embedded objects; the root
  list does not own or allocate any of them.
- Exact BN register identities and IDA definition-address lvars now preserve
  the shared list anchor plus its `list_prev`/`list_next` nodes. Native
  instructions at `0x4383d2..0x43860a` are full-width dword loads/stores; the
  remaining BN byte-lane expressions are a register-alias rendering limit, not
  evidence for partial pointers.
- No scratch source was changed for this pass. The current focused result is
  the honest `77.67%`, `560/555`, prefix `177/555`, with
  `101 ok / 0 unresolved / 0 mismatch` masked operands.
  This current measurement supersedes the historical `86.10%` snapshots,
  which predate later ownership-oriented source changes.

## 2026-07-11 slug voice threshold ownership

The two floats immediately before `enemy_manager` are now owned fields:
`next_slug_voice_trigger_z` at `+0x1270fcc` and
`slug_voice_trigger_spacing_z` at `+0x1270fd0`. This initializer seeds them to
`50.0f` and `100.0f`; exact-matched `spawn_slug_hazard` advances the former and
marks the selected slug's `engagement_voice_gate`. The typed stores are
codegen-neutral here, retaining `86.10%`, `560/555`, prefix `244/555`, and the
existing `105 ok / 1 mismatch` audit.

## 2026-07-11 embedded group-head ownership

- The start/completion banners and ordinary runtime cells share the complete
  `track_body_list_head +0x355b9c`. The tutorial barrier uses the complete
  `barrier_sub_lazer_list_head +0x355bd4`, which exact sub-lazer spawning also
  consumes; these are group sentinels rather than single-pool owners.
- The barrier node and its borrowed player pointer now use the embedded
  `BarrierActor` directly. Focused output remains `86.10%`, `560/555`, prefix
  `244/555`, with the same 105 clean non-table operands.
- COFF places `$L5037` at object `+0x838` with the tracked five entries and
  `$L5038` immediately after it with four. Their bounded relocations match the
  two curated target tables, clearing the former compiler-label-only audit gap
  and bringing the complete masked audit to 106 clean operands.

## 2026-07-11 landscape manager ownership

- Random landscape-script loads and activation now use the complete embedded
  `LandscapeManager` type at `SubgameRuntime +0xff7c00`; the former script-bank
  and first-entry receiver views were two windows onto this one object.
- Header consolidation renumbers the unchanged two local COFF tables to
  `$L5017`/`$L5018`. Their bounded contents match the already audited
  `$L5037`/`$L5038` forms, so both aliases are registered without hiding the
  separate source-shape residuals in the function body.

## 2026-07-11 SMTrack height-field header refresh

- Recovering the adjacent `0x128`-byte animator and Object-derived
  `FrameSequence` renumbers the two unchanged COFF tables to
  `$L5054`/`$L5055`.
- They remain at object `+0x838`/`+0x84c` with the same bounded five- and
  four-entry relocation contents. Registering these compiler-local spellings
  restores 106 clean operands without changing the 86.10% function body.

## 2026-07-11 GalaxyRoute slot header refresh

- The exact 101-slot route layout renumbers the unchanged tables to
  `$L5016`/`$L5017`, still at object `+0x838`/`+0x84c` with identical bounded
  contents.
- `$L5017` is reassigned from the prior state-table generation to the current
  track table, keeping aliases unambiguous and restoring all 106 clean operands
  without changing the partial function body.

## 2026-07-11 cRSlugVoiceManager owner

The exact call receiver at `SubgameRuntime +0x35bb7c` is now the embedded
`SlugVoiceManager` rather than an anonymous byte interval. Android independently
retains `cRSlugVoiceManager::Init()` with the same three fields and values. The
typed member call is codegen-neutral at the pinned 86.10% frontier.

## 2026-07-11 cRParcelManager initializer owner

The level reset now calls the embedded
`SubgameRuntime::parcel_manager.initialize_track_parcel_slots()` directly at
`+0x125e480`. The exact callee and Android `cRParcelManager::Init()` prove that
this is the manager owner, not a one-method pool window. The focused result
remains `86.10%`, `560/555`, prefix `244/555`, with 105 clean non-table
operands and the one real table-shape mismatch.

## 2026-07-11 empty cRProgressBar owner

The shared no-op call at SubgameRuntime +0x3bbb54 is now receiver-typed as the
embedded `ProgressBar` at Player +0x3f0. Android `cRSubGame::StartLevel()`
independently calls the one-instruction `cRProgressBar::Init()` at the matching
lifecycle point. Windows and Android AI ignore the receiver, so the owner is an
empty one-byte C++ class followed by alignment, not a fabricated state word.
Focused Wibo remains 86.10%, 560/555 instructions, with 105 clean operands and
the existing table-shape mismatch.

## 2026-07-13 shared level-build ownership

- The level reset now uses the shared `GameRoot`, `SubgameRuntime`, `Player`,
  and `SubTracks` owners for the star field, landscape/backdrop state, replay
  inputs, gauges and hazards, score/lives widgets, player setup, and terminal
  subgame state. These substitutions preserve the 86.10%, 560/555 instruction
  frontier and expose ownership without manufacturing a match.
- `SubgameRuntime +0xa854` is the byte-sized `track_state_latch` handed between
  row-event and movement-emitter paths. `SubTracks::selected_speed` also has a
  bitwise view for the native `-1.0f` sentinel comparison.
- The typed Banner-member rewrite was rejected because it changed the native
  register topology. The remaining raw Banner setup stays visible as a real
  source-shape residual even though the surrounding pool owner is known.
- The shared-header refresh advances the unchanged local tables to `$L6051`
  and `$L6052`. COFF still places them at object `+0x838` and `+0x84c`, with
  the established bounded five- and four-entry contents. Registering those
  content-proven aliases restores all 106 operands without altering the
  partial function body.

## 2026-07-13 SubSegment visited-latch refresh

The shared byte-latch correction advances the unchanged local tables to
`$L6052`/`$L6053`. COFF retains the bounded five- and four-entry tables at
object `+0x838`/`+0x84c`; `$L6052` is reassigned to the state table and
`$L6053` names the track table. The partial body remains at 86.10% with all
106 operands clean.

## 2026-07-13 root BOD-list owner refresh

Removing the duplicate pool-specific list-anchor typedefs advances the same
tables to `$L6050`/`$L6051`. COFF retains their bounded five- and four-entry
contents at object `+0x838`/`+0x84c`; `$L6051` is reassigned to the current
track table. The body remains honestly partial at 86.10% with all 106 operands
clean.

## 2026-07-13 SegmentCache backlink refresh

Retiring the synthetic `TrackRenderGrid` header view advances the unchanged
tables to `$L6040`/`$L6041`. COFF retains their bounded five- and four-entry
contents at object `+0x838`/`+0x84c`; registering the current aliases restores
all 106 operands. The body remains honestly partial at 86.10%.

## 2026-07-13 analysis level-definition closure

The path-template Binary Ninja/IDA campaign now embeds both complete
0x1a5978-byte `SubTracks` owners in `SubgameRuntime`: the active
`level_definition +0xa874` and startup scratch storage at `+0x1b01ec`. Their
100 segment slots, first/last segments, random controls, colors, level name,
speed/hazard controls, landscape index, and parcel fields end exactly at the
sentinel band at `+0x355b64`; the old first-dword `level_segment_count` view is
retired.

Binary Ninja preview verifies `SubSegment == 0x4220`, `SubTracks == 0x1a5978`,
and the enclosing `SubgameRuntime == 0x1272838`, then reverts. Matching source
is unchanged: focused Wibo remains 86.10%, 560/555 instructions, with all 106
masked operands clean and no mismatch.

## 2026-07-13 no-fakematch audit

The landscape fallback parameter reload and six start/completion Banner
position stores no longer use volatile qualifiers. Those qualifiers existed
only to preserve a stack reload and redundant zero-store schedule. The direct
source keeps the same proven `SubTracks`, `BannerPool`, player backlink, and
landscape ownership while leaving compiler allocation visible: focused Wibo is
77.67%, 560/555 instructions, prefix 177, with 100 clean operands and the
existing state jump-table identity mismatch.

## 2026-07-13 canonical Binary Ninja replay

The authoritative `SubgameRuntime` map now reaches this caller through the
return value of `initialize_subgoldy`, exposing the embedded Player presentation
channels, slug voice manager, active level definition, barrier backlink, and
Banner pool. The tracked BN export drops from 81 to 28 raw offsets and is
guarded by the decompile health checks. Its own receiver remains an honestly
reported deferred `Game*` correction because Binary Ninja restores a pinned
parameter local. Matching source is unchanged at the 77.67% no-fakematch
frontier above.

## 2026-07-14 canonical root services and active list

The level builder now reloads the canonical `GameRoot* g_game` for the
starfield, four random landscape loads, backdrop flip, render-skip gate,
player mouse cursor, and all seven active-list insertions. Those insertions
borrow `GameRoot::active_bod_list`; ownership remains with the embedded Player
and presentation subobjects. The old `char* +0x5a8` anchor obscured that list
boundary but described the same native address.

The Banner setup intentionally retains its receiver-relative byte cursor.
Focused output is byte-identical at 77.67%, 560/555 instructions, prefix
177/555, with all 101 operands clean.

## 2026-07-14 replay-suppression owner closure

The score-HUD gate now follows
`GameRoot::intro.hide_for_replay_latch`. Exact `Intro::update_new_game_menu`
owns the latch and `update_subgame` independently consumes it, closing the
former raw root `+0x4f2e0` access without changing this builder's focused
output.

## 2026-07-14 Snail active-list inheritance

The presentation node linked into `GameRoot::active_bod_list` is now the
embedded `Snail`'s inherited `RenderableBod`, rather than a manually duplicated
prefix. Player retains storage ownership and the list only borrows it. Focused
output is byte-identical at 77.67%, 560/555 instructions, prefix 177, with 101
clean operands and the existing state-table mismatch.

## 2026-07-14 animation-channel active-list inheritance

The jetpack and three weapon nodes now enter the active list through their real
`Weapon -> RenderableBod -> BodNode` inheritance. Snail
retains storage ownership and the root list only borrows those four embedded
subobjects. Focused output is byte-identical at 77.67%, 560/555 instructions,
prefix 177, with 101 clean operands and the existing state-table mismatch.

## 2026-07-14 Banner owner closure

The start and completion row actors now use the two embedded
`SubgameRuntime::banners.slots` directly. Their inherited position, list flags,
color alpha, and `owner_player` backlink are initialized from the named
`first_block_row_count` and `completion_row_start` fields; the scratch no
longer needs a raw byte alias of its receiver or any `+0x359080..+0x359134`
accesses.

This completes the same `BannerPool` ownership used by exact teardown and the
exact constructor/update pair without reshaping the compiler-sensitive store
schedule. Focused output remains byte-identical at 77.67%, 560/555
instructions, prefix 177, with all 101 masked operands clean.

## Authored owner hierarchy (2026-07-14)

Android `cRSubGame::StartLevel(int)` preserves this outer function's starfield
and HUD setup, music selection, subsystem resets, level load, nested
`GenerateLevel(int)` call, landscape activation, and player setup. The exact
Windows callee at `0x437de0` is the nested authored `GenerateLevel(int)`, and
its population callee at `0x435eb0` is authored `BuildLevel()`. This corrects
the old crosswalk that assigned `BuildLevel()` to this outer lifecycle method;
the matching source and honest 77.67% frontier are otherwise unchanged.

The music loader callsites push three cdecl arguments in every switch arm and
discard twelve bytes afterward. Canonicalizing `cache_music_file` as
`char(char* path, int32_t unused, char* unused_default_path)` preserves that
exact caller ABI; the former one-argument decompiler prototype caused IDA's
call analysis to reject this otherwise healthy outer function.

## 2026-07-14 times-up lifecycle ownership

Level start now clears the exact `TimesUp` tail owner through
`TIMES_UP_STATE_INACTIVE`, pairing this reset with Init, AI, and UnInit. Focused
output remains byte-identical at 77.67%, 560/555 instructions, prefix 177/555,
with all 101 operands clean.

## 2026-07-14 analysis receiver closure

The remaining live Binary Ninja `Game*` receiver was a stale same-size named
type, not a second StartLevel aggregate. The guarded repair recreated only the
exact known function as `SubgameRuntime*`, preserved both user-defined
parameters, verified readback, and saved explicitly. The tracked BN decompile
drops from 28 raw offsets to two and now follows the level definition, replay
record, runtime pools, landscape manager, banners, Player, presentation
channels, HUD, barrier, and slug-voice owners directly. The two remaining
expressions are unresolved Player-internal bytes, not receiver ambiguity.

IDA was already fully typed, so the two decompiler views now agree on the
outer owner. Matching source is unchanged at the honest 77.67%, 560/555
frontier with all 101 operands clean.
