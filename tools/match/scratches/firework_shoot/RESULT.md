# firework_shoot match result

## Score

| Metric | Result |
|---|---:|
| Match | 94.17% |
| Target instructions | 103 |
| Candidate instructions | 103 |
| Common prefix | 78 / 103 |
| Masked operands | 21 clean |

There are no unresolved or mismatched masked operands. The source recovers the
render-flag/count gate, sprite allocation arguments, color helper call, random
duration/color/velocity generation, and final position copy.

```text
target[78]    fmul dword [ADDR]
candidate[78] add esi, 0x48
```

The remaining residual is the final velocity/position tail. Native finishes the
last random X multiply and all three velocity stores before advancing the sprite
base to `position`; the current source advances the base just before the
multiply. Focused probes rejected raw float lanes, explicit velocity field
stores, and aggregate velocity output pointers, so the retained source keeps the
typed `Vector3 velocity` local and direct aggregate velocity assignment.
