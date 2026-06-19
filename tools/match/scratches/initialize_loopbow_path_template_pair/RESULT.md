# Result

## Matcher summary

| Metric | Starter | Final |
|---|---:|---:|
| Match score | 0.00% | **67.54%** |
| Target instructions | 796 | 796 |
| Candidate instructions | 2 | **800** |
| Common prefix | 0 / 796 | **10 / 796** |
| Native local frame | not reproduced | **`0x9c` exact** |
| Native stack cleanup | not reproduced | **`ret 0x18` exact** |

The final candidate is four instructions longer than the target while matching
the target's full local-frame size and six-argument epilogue.

## Masked operand audit

```text
60 ok, 2 unresolved, 0 mismatch
```

Both unresolved operands are calls to the scratch symbol
`multiply_matrix_in_place` and align exactly with the target calls:

```text
target/candidate instruction 348, relative offset +0x56c
target/candidate instruction 354, relative offset +0x57d
```

The target address for both is `0x44d1d0`.  No masked operand differs.

## Accepted source-shape changes

- Recovered the true six-argument member-function ABI from native call sites.
- Added conservative scratch-local overlays for the `0xa8` sample and `0x30`
  face-quad layouts.
- Reconstructed all primary and secondary straight samples and the circular
  loop-bow section.
- Kept constants and x87-sensitive arithmetic in target-like order.
- Used value-vector expressions for sample deltas, arc offsets, lateral
  offsets, and mesh points.
- Constructed separate terminal `{0, 0, 1}` direction values.
- Added a semantic endpoint vector for the synthetic terminal mesh row; this
  recovered the exact `0x9c` frame without padding.
- Scoped the sample pointer independently in each vertex branch.
- Duplicated side-specific face construction, winding, texture lookup, and UV
  stores to preserve the native branch shape.

## Representative rejected trials

| Trial | Score | Reason rejected |
|---|---:|---|
| First complete reconstruction | 21.82% | Correct broad behavior, but pointer induction and temporary lifetimes were far from native shape. |
| Direct-index reconstruction | 48.45% | Large improvement, retained as a base, but mesh and vector construction still diverged. |
| Straight-section increment-at-end form | 55.68% | Useful intermediate; later value-vector and branch-shape work superseded it. |
| Combined delta/vertex vector form | 59.48% | Recovered many x87 sequences but still had the wrong frame and mesh control flow. |
| Shared/common face pointer and tail | 62.50% | Merging the side branches removed native duplicated indexing and stores. |
| Scalar/direct-component vertex construction | 64.27% | Optimized away temporaries that the target appears to materialize. |
| Copying the terminal sample position as a vector | 61.03% | Produced substantially worse copy and x87 scheduling. |
| Endpoint constructor form | 66.25% | Close, but component assignment gave better local lifetimes and instruction alignment. |
| Inverted terminal-row branch | 66.50% | Altered branch layout and was below the retained form. |
| Top-level endpoint without branch-local sample pointers | 66.62% | Exact frame, but less accurate vertex-loop pointer scheduling. |
| Branch-local sample pointer with endpoint constructor | 67.25% | Near-final, but component assignment matched more instructions. |
| Branch-local sample pointer with partial endpoint values | 67.42% | One instruction-count improvement, but a lower total score than the retained full assignment. |
| Artificially doubled lateral expression | 58.25% | Distorted semantics and x87 scheduling; rejected outright. |
| Hoisted outer face pointer/reset | 45.59% | Strongly changed native loop/control-flow structure. |

## Remaining work

The first mismatch is a local-slot choice at target instruction 10
(`esp+0x2c` versus `esp+0x24`), despite the exact total frame.  The next focused
region should be the vertex-grid loop near target offset `+0x7d3`, especially
the sample-base induction and terminal endpoint expression.  After that, the
face loop's register allocation and UV-store ordering are the largest remaining
source-shape opportunities.
