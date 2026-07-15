# load_file_bytes_from_path @ 0x42f490

Loads bytes directly from the filesystem into either a caller-provided buffer or
a freshly allocated buffer. A nonzero `byte_count` parameter is used directly;
zero asks `get_stream_length_preserve_position` for the full file size.

Focused match: 100%, 59/59 instructions, with nine clean masked operands.

The missing-file path mirrors the other file helpers by capturing `_getcwd` and
printing the warning, so this scratch compiles as C (`/TC`) to preserve the
native cleanup shape.

2026-07-15 CRT ownership: `<stdio.h>`, `<stdlib.h>`, and `<direct.h>` now own
`FILE`, the stream operations, `malloc`, and `getcwd`. Removing the opaque
scratch `File` and six approximate declarations keeps the exact 59/59 object
and all nine masked operands.
