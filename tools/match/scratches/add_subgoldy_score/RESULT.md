# add_subgoldy_score match result

## Score

| Metric | Result |
|---|---:|
| Match | 100.00% |
| Target instructions | 58 |
| Candidate instructions | 58 |
| Common prefix | 58 / 58 |
| Masked operands | 6 clean |

The scratch now matches the score mutator exactly. The key source-shape fix was
nesting the score sound gate under the successful 50,000-point life-award path:
native does not consider the sound gate when the score threshold is unchanged or
the visible life stock is already capped.
