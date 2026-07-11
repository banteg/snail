# initialize_subgoldy

First scratch for `initialize_subgoldy @ 0x43a9c0`.

This initializes the live Goldy player block for a new subgame run. The scratch
keeps the broad `Player` storage as raw offsets while using established helper
types for animation managers, click-start, cameraman, damage gauge, jetpack
gauge, snail skin, invincibility shell, and matrices.

Recovered structure:

- resets player, movement, row-event, nuke, resurrect, completion, and score
  producer lanes;
- initializes the visual-root spring, Squidge oscillator, invincible shell, animation
  managers, snail skin, authored cRInvincible, cutscene AI, click-start prompt, cameraman, ghost, and
  damage gauge;
- seeds the live position, cached camera target, wobble timers, control source,
  follow state, completion handoff cycle, and jetpack gauge;
- clears the twelve 0x2e8-byte follow/attachment matrix records and points
  them back at the active subgame.

Source-shape notes:

- The receiver is the complete shared `Player`; several old initialization
  runs remain raw-offset shaped where that is the proven VC6 source form.
- The tiny `0x41aa30` spring reset is now split out as a proof-grade
  `reset_spring_float` scratch; the empty runtime callback is still represented
  as a local method view only to preserve its call shape.
- The camera-target/control-source tail is now exact. The retained aggregate
  assignment is supported independently by the named Android
  `cRSubGoldy::Init` implementation, not by register forcing.

Latest focused result:

- match: 100.00%
- target/candidate instructions: 279 / 279
- prefix: 279 / 279
- masked operands: 27 clean, 0 unresolved, 0 mismatched

2026-07-11 Squidge ownership closure:

- The call on `Player +0x4344` is the authored `cRSquidge::Init`, not
  `cRSubGoldy::ScoreStatsInit`. Android and iOS expose the full matching
  `cRSquidge::{Init,StartY,StartZ,AI}` family, and the six-float layout agrees
  exactly with the Windows helpers.
- The scratch now calls the real inline `Player::squidge` owner directly.
  Goldy's score buckets remain independently owned at `Player +0x310`.
- Focused Wibo remains exact at 100.00%, 279/279 instructions, with all 27
  masked operands clean.

2026-07-11 cRInvincible ownership closure:

- The owner at `Player::presentation +0x1894` (`Player +0x4218`) is the exact
  0xa4-byte Windows `Invincible`, backed by iOS/Android
  `cRInvincible::{Init,AI}` and Android `cRInvincible::Start`.
- The initializer now reaches that embedded member through the recovered owner
  chain and remains exact at 279/279 instructions.

2026-07-11 cRCutScene ownership closure:

- The owner at `Player::presentation +0x1958` (`Player +0x42dc`) is the exact
  0x5c-byte `CutScene`. Android's `cRCutScene::Init` performs the same backlink
  and state stores, while iOS v1.9 exposes the Player-parameter variant.
- The initializer now calls that embedded owner directly and remains exact at
  279/279 instructions. The source return is `void`; direct member assignments
  preserve the native instruction order without inventing a returned value.

2026-06-20 larger near-proof tail audit:

- Focused Wibo still reports 95.14%, 276/279 candidate/target instructions,
  190/279 prefix, and 27 clean masked operands.
- Rejected cached-camera-target probes: using the shared `PositionBits` raw-copy
  view and moving the `zero_x`/`zero_y` assignments into the target block are
  both codegen-neutral. VC6 still folds the `self + 0x2964` target pointer into
  direct stores instead of keeping native `eax` live across the x/y/z writes.
- Rejected control-source probe: spelling the IDA-style checks as
  `g_game_base != (char*)-0x44/-0xb4` regresses to 92.95% and removes two
  candidate instructions. Keep the current pointer-after-add truthiness test.
- Rejected transform-loop probe: naming a `game` local after each
  `set_matrix_identity` call is codegen-neutral and still reloads the game
  pointer through `eax` instead of native `edx`. Keep the direct store from
  `self + 0x408`.

2026-06-20 live-position lane pass:

- Focused Wibo improves from 95.14% to 95.50% while keeping 276/279 candidate
  instructions, the 190/279 prefix, and 27 clean masked operands.
- Retained: spelling the live-matrix position lanes at `self+0x68` through a
  raw `int* live_position` before copying z into `cached_camera_target_world`.
  This recovers the native order for the `+0x68/+0x6c` zero stores after the
  damage/surface reaction constants instead of letting VC6 hoist the x lane.
- Rejected: a typed `Vector3*` camera-target view regresses to 92.61% by
  materializing the z constant in a register and disturbing the control-source
  tail. Naming the reaction-step constant and spelling the cached target as a
  byte-offset `char*` are codegen-neutral at 95.50% and still fold the
  `self+0x2964` stores. The remaining residual is the cached-target base
  materialization plus the existing control-source/transform-loop register
  ownership.

2026-06-20 velocity-lane tail pass:

- Focused Wibo improves from 95.50% to 95.86% while keeping 276/279 candidate
  instructions, the 190/279 prefix, and 27 clean masked operands.
- Retained: spelling the velocity clear through a raw `int* velocity_lanes`
  keeps the `player_slot` load after the z/y/x velocity zero stores, matching
  native's post-camera-target tail order.
- Rejected: moving the zero-y temporary earlier and naming cached-target y/z
  lane pointers are codegen-neutral and still fold `self+0x2964` into direct
  stores. Hoisting a shared `g_game_base` local for the control-source branch
  regresses to 95.14%, and naming the transform-loop game pointer regresses to
  94.43% by keeping the game pointer in `ebp` and spilling the loop count.
- 2026-06-20 Player header consolidation: including the promoted `player.h`
  declaration is codegen-neutral at the retained `95.86%`, `276/279`,
  `27 ok / 0` profile. The body stays raw-offset shaped because the remaining
  debt is cached-target/control-source scheduling, not missing field names.

2026-07-10 ownership pass:

- Binary Ninja xrefs confirm this function is the sole setter of both
  `Player::game +0x408` and `Player::control_source +0x43c`. The former points
  back to the `SubgameRuntime` that embeds the Player; the latter borrows one
  of two input-controller views from the root game object.
- The self-links at `Nuke::owner_player` and
  authored `Snail::owner_player`, plus the embedded
  `follow_active` lane, are now expressed through shared `Player` fields in the
  scratch instead of raw offsets. Focused Wibo is byte-shape neutral at the
  retained `95.86%`, `276/279`, `27 ok / 0` result.
- `Player +0xa0` is now exposed as the embedded `ClickStartController`; using
  that owner view at its initializer is also codegen-neutral.
- A fully typed `Vector3` spelling of the cached-camera/live-position block was
  rejected: it regressed to `92.97%` and changed the native constant/register
  schedule. At that stage, the honest residual was the three-instruction
  camera-target pointer materialization plus control-source/attachment-loop
  register choice.

2026-07-11 cross-port aggregate closure:

- The bundled Android binary retains the named `cRSubGoldy::Init(int)` body and
  independently shows the live-position/cached-camera seed as actor-owned
  vector state adjacent to the same wobble, damage, and input-owner setup.
- Expressing the Windows source as `position = {0, 0, 4}` followed, after the
  neighboring timer/wobble resets, by
  `cached_camera_target_world = position` recovers native's retained target
  base register and all downstream control-source/attachment-loop choices.
- Focused Wibo improves from 95.86% (276/279, prefix 190) to proof-grade
  100.00% (279/279, full prefix), with all 27 operands clean. No volatile,
  register annotation, raw offset alias, or other fakematch is used.

2026-07-11 cRNuke ownership: the self-link at Player +0x154 now belongs to the
exact 0x7c-byte authored `Nuke` embedded at +0x150. Android independently uses
the same `cRNuke` offsets and containing-Goldy backlink. Focused Wibo remains
exact at 279/279 instructions with all 27 operands clean.

2026-07-11 cRProgressBar ownership: the folded one-byte call on Player +0x3f0
is now expressed as the embedded `ProgressBar` lifecycle method. Android
`cRSubGoldy::Init()` calls the one-instruction `cRProgressBar::Init()` on its
matching +0x3e0 owner. The class is empty and the following three bytes align
cRWarning, rather than storing an invented progress state. Focused Wibo remains
exact at 279/279 instructions with all 27 operands clean.

2026-07-11 cRCameraman ownership: Player +0x200 is now the exact 0xd8-byte
authored `Cameraman`. Android `cRSubGoldy::Init()` calls
`cRCameraman::Init()` through the matching embedded object, whose full field
layout agrees with Windows. Focused Wibo remains exact at 279/279 instructions
with all 27 operands clean.
