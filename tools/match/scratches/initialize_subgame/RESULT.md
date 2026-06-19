# `initialize_subgame` match result

First measured broad scratch:

```text
match: 63.25%
target: 396 insns, candidate: 385 insns
prefix: 1/396 target insns
masked operands: 63 ok, 5 unresolved, 6 mismatch
```

The scratch compiles and recovers the major gameplay initializer blocks: runtime
cell clearing, level-record copy, replay speed seed, HUD widgets, timer/score
rendering, static segment/runtime initialization, and the selector dispatch into
galaxy/challenge/reset.

Open shape work:

- native keeps the opening clear loop in `edx`/`edi` while this scratch uses a
  cleaner compiler allocation;
- string/data globals are still named externs, so the masked audit reports them
  as symbolic mismatches/unresolved operands;
- the bottom HUD and startup dispatch switches are semantically recovered, but
  their table layout still diverges from native.
