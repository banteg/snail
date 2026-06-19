# load_galaxy_layout match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **77.94%** |
| Target instructions | 233 | 233 |
| Candidate instructions | 0 | **234** |
| Common prefix | 0 / 233 | **38 / 233** |
| Masked operands | none | **33 clean, 7 unresolved, 0 mismatched** |

The retained scratch is one instruction longer than the target. All masked
operands are clean or unresolved symbol labels for the real point tables and
star-position tables; there are no mismatched calls, strings, or data operands.

## Covered behavior

- Rescales both authored galaxy point tables with the native `0.8`, `240`,
  `0.93`, and `250` constants.
- Loads `Galaxy/_Galaxy.txt` through `load_file_bytes_from_archive_or_fs` using
  the archive data base as the output buffer.
- Scans `Galaxy%i:`, quoted galaxy names, and `StarNumber=` entries.
- Seeds the route-name table colors, map positions, and per-star route records.
- Writes `"LEVEL %i MISSING"` placeholders into both route text buffers.
- Initializes the first route record to the first authored point and clears its
  text buffers.

## Remaining residuals

- Native keeps the inner star counter in `ebx` and the star-group offset in a
  stack slot. This scratch currently gives those roles to different storage,
  which shifts the inner-loop register scheduling.
- Native compares the stored star count from memory after clobbering `eax` with
  the white color constant; VC6 keeps the parse result live in this scratch.
- The final success block is semantically correct but laid out after the error
  returns instead of as the direct fall-through after the outer loop compare.
