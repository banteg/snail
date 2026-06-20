# `initialize_subgoldy` match result

Current focused result after the velocity-lane tail pass:

```text
match: 95.86%
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
- Spelling the velocity clear through a raw `int* velocity_lanes` moved the
  tail from 95.50% to 95.86% by preserving the native ordering where
  `player_slot` is loaded after the z/y/x velocity zero stores.

Rejected follow-ups in this pass:

- zero-y declaration and cached-target y/z lane pointers were codegen-neutral;
- including the promoted `player.h` declaration was codegen-neutral without
  improving the raw-offset initializer;
- hoisting a shared `g_game_base` local for the control-source branch regressed
  to 95.14%;
- naming the transform-loop game pointer regressed to 94.43% by keeping the
  game pointer in `ebp` and spilling the loop count.
