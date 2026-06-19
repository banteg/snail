# `initialize_quaternion_from_matrix` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **92.47%** |
| Target instructions | 186 | 186 |
| Candidate instructions | 0 | 186 |
| Common prefix | 0 / 186 | **42 / 186** |
| Masked operands | none | **23 clean, 0 unresolved, 0 mismatched** |

The final scratch is instruction-count exact and has no unresolved or mismatched
masked operands. The first remaining mismatch is the destination sense of the
first fallback diagonal branch:

```text
target[42]    jne L120
candidate[42] je L120
```

## Accepted source-shape changes

- Recovered the standard trace-positive matrix-to-quaternion path.
- Recovered the X/Y/Z dominant-diagonal fallback formulas.
- Preserved native typo strings: X uses `"ERROR:sqrt %f\n"`, while Y and Z use
  `"ERROR:sqt %f\n"`.
- Declared `square_root` as caller-side `float` so VC6 emits the native 32-bit
  constants for `0.5f` and `0.25f`.
- Kept direct labels for the fallback arms; this is the best measured honest
  source shape so far.

## Measured progression

| Trial | Match | Candidate instructions | Outcome |
|---|---:|---:|---|
| No scratch | 0.00% | 0 | Baseline |
| Initial readable formula, `double square_root` caller shape | 78.49% | 186 | Superseded |
| Direct labels plus caller-side `float square_root` | 91.94% | 186 | Superseded |
| Direct labels plus float positive-path scale | **92.47%** | **186** | Final retained result |

## Rejected trials

- Spelling the first diagonal test as `!(m00 < m11)` improved the positive-path
  prefix but pulled the X arm inline and dropped the score to 73.02%.
- Jumping explicitly over the less-than dispatcher made VC6 insert an extra jump
  and moved the Y arm forward, dropping the score to 67.56%.
- A structured `m00 >= m11` top-level form produced the right first branch sense
  locally but swapped the X/Y branch targets and dropped the score to 74.73%.
- No inline assembly, `volatile` clutter, fake globals, dummy externs, or stack
  padding were retained.
