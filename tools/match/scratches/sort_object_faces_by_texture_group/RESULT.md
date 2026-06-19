# `sort_object_faces_by_texture_group` match result

## Score

| Metric | Result |
|---|---:|
| Match | **41.61%** |
| Target instructions | 75 |
| Candidate instructions | 74 |
| Common prefix | 1 / 75 |
| Masked operands | none |

The source captures the in-place texture-reference grouping algorithm and the
compiler emits inline 0x30-byte struct swaps. The current mismatch is dominated
by register allocation and block layout, not missing calls or invented helper
behavior.
