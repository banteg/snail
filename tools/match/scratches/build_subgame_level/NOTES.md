# `build_subgame_level` scratch notes

## Scope

This scratch reconstructs `Game::build_subgame_level(int level_index)` at
`0x437eb0` using shared runtime headers where their call surfaces are already
stable, with raw `Game` offsets still kept local.

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

The two compiler-generated jump tables are now content-audited. The later
track dispatch table matches, while the first state dispatch table is a real
masked-operand mismatch. The former completion-bonus `+0x4` operands are now
resolved to `RuntimeConfig::default_challenge_speed_slider`.

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
  Focused Wibo is unchanged at `86.10%`, `560/555`, prefix `244/555`, with
  `105 ok / 0 unresolved / 1` masked mismatch. Moving the `row_alpha`
  declaration closer to its store was also codegen-neutral and was not kept.

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
