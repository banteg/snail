# Math storage and executable integration

The initializer and lookup helpers now share two actual 8192-float arrays.
The earlier `g_cosine_table_init_base` and `g_sine_table_init_base` declarations
were compiler relocation bases, not independently owned storage.

The native initializer at `0x44c930` increments its index before both stores:
`0x44c955` addresses `0x777f38 + index*4`, and `0x44c95e` addresses
`0x77ff88 + index*4`. The loop covers incremented indices 1..8192. These
therefore write exactly the canonical arrays at `0x777f3c` and `0x77ff8c`.
The preceding words belong to Cross's static guard/result storage and must
not be separately allocated as trigonometry arrays.

A conventional zero-based `for` loop over the canonical arrays reproduces
all 18 native instructions. VC6 itself emits each array relocation with an
addend of -4. The reference manifest records the proven 0x8000-byte extents
and only that one prebase displacement. Its ordinary operand audit validates
both stores; no normalization or comparison rule changed. A direct rewrite
that kept the previously reconstructed two-index loop did not match and was
rejected. A zero-based do-loop is equivalent to the retained for-loop.

`rmath_tables.h` supplies shared declarations for those arrays and the existing
8191-entry random table/cursor. The initializer, sine, cosine, random-table
initializer, and random reader all remain exact with clean references.
Binary Ninja now has the corresponding four typed/named data variables;
`tools/binja/sync_rmath_storage.py` verifies the native store bytes and provides
a repeatable preview/apply path.

## The executable check

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/link_path_math.py \
  --group rmath --run --out artifacts/match/rmath-run \
  --runtime-library /path/to/vc6/MSVCRT.LIB
```

This compiles fourteen exact recovered functions (1,118 native body bytes)
as separate objects, adds real storage definitions and a test harness, and
links a console executable through the VC6 `mainCRTStartup` entry. It uses
the same existing runtime import library as the previous link check. There
are no unresolved-symbol overrides, source-function substitutes, or copied
native code.

The linked PE/map verifier checks all non-relocation bytes, thirteen REL32
destinations, and 27 named data relocations. That includes independently
checking the two -4 array addends against the linked array symbols. Local
static data references absent from the link map remain explicitly listed as
not map-verified.

Under Wibo, 23 integration checks pass. They cover the first/last and
quarter-turn trigonometry samples, the lookup helpers, the RNG's advance-before-
read and 8191-call wraparound, both Cross input-alias cases, both Dot ABIs,
normalization including zero/source-copy behavior, square root, identity, and
rigid matrix inversion. A second process deliberately corrupts sine sample
zero; it reports exactly one failed check and exits with status 1. The normal
run reports zero failures and exits 0. The driver requires both results and
their completion markers, so an empty successful process exit cannot pass.

The earlier exploratory run needed explicit `fflush(0)` for its CRT output
to survive Wibo's exit path. A separate temporary return-37 control established
that the process did reach `main`; it is not retained in the test harness.

This validates the selected math operations on Wibo, not Windows-native
gameplay or original BSS placement. `CalcLengthZ` is linked but is not yet
exercised by this harness. The test program and storage support receive no
matching credit, and the public executable's linked measure remains zero.
The generated receipt records code/source identities, linker/runtime hashes,
verified relocations, runtime exit codes, and both captured test summaries.
