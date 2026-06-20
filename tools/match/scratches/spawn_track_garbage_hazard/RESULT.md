# Result

## Matcher summary

| Metric | Before | After |
| --- | ---: | ---: |
| Match | 99.30% | 99.30% |
| Instructions | target 143 / candidate 143 | target 143 / candidate 143 |
| Common prefix | 48 / 143 | 48 / 143 |
| Masked operands | 16 ok, 0 unresolved, 0 mismatch | 16 ok, 0 unresolved, 0 mismatch |

## Accepted changes

None. The existing x/z/y `Vector3` staging remains the best measured source
shape, so `scratch.cpp` is unchanged.

## Rejected trials

- Moving the y expression ahead of the vector stores and testing expression
  orders x/y/z, x/z/y, and y/x/z produced 98.60%, 143/143 instructions, and a
  47/143 prefix.
- Split x/y/z ordering was codegen-neutral only for the existing effective
  schedule (99.30%); y/x/z fell to 97.20%, while z-first orders produced
  92.68%-94.08% and often grew to 144 candidate instructions.
- These trials preserved the clean 16-operand audit, but none improved the
  single localized scheduling region.

## Next region

Target instruction 48 in the projection staging block. Native performs
`fadd [cell->anchor_position.y]` before loading the x and z dwords; the current
candidate loads x/z first and then performs the same `fadd`. The next useful
probe needs a plausible source construct that changes only this x87/integer-load
interleave without disturbing the staged-vector copy.
