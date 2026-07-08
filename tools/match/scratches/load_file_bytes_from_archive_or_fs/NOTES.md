# load_file_bytes_from_archive_or_fs

Initial source-shaped scratch for the variable-size archive/filesystem loader at
`0x4312d0`.

This is the size-reporting sibling of
`load_file_bytes_fixed_size_from_archive_or_fs`: it ticks the loading screen,
scans `g_archive_index_records` inline, writes the selected archive or filesystem
byte count through `out_size`, handles the `buffer == (char*)-1` data-offset
sentinel, and otherwise reads/decrypts into either the supplied buffer or a
tracked allocation.

Focused matcher result: 65.71%, 211 candidate instructions versus 206 target
instructions, 10-instruction prefix, and 31 clean masked operands.

Known residuals:

- native keeps the archive path cursor in `edx` and current archive byte in
  `cl`, while this C++ scratch keeps them in `ecx`/`dl`;
- native lays out the filesystem-open failure path between the archive scan and
  archive-found body, then places filesystem success after the archive return
  paths; this source spells the same topology but VC6 still chooses different
  label identities;
- native coalesces `ftell` and `_getcwd` stack cleanup into later calls, while
  this C++ scratch emits local cleanup for those call sites.

2026-07-09 sibling-transfer campaign: fixed-size `while (*archive_cursor)`
compare still regresses this helper to 61.39%. Goto-scan loop packaging is
codegen-neutral at 65.71%. Inlining the found-entry body like the fixed-size
scratch (no `goto found`) collapses to 33.84%. Keep the goto-split archive vs
filesystem topology.
