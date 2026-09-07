# `rebuild_game_archive_if_needed`

Archive rebuild helper at `0x405370`.

Baseline focused matcher result: 50.54%, 227 candidate instructions versus 232
target instructions, no common prefix, and 19 clean masked operands plus one
mismatched call.

Current focused matcher result: 66.38%, 232/232 instructions, a 5-instruction
prefix, and 22 clean masked operands with no unresolved or mismatched references.

Recovered behavior:

- returns immediately when `SnailMail.dat` already exists, or when `SnailMail.dam` is absent;
- allocates a 40,000,000-byte rebuild buffer and loads `SnailMail.dam`;
- toggles the DAM high-bit encoding in place, copies the archive header/index region into the rebuild buffer, and starts appending payload bytes at the header size stored at offset `+8`;
- walks 12-byte archive records: path offset, source data offset, byte count;
- TGA-class entries are written to `0.png`, loaded through the PNG/image helper, converted into a bottom-up BGR(A) TGA-like payload with a 20-byte native header, and their rebuilt byte count is updated;
- all other entries are copied byte-for-byte from the DAM payload;
- payload alignment keeps the native signed remainder expression instead of normalizing to conventional padding;
- writes `SnailMail.dat`, deletes `SnailMail.dam` and `0.png`, then frees the rebuild buffer.

Recovered ownership:

- the decoded DAM allocation has a `SerializedArchiveIndex` view whose `count`
  owns loop termination and whose `SerializedArchiveEntry[1]` begins the
  12-byte record array;
- `SerializedArchiveEntry::path_offset` is distinct from the rebased
  `ArchiveEntry::path` used by the live DAT index. A typed serialized-entry
  base establishes that lifecycle before the header copy, while the hot loop
  keeps the native byte-count-field cursor so `[-2]`, `[-1]`, and `[0]` remain
  the path offset, data offset, and byte count;
- the rebuilt output cursor begins at the first entry's `data_offset` field and advances by `sizeof(ArchiveEntry)`; the source-to-output base delta updates the corresponding serialized byte count;
- `TgaImageView` now names the complete TGA header fields and inline pixel owner instead of treating the payload as raw byte offsets; its padded size remains the native `0x14` used by the converted payload calculation;
- `load_png_image @ 0x42f0a0` is a seven-argument `cdecl` used only here. Direct disassembly reads arguments at `[ebp+8]` through `[ebp+0x20]`; Binary Ninja's extra `esi`/`edi` parameters are a bad auto-prototype induced by the helper's `setjmp` path, not hidden caller arguments. The sixth argument receives the optional PNG `bKGD` color, and the seventh is an integer file offset.

Retained source-shape gains:

- keeping the typed source-entry base live through the initial header copy recovers the native `0x234` frame and exact candidate instruction count;
- retaining the base-to-base source/output delta raises the focused match from 63.23% to 66.38%;
- initializing the named TGA fields in native order raises the original scratch from 50.54% to 56.21% before the archive-record ownership changes;
- curating the PNG helper resolves the previous masked call mismatch, leaving 22 clean references.

Remaining source-shape debt:

- VC6 folds the rebuilt data-offset cursor into a second source-cursor delta, while native spills and advances the output cursor independently;
- that allocation choice shifts the width, height, and x locals even though the header and bottom-up BGR(A) copy semantics agree;
- native decrements the extension classifier result before branching and uses different registers for the signed remainder expressions; spelling those schedules explicitly would not recover additional ownership.

No inline assembly, `volatile` spills, stack padding, dummy symbols, fake aliases,
or normalizer-specific tricks are used.

## 2026-07-14 serialized archive ownership

The archive loader proves two phases for the first record word: decoded DAT/DAM
bytes hold a file-relative `path_offset`, and `load_archive_index` adds the
allocation base before publishing the records as the live `ArchiveIndex` whose
first word is a `char* path`. The DAM rebuild never performs that rebase, so it
now uses the separate `SerializedArchiveIndex`/`SerializedArchiveEntry` owner.
This removes a false pointer interpretation without changing the proven native
byte-count cursor or generated code.

## 2026-07-25 replayed rebuild lifetimes

Both decompilers now carry the decoded source and rebuilt destination as
distinct `SerializedArchiveIndex*` owners, with durable names for the record
cursors, source-to-destination byte delta, entry path/stem, TGA row offsets,
PNG allocation, dimensions, and channel count. The adjacent `printf` and
`free` calls are curated too, so the exported function no longer hides those
ownership endpoints behind raw subroutine names.

The sole callsite and direct callee disassembly also correct
`load_png_image @ 0x42f0a0` to an ordinary seven-argument `cdecl`.
Binary Ninja's former synthetic `esi`/`edi` arguments came from analysis around
the callee's `setjmp`; they are not arguments passed by this function. IDA
local inspection now reports definition addresses and exact stack offsets, so
the replay keys these owners to observed lifetimes instead of guessed slots.

The focused object remains honestly codegen-neutral at 66.38%, 232/232
instructions, a five-instruction prefix, and 22 clean masked operands. The
remaining output-cursor register allocation was not coerced with spills,
aliases, or other fakematching.

## 2026-08-11 destination record cursor recovery

The destination cursor is now typed to the field it actually owns:
`SerializedArchiveEntry::data_offset`. It starts at the first output record's
`data_offset`, writes the rebuilt payload displacement directly, and advances
by one 12-byte `SerializedArchiveEntry`. This replaces an anonymous `char*`
plus casts without changing generated code: focused matching remains 66.38%,
232/232, with 22 clean references.

iOS `DatBuild() @ 0x0000986c` independently preserves the same two-cursor
contract. It writes the payload displacement at destination record `+8`, then
advances the source record by three words and the destination record by
`0x0c`. That is direct cross-port evidence for the distinct typed destination
cursor, while Windows remains authoritative for layout and code generation.
A source `switch` for the extension class was also tested because native
decrements the classifier result before its branch; VC6 regressed to 55.41%,
so the semantic TGA comparison remains.


## 2026-09-07 serialized archive ownership investigation

Eight recorded recipes (129 source forms) test actual source/output record
ownership, loop initialization, extension dispatch, signed remainder, and PNG
result lifetimes. The iOS `DatBuild()` body at 0x986c corroborates the archive
rebuilding responsibility and C++ language, but the current mobile crosswalk
still reports this Windows target as unverified. The port is contract evidence,
not proof of the Windows object compiler or exact pixel-buffer behavior.

A plain C++ control initially falls to 25.22% because the handwritten libc
prototypes introduce C++ overloads instead of the genuine C declarations.
Including stdlib.h/string.h, or explicitly restoring C linkage, returns to the
canonical 66.38%, 232/232 instructions, prefix 5, and 22 clean references.
This separates declaration correctness from compiler version. No compiler
version is selected from that diagnostic.

The useful new seed keeps source and output SerializedArchiveEntry arrays,
uses a counted loop and an extension switch, and writes the native unusual
alignment as `payload_end + (int)payload_end % 4`. Those changes together
recover the early source-entry base, decrement-based extension dispatch, and
signed-remainder branch, reaching 73.43%. Shortening the output-entry base
lifetime with a positive-count guard reaches 73.87%, 231/232 instructions,
prefix 5, and all 22 references clean. Allocation-owner simplification and
removal of obsolete cursor locals are neutral at that seed. Earlier PNG-result
initialization reaches 74.03%, but shrinks the body again to 230 instructions.

These are retained diagnostic seeds, not promoted score-only gains: the
canonical source has no instruction-count gap, while the new forms omit one
or two native instructions and still allocate several live locals differently.
The 73.87% source is reproducible from
`output-entry-base-and-header-copy-lifetimes-20260907.json`, candidate
`output-base/before-loop-guarded-for`; the subsequent cleanup recipe removes
unused cursor declarations without changing codegen. Keep the actual Windows
payload layout, signed remainder behavior, and missing PNG-free behavior; do
not import differing iOS allocation or cleanup behavior.
