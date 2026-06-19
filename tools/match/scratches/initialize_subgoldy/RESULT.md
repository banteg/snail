# `initialize_subgoldy` match result

First measured broad scratch:

```text
match: 92.25%
target: 279 insns, candidate: 276 insns
prefix: 190/279 target insns
masked operands: 26 ok, 1 unresolved, 0 mismatch
```

Recovered blocks include the player-field reset, animation-manager setup for
the body/jetpack/weapon channels, snail skin and cutscene AI initialization,
matrix resets, click-start/cameraman/ghost setup, camera target and control
source seed, follow attachment matrix reset loop, jetpack gauge initialization,
and final lane/attachment/nuke state clears.

The only masked unresolved operand is the call to the small spring reset helper
at `0x41aa30`, represented locally as `SpringFloat::reset_spring_float()`.
