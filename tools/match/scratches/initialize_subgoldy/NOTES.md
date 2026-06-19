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
- The tiny `0x41aa30` spring reset and empty runtime callback are represented
  as local method views only to preserve their call shapes.
- The remaining tail mismatch starts after the ghost/cameraman setup in the
  camera-target/control-source seed block and is currently register/order
  polish rather than a known semantic difference.
