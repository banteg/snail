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
scratch (no `goto found`) collapses to 33.84%. Keep the goto-split archive vs
filesystem topology.

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
