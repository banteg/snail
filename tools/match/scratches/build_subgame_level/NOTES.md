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
- `g_completion_bonus_x_source` and the neighboring
  `g_config_default_challenge_speed_slider` are declared separately now that the
  saved-config scalar split is curated in the global reference manifest.
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
  views for `StarField`, `GolbPathBank`, `DamageGaugeController`,
  `SubLazerPool`, `SaltHazardPool`, `LevelDefinitionLoader`,
  `TrackParcelPool`, `FrontendWidget`, `LandscapeScriptBank`,
  `ActiveLandscapeEntry`, `BodList`, `BodNode`, `MouseCursorState`, and
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
resolved to `g_config_default_challenge_speed_slider`.

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
