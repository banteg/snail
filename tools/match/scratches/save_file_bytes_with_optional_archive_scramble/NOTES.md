# save_file_bytes_with_optional_archive_scramble @ 0x4052a0

Writes one byte buffer to the filesystem, optionally applying the archive
scramble in place before opening the destination. The success path logs the
write, writes the bytes, and closes the stream. The failure path captures the
current directory and reports the save failure.

Focused match: 100%, 56/56 instructions, with ten clean masked operands.

This scratch compiles as C (`/TC`). C-mode MSVC 6.5 keeps the `_getcwd`
arguments live across the failure `printf` argument setup, coalescing cleanup
into the native `add esp, 0x14`.

2026-07-15 CRT ownership: the scratch now gets `FILE`, the stream calls,
`printf`, and `getcwd` from VC6's authentic `<stdio.h>` and `<direct.h>` headers.
The top-of-function `FILE*` local retains C89 ordering, and removing the opaque
`File` plus five hand-written declarations preserves the exact 56/56 object and
all ten masked operands.
