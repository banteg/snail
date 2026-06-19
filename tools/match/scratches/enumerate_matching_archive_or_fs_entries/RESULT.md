# enumerate_matching_archive_or_fs_entries @ 0x431740

Initial scratch added for the archive/filesystem enumerator.

| Metric | Starter | Current |
|---|---:|---:|
| Match | 0.00% | **49.60%** |
| Target instructions | 182 | 182 |
| Candidate instructions | 0 | 189 |
| Common prefix | 0 / 182 | **0 / 182** |
| Masked operands | none | **23 clean, 0 unresolved, 0 mismatched** |

No inline assembly, dummy symbols, stack padding, or normalizer-specific tricks are used.

The source recovers the archive-backed and filesystem-backed filename enumeration
behavior. The remaining first mismatch is the prologue/register owner shape:
native loads `g_archive_index_records` before reserving the stack, while the
scratch keeps the pointer live in `ebx` and grows the frame by four bytes.
