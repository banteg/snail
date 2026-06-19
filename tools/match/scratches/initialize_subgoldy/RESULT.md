# `initialize_subgoldy` match result

Current focused result after recovering `reset_spring_float`:

```text
match: 95.14%
target: 279 insns, candidate: 276 insns
prefix: 190/279 target insns
masked operands: 27 ok, 0 unresolved, 0 mismatch
```

Recovered blocks include the player-field reset, animation-manager setup for
the body/jetpack/weapon channels, snail skin and cutscene AI initialization,
matrix resets, click-start/cameraman/ghost setup, camera target and control
source seed, follow attachment matrix reset loop, jetpack gauge initialization,
and final lane/attachment/nuke state clears.

Evidence-backed changes in this pass:

- `reset_spring_float @ 0x41aa30` is now a proof-grade scratch, resolving the
  only masked unresolved operand in this caller.
- Recasting the cached camera target as an `int*` and assigning the live Z seed
  as `4.0f` moved the tail from 92.25% to 94.77%.
- Keeping the `g_game_base` load inside the active-slot branches moved the tail
  from 94.77% to 95.14%.

A transform-loop `game` local was tested but produced no matcher change, so it
was not kept.
