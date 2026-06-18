# load_file_bytes_from_path @ 0x42f490

Loads bytes directly from the filesystem into either a caller-provided buffer or
a freshly allocated buffer. A nonzero `byte_count` parameter is used directly;
zero asks `get_stream_length_preserve_position` for the full file size.

Focused match: 100%, 59/59 instructions, with nine clean masked operands.

The missing-file path mirrors the other file helpers by capturing `_getcwd` and
printing the warning, so this scratch compiles as C (`/TC`) to preserve the
native cleanup shape.
