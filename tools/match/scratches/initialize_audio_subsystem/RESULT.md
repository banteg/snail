# `initialize_audio_subsystem` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 73 |
| Candidate instructions | 73 |
| Common prefix | 73 / 73 |
| Masked operands | 17 clean, 4 unresolved, 2 mismatched |

The exact body match requires `END=0x407af6`; without it, the manifest extent
includes the following cleanup helper after the final return.

The remaining operand mismatches are unresolved or stale global names rather
than instruction differences. The source deliberately avoids dummy aliases for
`data_4dfad8` and `data_4dfaf8`.
