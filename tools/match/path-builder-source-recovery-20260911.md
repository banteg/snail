# Path-builder source recovery

Nine existing path-builder scratches improve. **All remain partial**; no exact
matches are added, and `body_byte_exact` is false for every retained candidate.

| Builder | Before | After | Instructions before → after / native | Clean aligned references |
| --- | ---: | ---: | --- | ---: |
| `dump` | 82.81% | 94.56% | 689 → 689 / 690 | 43 |
| `turnoverdouble` | 75.72% | 94.27% | 683 → 682 / 680 | 46 |
| `turnover` | 69.60% | 78.12% | 671 → 673 / 671 | 41 |
| `dip` | 66.46% | 75.96% | 642 → 643 / 655 | 37 |
| `wibble` | 80.10% | 89.14% | 608 → 608 / 608 | 39 |
| `hill_valley` | 83.92% | 97.60% | 669 → 668 / 668 | 41 |
| `loopout` | 68.15% | 72.68% | 723 → 724 / 718 | 52 |
| `hump` | 79.80% | 92.57% | 686 → 687 / 685 | 43 |
| `halfpipe` | 68.96% | 75.41% | 688 → 688 / 707 | 55 |

The curated-extent weighted fuzzy gap falls by **2,345.88 bytes**.
Core fuzzy progress rises from **89.54% to 90.32%**. This metric describes
instruction similarity; it is not newly byte-matched code.

## Recovered source structure

The common gain is separating face UV assignment from texture selection. The
two phases remain in the same face iteration and preserve geometry, textures,
UV values, and call order. Their source separation recovers native continuations
after the function return. It is retained only where the full function improves:
the same transfer regresses Invert, whose source is unchanged.

### dump

The retained changes recover separate face UV dispatch, physical sample-bank delta traversal, and a shared logical counter with a count-relative departure bound.

The lead receiver, departure schedule, curve preheader, and vertex temporary allocation still differ.

### turnoverdouble

The retained source uses branch-local mesh vectors, separate UV dispatch, one curve counter, nested roll sine evaluation, an aggregate secondary offset, and physical delta traversal.

The native departure bound still differs: the candidate derives a separate loop counter. Curve preheader and scalar-store scheduling also remain different.

### turnover

The retained changes recover branch-local mesh vectors, physical delta traversal, and nested full-angle/half-angle sine evaluation. The original face structure remains stronger for this builder.

Receiver calculations, register/stack allocation, curve scheduling, and mesh/face details still differ.

### dip

The retained change recovers the ordinary/terminal vertex lifetimes and separates face UV assignment from texture selection.

Endpoint index allocation, previous-sample orientation ownership, and curve/mesh scheduling still differ. Direct physical orientation and delta controls do not improve this retained body.

### wibble

Separate face UV dispatch and branch-local mesh vectors improve this fixed 32-sample builder. Its indexed curve and existing delta loop remain stronger than the tested physical-counter forms.

Curve phase lifetime, transform-copy addressing, loop termination, and delta traversal still differ despite equal total instruction counts.

### hill_valley

The retained source separates face UV dispatch, uses branch-local mesh vectors and physical delta traversal, and guards previous-sample orientation by the native byte offset. Testing parity-bit equality recovers both native texture branch directions while preserving the equal-texture arms.

Endpoint logical-index retention, scaling order, one secondary receiver calculation, and associated branch displacements remain different.

### loopout

The retained change separates face UV assignment from texture selection while preserving the builder-specific vertices, ten-sample lead, four-sample departure, and curve/orientation source.

Stack-frame and temporary allocation, curve preheader/scheduling, and other native instructions still differ. Whole-mesh transfers and the tested physical curve counter do not improve this source.

### hump

The retained source separates face UV dispatch, uses physical delta traversal, shares the logical lead/departure counter, retains a count-relative departure bound, and places the lead Z conversion and curve initialization in the native source contexts.

Lead/departure receiver calculations, departure-bound scheduling, curve secondary receiver, and mesh scheduling still differ.

### halfpipe

The retained source separates face UV dispatch and traverses the 34 middle samples with a byte offset, using vector subtraction for the forward basis. Kind-42 attachment transforms and radius-dependent vertex adjustment are preserved.

Lead/exit temporary lifetimes, departure addressing, middle/delta scheduling, and custom mesh details still differ. Applying physical traversal to the departure phase regresses the body.

## Evidence and limits

Compiler `msvc6.5`, `/O2 /G5 /W3`, shared headers, ABI, matcher rules, and tests
are unchanged. Helper boundaries and counter ownership are reconstructed source
forms, not claims about the uniquely original source. No register directives,
inline assembly, volatile barriers, or invented side effects are introduced.

Clean aligned references do **not** establish positional identity. The receipt
preserves every reference entry; the counts below separate these properties.

| Builder | Aligned | Same instruction index | Same byte offset | Compared bytes | Excluded terminal padding |
| --- | ---: | ---: | ---: | --- | --- |
| `dump` | 43 | 12 | 17 | [0, 2563) | [2563, 2576) |
| `turnoverdouble` | 46 | 8 | 8 | [0, 2458) | [2458, 2464) |
| `turnover` | 41 | 12 | 8 | [0, 2433) | [2433, 2448) |
| `dip` | 37 | 2 | 5 | [0, 2390) | [2390, 2400) |
| `wibble` | 39 | 23 | 17 | [0, 2213) | [2213, 2224) |
| `hill_valley` | 41 | 27 | 27 | [0, 2447) | [2447, 2448) |
| `loopout` | 52 | 40 | 40 | [0, 2615) | [2615, 2624) |
| `hump` | 43 | 6 | 15 | [0, 2553) | [2553, 2560) |
| `halfpipe` | 55 | 21 | 15 | [0, 2592) | none |

There are no unexplained target ranges. Post-return continuations remain in the
comparison. Only recognized terminal padding is excluded; Halfpipe compares its
entire curated extent. Equal instruction counts in Hill/Valley and Wibble are
not equality of their bodies.

The [complete receipt](path-builder-source-recovery-20260911.json) contains the
native-image hash, before/after sources and hashes, compilation identities,
comparison ranges, reference audits, and complete remaining assembly diffs.
Each retained promotion has an experiment-ledger record. Ten bounded controls
also retain their full source, hash, measured result, and diff for replay.

The last controls tested phase/helper ownership, physical counters, endpoint
lifetimes, and parity forms suggested by the native differences. They explain
why the retained source differs by builder. They do not prove source exhaustion
or a compiler limitation; the residual descriptions identify what remains open.

## Reproduce and validate

Replay a retained source by writing its `source` field from the receipt to a
temporary file, checking `source_sha256`, and running:

```sh
uv run snail match probe FUNCTION --source FILE
uv run snail match status --check -j 8
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```

The full status check succeeds, and comparison of all **785 function rows**
changes exactly these nine builders. Exact totals remain **572/662 core** and
**110/120 platform**. All **1,016 tests pass** without test changes. The strict
ledger checks 2,449 records and the specification check finds 13 active runnable
specifications, with zero errors. `git diff --check` is clean.
