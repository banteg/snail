# load_file_bytes_from_archive_or_fs match result

## Score

| Metric | Result |
|---|---:|
| Match | 79.23% |
| Target instructions | 206 |
| Candidate instructions | 208 |
| Common prefix | 10 / 206 |
| Masked operands | 31 clean, 0 unresolved, 0 mismatched |

The scratch recovers the variable-size archive/filesystem loader behavior:
inline archive name scan, optional `out_size`, the `buffer == (char*)-1`
data-offset sentinel, archive decode, and filesystem fallback.

## Remaining mismatch shape

- The archive scan and found-entry body now recover the native register
  ownership and field contract.
- VC6 lays out the filesystem-open failure block before the archive-found body;
  this equivalent source emits it after the archive return paths.
- Lowercase folding uses the equivalent `add al, 0xe0` encoding instead of
  native `sub al, 0x20`.
- CRT stack cleanup around `_getcwd` remains locally scheduled instead of
  coalesced with the following report call.
