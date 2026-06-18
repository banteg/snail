# save_file_bytes_with_optional_archive_scramble @ 0x4052a0

Writes one byte buffer to the filesystem, optionally applying the archive
scramble in place before opening the destination. The success path logs the
write, writes the bytes, and closes the stream. The failure path captures the
current directory and reports the save failure.

Focused match: 100%, 56/56 instructions, with ten clean masked operands.

This scratch compiles as C (`/TC`). C-mode MSVC 6.5 keeps the `_getcwd`
arguments live across the failure `printf` argument setup, coalescing cleanup
into the native `add esp, 0x14`. The source keeps C/C++ compatible opaque
`File` declarations and uses a top-of-function `File* file` local for C89
declaration ordering.
