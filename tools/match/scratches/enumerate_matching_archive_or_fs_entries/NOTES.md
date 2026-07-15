# Scratch status

Initial structure-first scratch for `enumerate_matching_archive_or_fs_entries @ 0x431740`.

Baseline focused matcher result: 49.60%, 189 candidate instructions versus 182
target instructions, 0-instruction prefix, and 23 clean masked operands.

Current focused matcher result: 81.52%, 186 candidate instructions versus 182
target instructions, 7-instruction prefix, and 26 clean masked operands.

Recovered behavior:

- if the DAT archive index is loaded, scan `ArchiveIndex` records;
- match `directory` against the archive path prefix case-insensitively, then require a `/`;
- apply the simple `*` wildcard pattern to the basename;
- copy matching basenames into 128-byte output slots and publish the count through `out_count`;
- otherwise save cwd, try to enter the requested directory, enumerate filesystem matches with `_findfirst`/`_findnext`, then restore cwd.

The native does not close the find handle in this routine. The scratch keeps that behavior.

Retained source-shape choices:

- model the function as `void`; callers ignore `eax`, and the observed return values are incidental leftovers from the archive pointer, count, or `chdir`;
- keep `_finddata_t::name` at `+0x14`, matching the native copies from the stack record;
- model each caller-owned output record as the shared 128-byte
  `DirectoryEntryName`, matching the iOS `RShellReadDirectory` signature
  without changing code generation;
- scope the archive byte offset to the guarded record loop and rebind the local `ArchiveIndex*` from `g_archive_index_records` at the loop tail; this recovers the native `0x324` frame, pre-frame `eax` load, and archive-only `ebx`/`ebp` saves, raising the match from 49.60% to 71.39%;
- compare the archive path through the advancing cursor directly, recovering the native `ecx`/`dl`/`al` register lanes and raising the match to 80.98%;
- initialize the basename index before the pattern index, matching the native `edi`/`esi` zeroing order and raising the match to 81.52%;
- keep the archive prefix comparison inline, but call the exact `ascii_upper_if_lowercase` helper for wildcard matching;
- keep only one named folded-byte temporary and inline the pattern fold call, reflecting the native stack model without manufacturing a spill;
- curate `g_enumerated_entry_count`, `_findfirst`, and `_findnext` in `analysis/symbols/gameplay-references.json` after BN confirmed the xrefs and wrapper behavior.

Remaining source-shape debt:

- the native keeps the pattern byte in `bl` and spills the folded basename byte, while this equivalent source keeps the folded basename byte in `bl` and spills the pattern byte;
- that allocation choice also makes the compiler hoist the next pattern-byte load at the wildcard-loop tail, leaving four extra candidate instructions and shifted branch labels;
- the inline ASCII fold compiles as `add al, 0xe0` instead of the native-equivalent `sub al, 0x20`.

These residuals are compiler allocation and expression-form differences. Forcing
the spill with `volatile`, a dummy local, or inline assembly would be
fakematching, so the scratch leaves them visible.

Cross-port ownership:

- iOS `RShell.o` supplies the exact public signature
  `RShellReadDirectory(char*, char*, int*, char (*)[128])`, proving the
  caller-owned 128-byte output records.
- The iOS entry is an empty platform stub, while Windows implements the
  DAT/filesystem enumeration locally; no body equivalence is claimed beyond
  the shared public contract.

2026-07-15 CRT ownership closure:

- The filesystem record is the bundled MSVC6 CRT's real `struct _finddata_t`,
  not a Snail Mail-owned `FindData`. Its `time_t` and `_fsize_t` fields keep the
  native 32-bit ABI, placing `name[260]` at `+0x14` in the `0x118`-byte record.
- The scratch now includes `<io.h>` and `<direct.h>` and calls the authored
  `_findfirst`, `_findnext`, `_getcwd`, and `_chdir` interfaces with the CRT's
  real `long` search handle. No project-local compatibility header is added for
  a third-party-owned layout.
- Focused matching is byte-stable at 81.52%, 186/182 candidate/target
  instructions, 7/182 prefix, and 26 clean operands. The local-type inventory
  no longer reports the retired synthetic `FindData` owner.

Rejected probes:

- branching to the filesystem path before clearing `g_enumerated_entry_count` regressed to 34.41%;
- using the global directly throughout the archive loop regressed to 37.84%; the retained local rebind at the loop tail is the native ownership shape;
- changing the function to return `int` and adding explicit incidental returns regressed to 48.26%;
- keeping `pattern_char` live across the full wildcard loop regressed to 50.41% and expanded the frame to `0x328`;
- default C++ mode emitted the same code as explicit `/TC`, so the scratch keeps the clearer C-mode build.
