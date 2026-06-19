# firework_shoot match result

## Score

| Metric | Result |
|---|---:|
| Match | 78.22% |
| Target instructions | 103 |
| Candidate instructions | 99 |
| Common prefix | 4 / 103 |
| Masked operands | 21 clean |

There are no unresolved or mismatched masked operands. The source recovers the
render-flag/count gate, sprite allocation arguments, color helper call, random
duration/color/velocity generation, and final position copy.

The first remaining mismatch is only a branch-label distance after the matched
prologue:

```text
target[4]    je L17f
candidate[4] je L16f
```

The main residual is later in the velocity/position staging. The target reuses
the original argument slots for temporary floats once `owner` and `texture_id`
have been copied into registers for `allocate_sprite`; the retained source uses
a cleaner `Vector3 velocity` local.
