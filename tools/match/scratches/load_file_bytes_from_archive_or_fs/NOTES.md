# load_file_bytes_from_archive_or_fs

Initial source-shaped scratch for the variable-size archive/filesystem loader at
`0x4312d0`.

This is the size-reporting sibling of
`load_file_bytes_fixed_size_from_archive_or_fs`: it ticks the loading screen,
scans `g_archive_index_records` inline, writes the selected archive or filesystem
byte count through `out_size`, handles the `buffer == (char*)-1` data-offset
sentinel, and otherwise reads/decrypts into either the supplied buffer or a
tracked allocation.

Earlier focused matcher result: 65.71%, 211 candidate instructions versus 206
target instructions, 10-instruction prefix, and 31 clean masked operands.

Known residuals after the current ownership pass:

- native lays out the filesystem-open failure path between the archive scan and
  archive-found body; this source has the same control-flow topology, but VC6
  still places the fallback after the archive return paths;
- lowercase folding remains the equivalent `add al, 0xe0` instead of native
  `sub al, 0x20`;
- native coalesces `_getcwd` stack cleanup into the following report call,
  while this scratch cleans that call locally.

2026-07-09 sibling-transfer campaign: fixed-size `while (*archive_cursor)`
compare still regresses this helper to 61.39%. Goto-scan loop packaging is
codegen-neutral at 65.71%. Inlining the found-entry body like the fixed-size
scratch (no `goto found`) collapsed to 33.84% under the ownership model used
at that time. The 2026-08-11 replay below supersedes that source-shape
conclusion after the archive-entry and stream-position lifetimes were fixed.

2026-07-12 archive-entry and stream-position ownership:

- The inline archive scan now reads the current archive byte directly through
  its advancing path cursor. Combined with the recovered read-path lifetimes,
  this restores native's `edx` cursor and `cl` byte lanes; the older isolated
  direct-cursor regression no longer applies.
- Both archive read paths own the current `ftell(g_archive_file)` position
  before constructing the relative `fseek`. The allocation path computes the
  entry byte count before allocating and defers the data offset until after
  `ftell`; the caller-buffer path defers its byte count until after `fseek`.
- Raw `3 * index` byte arithmetic is replaced by the recovered 12-byte
  `ArchiveEntry` contract. `byte_count` owns the optional size result,
  allocation size, and read/decode length; `data_offset` owns the sentinel
  return, archive seek target, and XOR seed.
- These changes raise focused Wibo from 65.71% to 79.23% (208/206
  instructions, 10/206 prefix, 31 clean masks, no unresolved operands or
  mismatches). The archive-found body now normalizes identically; the remaining
  diff is the filesystem-fallback layout and the two compiler encodings noted
  above.

2026-07-12 cross-port ownership: iOS `RShell.o` names this public contract
`RShellLoadFile(char*, void*, int*)`. The live analysis database now carries
that destination and size-result ownership plus typed `ArchiveIndex` globals;
the focused source remains byte-oriented to preserve the proven Windows shape.

2026-07-15 CRT ownership: both the filesystem fallback and the shared DAT
stream now use VC6's real `FILE` owner and `<stdio.h>` function declarations;
`<direct.h>` owns `getcwd`, and the archive-position deltas use `SEEK_CUR`.
Removing the opaque scratch `File` type and six hand-written CRT declarations
is codegen-neutral: focused matching remains 79.23% with 31 clean masked
operands and the same control-layout, lowercase-fold, and cleanup residuals.

2026-07-25 archive/filesystem service ownership replay:

- The analysis-only opaque `File` owner now flows through `fopen`, `fread`,
  `fseek`, `ftell`, and `fclose` in both replay headers. It represents the
  same CRT stream without importing the CRT's private structure layout.
- IDA now distinguishes the 12-byte `ArchiveEntry` cursor and borrowed path
  cursors from the filesystem stream, tracked allocation, caller buffer, and
  512-byte cwd buffer. Separate archive-position and byte-count-offset
  lifetimes preserve the native register reuse instead of merging unrelated
  values under anonymous locals.
- The Binary Ninja replay records the corresponding exact SSA identities and
  names the previously anonymous `fread`, `getcwd`, and `chdir` callees.
  Post-prototype reanalysis also distinguishes the saved filesystem stream,
  tracked allocation result, archive positions, and byte counts instead of
  retaining stale pre-prototype register names.
- Focused matching remains 79.23%, 208/206 instructions, 10/206 prefix, and
  31 clean masked operands. No source-shape probe or fake match was introduced.

## 2026-08-11 archive-hit control-flow replay

The old inline-body rejection was stale. Replaying it after the 2026-07-12
entry and stream-position ownership fixes produces byte-identical code at
79.23%, with the same 208/206 instruction counts and the current 36 clean
masked operands. The retained source therefore handles the archive hit
directly inside the scan and lets filesystem fallback follow scan exhaustion,
removing the two decompiler-shaped `found_archive_entry` and
`filesystem_success` labels.

iOS `RShellLoadFile(char*, void*, int*) @ 0x0000d090` independently keeps the
size/sentinel/read handling inside its matching archive-entry branch and falls
through to filesystem loading only after the scan. Android delegates the scan
to `RShellDatFind`, so it corroborates the same service boundary without
constraining the Windows loop shape. The remaining Windows difference is still
compiler block placement plus the lowercase and `_getcwd` cleanup encodings;
the cleanup is semantic, not a score-only rewrite.

## 2026-09-07 exact platform loader recovery

Retained **100%, 206/206 instructions, full prefix, and 36 clean reference
operands**, up from 79.23%, 208/206, prefix 10. A normal `for` loop owns the
count guard and reads `archive_index->entries[entry_index].path` directly.
This removes the separately advanced path-field cursor and recovers the native
filesystem-failure placement. The inline archive-hit body remains structured;
no found flag or dispatch labels are retained.

The signed-input, unsigned-byte-result case fold transfers from the exact
archive lookup and fixed-size loader. The result is converted back to `char`
for the original comparison, preserving high-byte behavior. Allocation, size
publication, sentinel returns, seeks, reads, and decoding remain unchanged.

VC6 8168 C++ reproduces all native instructions. The same source under the
standard SP5-style C++ profile reaches 94.92%, 207/206, prefix 41, with all
36 references clean. Compiler selection is supported by the independently
verified RShell sibling evidence in
[the fixed-size loader profile record](../load_file_bytes_fixed_size_from_archive_or_fs/profile-evidence-20260907.md):
the executable has valid 8168 C++ contributions, and twelve unchanged nearby
controls match under that profile, six distinguishing it from SP5-style C++.
Both verified mobile ports name this contract `RShellLoadFile(char*, void*,
int*)` in `RShell.o`. These establish a supported reproduction profile and
C++ service relationship, not a proven original Windows object/build mapping.

Three source layouts using direct indexing are exact: inline hit handling and
two explicit continuation layouts. The simplest inline form is retained.
Independently advanced cursors, flat guards, search-result flags, structured
backend decisions, and explicit filesystem-success branches were insufficient
before changing the loop's entry ownership. Their hash-bound receipts remain
available as bounded negative controls.
