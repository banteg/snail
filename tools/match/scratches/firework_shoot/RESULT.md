# firework_shoot match result

## Score

| Metric | Result |
|---|---:|
| Match | 95.15% |
| Target instructions | 103 |
| Candidate instructions | 103 |
| Common prefix | 78 / 103 |
| Masked operands | 21 clean |

There are no unresolved or mismatched masked operands. The source recovers the
render-flag/count gate, sprite allocation arguments, color helper call, random
duration/color/velocity generation, and final position copy.

```text
target[78]    fmul dword [ADDR]
candidate[78] lea esi, dword [esi+0x48]
```

The remaining residual is the final velocity/position tail. Native finishes the
last random X multiply and all three velocity stores before advancing the sprite
base to `position`; the current source advances the base just before the
multiply. Ending the ordinary countdown lifetime before the final position copy
recovers four fuzzy bytes and the native counter's overlap with that copy.
Focused probes rejected raw float lanes, explicit velocity field stores, and
aggregate velocity output pointers, so the retained source keeps the typed
`Vector3 velocity` local and aggregate velocity assignment.

The 2026-07-25 BN/IDA lifetime replay improves analysis ownership without
changing this result: the reused argument slots are now split into their real
color/velocity temporaries, and IDA presents the native `FireWork` receiver,
`Sprite` fields, and final `Vec3` copy. No matcher source was changed.
