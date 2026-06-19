# load_file_bytes_fixed_size_from_archive_or_fs match result

## Score

| Metric | Result |
|---|---:|
| Match | 81.05% |
| Target instructions | 188 |
| Candidate instructions | 192 |
| Common prefix | 9 / 188 |
| Masked operands | 32 clean, 0 unresolved, 0 mismatched |

The scratch recovers the full source-level archive/filesystem behavior without
factoring away the native duplicated archive read/decode paths.

## Remaining mismatch shape

- Archive scan register ownership differs: target uses `edx` for the archive
  cursor and `cl` for the archive byte; candidate uses `ecx` and `dl`.
- C++ codegen cleans `ftell` and `_getcwd` arguments earlier than native, which
  batches those stack slots with the later `fseek`/`report_messagef` calls.
- Equivalent loop-exit and fallback labels differ after the first archive-index
  null/count checks.
