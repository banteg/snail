# enumerate_matching_archive_or_fs_entries @ 0x431740

Initial scratch added for the archive/filesystem enumerator.

| Metric | Starter | Current |
|---|---:|---:|
| Match | 0.00% | **81.52%** |
| Target instructions | 182 | 182 |
| Candidate instructions | 0 | 186 |
| Common prefix | 0 / 182 | **7 / 182** |
| Masked operands | none | **26 clean, 0 unresolved, 0 mismatched** |

No inline assembly, dummy symbols, stack padding, or normalizer-specific tricks are used.

The source recovers the archive-backed and filesystem-backed filename
enumeration behavior. The filesystem lane uses the bundled MSVC6 CRT's exact
`_finddata_t`, `_findfirst`, `_findnext`, `_getcwd`, and `_chdir` ownership;
remaining differences are the documented wildcard-loop byte allocation and
ASCII-fold expression shape.
