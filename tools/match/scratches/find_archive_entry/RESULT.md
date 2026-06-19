# `find_archive_entry` match result

## Score

| Metric | Result |
|---|---:|
| Match | **66.12%** |
| Target instructions | 60 |
| Candidate instructions | 61 |
| Common prefix | 7 / 60 |
| Masked operands | 2 clean, 0 unresolved, 0 mismatched |

The retained partial recovers the archive-index null/count guards, 12-byte
record walk, case-folded path comparison, shared not-found semantics, and found
record address calculation.

The remaining mismatch is source-shape/codegen debt rather than unresolved
data: candidate VC6 places the not-found epilogue after the found return,
selects `ecx` for the archive cursor where native uses `edx`, and encodes the
case fold as equivalent `add al, 0xe0` instead of native `sub al, 0x20`. No
volatile access, register shim, or fake alias was retained to force that shape.
