# `initialize_default_runtime_config` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 36 |
| Candidate instructions | 36 |
| Common prefix | 36 / 36 |
| Masked operands | 32 clean, 0 unresolved, 0 mismatched |

The candidate exactly recovers the full straight-line initializer body. The
CRT table entry, one-instruction tail-call thunk, and 11 alignment nops now have
separate ownership at `0x406c10`, so none are incorrectly counted as source for
this function.

The retained source avoids inline assembly, naked functions, dummy aliases, and
normalizer-specific symbols. The saved config blob slots are covered by
curated references: known consumers use role names, and unrecovered saved slots
are documented as reserved config offsets.
