# sample_smtrack_heightmap match result

## Score

| Metric | Result |
|---|---:|
| Match | 59.09% |
| Target instructions | 109 |
| Candidate instructions | 111 |
| Common prefix | 0 / 109 |
| Masked operands | 12 clean |

There are no unresolved or mismatched masked operands. The scratch recovers the
replacement-image pointer, the source/output field roles, the inclusive x87 loop
conditions, the bottom-up texel index, RGB averaging, optional cubic shaping,
and the final y-lane sample write.

The major retained mismatch is register allocation around the inner loop:

```text
target    keeps the output sample pointer in ebp
candidate keeps that pointer on the stack and uses ebp for texel indexing
```

The target also materializes all three color channels with separate `fild`
operations before `faddp`, while the candidate emits equivalent `fiadd`
instructions for later channel additions.

## Measured progression

| Trial | Match | Outcome |
|---|---:|---|
| Initial semantic sampler | 54.38% | One constant mismatch from folded `1/255 * 1/3` |
| Inclusive loop bounds and separate scale factors | 59.09% | Kept; masked operands clean |
| Split row/column index expression | 59.09% | No codegen change |
| `register` output pointer hint | 59.09% | No codegen change; not retained |
