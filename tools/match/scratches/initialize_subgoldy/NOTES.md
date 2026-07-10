# initialize_subgoldy

First scratch for `initialize_subgoldy @ 0x43a9c0`.

This initializes the live Goldy player block for a new subgame run. The scratch
keeps the broad `Player` storage as raw offsets while using established helper
types for animation managers, click-start, cameraman, damage gauge, jetpack
gauge, snail skin, invincibility shell, and matrices.

Recovered structure:

- resets player, movement, row-event, nuke, resurrect, completion, and score
  producer lanes;
- initializes the visual-root spring, score stats, invincible shell, animation
  managers, snail skin, cutscene AI, click-start prompt, cameraman, ghost, and
  damage gauge;
- seeds the live position, cached camera target, wobble timers, control source,
  follow state, completion handoff cycle, and jetpack gauge;
- clears the twelve 0x2e8-byte follow/attachment matrix records and points
  them back at the active subgame.

Known partials:

- The full `Player` layout is still intentionally raw here; do not consolidate
  from this scratch alone.
- The tiny `0x41aa30` spring reset is now split out as a proof-grade
  `reset_spring_float` scratch; the empty runtime callback is still represented
  as a local method view only to preserve its call shape.
- The remaining tail mismatch starts after the ghost/cameraman setup in the
  camera-target/control-source seed block. The current scratch matches all
  masked operands but still differs in base-pointer/register scheduling for the
  cached camera target, the control-source branch, and one transform-loop game
  pointer load.

Latest focused result:

- match: 95.86%
- target/candidate instructions: 279 / 276
- prefix: 190 / 279
- masked operands: 27 clean, 0 unresolved, 0 mismatched

2026-06-20 helper-type consolidation:

- `ScoreStats` and `SpringFloat` now come from shared headers instead of
  scratch-local duplicate declarations.
- Focused Wibo remains unchanged at 95.14%, 276/279 instructions, prefix
  190/279, with 27 clean masked operands.
- The normal type-consolidation report no longer lists either helper as
  `partial-compatible`; remaining initializer debt is still the cached camera
  target/control-source tail described above.

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
- The self-links at `NukeController::owner_player` and
  `PlayerPresentationController::owner_player`, plus the embedded
  `follow_active` lane, are now expressed through shared `Player` fields in the
  scratch instead of raw offsets. Focused Wibo is byte-shape neutral at the
  retained `95.86%`, `276/279`, `27 ok / 0` result.
- A fully typed `Vector3` spelling of the cached-camera/live-position block was
  rejected: it regressed to `92.97%` and changed the native constant/register
  schedule. The honest residual remains the three-instruction camera-target
  pointer materialization plus control-source/attachment-loop register choice.
