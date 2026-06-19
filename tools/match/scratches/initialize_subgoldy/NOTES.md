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

- match: 95.14%
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
