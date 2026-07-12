# load_galaxy_layout match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **88.27%** |
| Target instructions | 233 | 233 |
| Candidate instructions | 0 | **236** |
| Common prefix | 0 / 233 | **62 / 233** |
| Masked operands | none | **39 clean, 0 unresolved, 0 mismatched** |

The retained scratch is three instructions longer than the target. Every
masked call, string, and data operand is resolved and clean.

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
- Uses the recovered void contract and the parser/bootstrap portion of mobile
  `cRGalaxy::Open(int)`; Windows split the interactive card behavior into exact
  `open_galaxy_route`, corresponding to mobile `cRGalaxy::BoxOn(int)`.

## Remaining residuals

- Native compares the stored star count from memory after clobbering `eax` with
  the white color constant; VC6 keeps the parse result live in this scratch.
- Native reloads the route-point cursor into `ebp` before the outer backedge;
  VC6 currently compares it in `eax` and moves it into `ebp` only on continue.
- One parser error tail remains before the successful epilogue instead of both
  cold tails following it. Explicit labels recover the correct string/call
  identities without forcing the remaining block placement.
