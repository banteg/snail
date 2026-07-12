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

- the decoded DAM allocation has an `ArchiveIndex` view whose `count` owns loop termination and whose `ArchiveEntry[1]` begins the 12-byte serialized record array;
- a typed `ArchiveEntry*` establishes the record-array base before the header copy, while the hot loop keeps the native byte-count-field cursor so `[-2]`, `[-1]`, and `[0]` remain the path offset, data offset, and byte count;
- the rebuilt output cursor begins at the first entry's `data_offset` field and advances by `sizeof(ArchiveEntry)`; the source-to-output base delta updates the corresponding serialized byte count;
- `TgaImageView` now names the complete TGA header fields and inline pixel owner instead of treating the payload as raw byte offsets; its padded size remains the native `0x14` used by the converted payload calculation;
- `load_png_image @ 0x42f0a0` is a seven-argument `cdecl` used only here. Direct disassembly reads arguments at `[ebp+8]` through `[ebp+0x20]`; Binary Ninja's extra `esi`/`edi` parameters are a bad auto-prototype induced by the helper's `setjmp` path, not hidden caller arguments.

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
