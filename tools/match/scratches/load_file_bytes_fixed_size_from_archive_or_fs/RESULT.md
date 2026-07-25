# load_file_bytes_fixed_size_from_archive_or_fs match result

## Score

| Metric | Result |
|---|---:|
| Match | 92.84% |
| Target instructions | 188 |
| Candidate instructions | 189 |
| Common prefix | 9 / 188 |
| Masked operands | 32 clean, 0 unresolved, 0 mismatched |

The scratch recovers the full source-level archive/filesystem behavior without
factoring away the native duplicated archive read/decode paths.

## Remaining mismatch shape

- VC6 encodes the uppercase fold as equivalent `add al, 0xe0` instead of
  native `sub al, 0x20`.
- C++ codegen cleans `_getcwd` arguments earlier than native, which batches
  that stack slot with the later `report_messagef` call.
- Equivalent loop-exit and filesystem-fallback blocks remain laid out
  differently after the archive scan.

The archive cursor, selected entry, data offset, saved stream position, and
both output-buffer ownership paths are now recovered without artificial
register shims.
