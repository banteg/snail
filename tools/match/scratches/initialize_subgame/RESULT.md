# `initialize_subgame` match result

Current retained broad scratch:

```text
match: 63.25%
target: 396 insns, candidate: 385 insns
prefix: 1/396 target insns
masked operands: 65 ok, 1 unresolved, 8 mismatch
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

2026-06-20 switch-table audit names the startup mode table at `0x437adc` and
bottom-HUD mode table at `0x437af0`. The score stays `63.25%`; masked audit is
now `65 ok, 1 unresolved, 8 mismatch`. The two former switch-table unresolved
operands are real table-layout mismatches, while the remaining unresolved
operand is the built-in segment definition table push.
