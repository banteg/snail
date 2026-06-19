# `initialize_default_runtime_config` match result

## Score

| Metric | Result |
|---|---:|
| Match | **85.71%** |
| Target instructions | 48 |
| Candidate instructions | 36 |
| Common prefix | 0 / 48 |
| Masked operands | 12 clean, 17 unresolved, 3 mismatched |

The candidate recovers the full straight-line initializer body. The only
normalized instruction mismatch is at the manifest start: native begins with a
startup-table jump over padding, while VC6 emits the candidate body directly.

The retained source avoids inline assembly, naked functions, dummy aliases, and
normalizer-specific symbols. The remaining audit issues should be cleaned by
recovering the config blob fields or reference aliases, not by inventing scratch
symbols.
