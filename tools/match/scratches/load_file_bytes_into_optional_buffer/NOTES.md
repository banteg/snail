# load_file_bytes_into_optional_buffer @ 0x4051d0

Loads a filesystem file into either the caller-provided buffer or a freshly
allocated buffer, then optionally writes the byte count to the out parameter.
The missing-file path captures the current directory and reports a warning.

Focused match: 100%, 56/56 instructions, with nine clean masked operands.

This scratch was first matched as C (`/TC`) for the same `_getcwd`/`printf` cleanup shape
used by `save_file_bytes_with_optional_archive_scramble`.

2026-07-15 CRT ownership: VC6's `<stdio.h>`, `<stdlib.h>`, and `<direct.h>` now
own `FILE`, the stream calls, `malloc`, and `getcwd`. Removing the opaque
scratch `File` and six approximate declarations preserves the exact 56/56
instruction object and all nine masked operands.

## 2026-10-05 compiler baseline

The C-mode choice compensated for the SP5 C++ frontend. Under the corrected
baseline, msvc6.3, the unchanged source is exact as C++, and its object is
C++; see the [compiler identification](../../compiler-identification-20261005.md).
