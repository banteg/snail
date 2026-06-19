# load_file_bytes_from_archive_or_fs match result

## Score

| Metric | Result |
|---|---:|
| Match | 65.71% |
| Target instructions | 206 |
| Candidate instructions | 211 |
| Common prefix | 10 / 206 |
| Masked operands | 31 clean, 0 unresolved, 0 mismatched |

The scratch recovers the variable-size archive/filesystem loader behavior:
inline archive name scan, optional `out_size`, the `buffer == (char*)-1`
data-offset sentinel, archive decode, and filesystem fallback.

## Remaining mismatch shape

- Archive scan register ownership differs: target uses `edx`/`cl`; candidate
  uses `ecx`/`dl`.
- Equivalent archive-found and filesystem-fallback blocks are laid out with
  different label identities.
- CRT stack cleanup around `ftell`/`_getcwd` remains locally scheduled in the
  scratch instead of batched with later calls.
