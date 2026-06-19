# `initialize_audio_subsystem` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 73 |
| Candidate instructions | 73 |
| Common prefix | 73 / 73 |
| Masked operands | 23 clean |

The exact body match requires `END=0x407af6`; without it, the manifest extent
includes the following cleanup helper after the final return.

The reference manifest resolves the application instance, hidden BASS window,
window procedure, and shutdown helper references, so this is proof-grade rather
than audit-pending.
