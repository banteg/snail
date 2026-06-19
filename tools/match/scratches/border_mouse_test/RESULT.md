# border_mouse_test match result

## Score

| Metric | Result |
|---|---:|
| Match | 98.29% |
| Target instructions | 117 |
| Candidate instructions | 117 |
| Common prefix | 73 / 117 |
| Masked operands | 5 clean |

There are no unresolved or mismatched masked operands. The source recovers both
the plain padded-rectangle path and the texture-mask hit-test path, including
the raw 18-byte texture header / 3-byte pixel stride adjustment.

The only remaining mismatch is the final row-offset multiply register choice:

```text
target[73]    imul esi, eax
candidate[73] imul eax, esi
```

The native keeps the row product in the original width register (`esi`) before
adding x and the six-pixel header offset; the scratch emits the equivalent row
product in `eax`. Source variants using `width *= y`, a separate `row` local,
and direct indexed `pixels[(y * width + x) * 3]` did not improve this without
byte-shaping the source.
