# load_file_bytes_into_optional_buffer @ 0x4051d0

Loads a filesystem file into either the caller-provided buffer or a freshly
allocated buffer, then optionally writes the byte count to the out parameter.
The missing-file path captures the current directory and reports a warning.

Focused match: 100%, 56/56 instructions, with nine clean masked operands.

This scratch compiles as C (`/TC`) for the same `_getcwd`/`printf` cleanup shape
used by `save_file_bytes_with_optional_archive_scramble`.
