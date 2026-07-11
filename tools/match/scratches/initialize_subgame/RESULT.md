# `initialize_subgame` match result

Current retained source is proof-grade:

```text
match: 100.00%
target: 396 insns, candidate: 396 insns
prefix: 396/396 target insns
masked operands: 85 ok, 0 unresolved, 0 mismatch
```

The source recovers the runtime-cell fringe clear, level-record copy, replay
speed seed, owned HUD handles, timer/score rendering, embedded player setup,
static segment initialization, and the selector dispatch into
galaxy/challenge/reset.

The two compiler-emitted mode tables are content-audited:

- `0x437adc`, five entries, bottom-HUD mode dispatch, current candidate
  `$L4670`;
- `0x437af0`, eight entries, startup mode dispatch, current candidate
  `$L4671`.

The earlier curated table names were reversed. The corrected names and current
VC6 aliases (plus the prior `$L4668`/`$L4669` generation) are backed by the
target callsites and bounded table contents; no operand was accepted on label
identity alone.
