# run_frame_update match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 97.78% | **100.00%** |
| Target instructions | 135 | 135 |
| Candidate instructions | 135 | 135 |
| Common prefix | 18 / 135 | **135 / 135** |
| Masked operands | 23 clean | **23 clean** |

The exact source preserves the root cRGame::AI ownership already recovered for
the fixed-step state, player mouse cursor, active BOD list, player callbacks,
sprite buckets, and subgame contact registry.

## Accepted source-shape changes

- Updated `fixed_update_accumulator` in place so the x87 value stays live
  across the native mouse-owner and quit-latch setup.
- Kept the cursor x/y offsets and tint construction in the quad-call argument
  expression, recovering VC6's native right-to-left layer/tint/coordinate
  evaluation without stack spills.

No masked operands remain unresolved or mismatched.
