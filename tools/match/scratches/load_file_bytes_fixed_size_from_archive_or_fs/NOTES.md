# load_file_bytes_fixed_size_from_archive_or_fs

Initial source-shaped scratch for the fixed-size archive/filesystem loader at
`0x431030`.

The helper first ticks `g_loading_screen`, scans the loaded archive index with
the same case folding as `find_archive_entry`, and either returns the archived
data offset for the `buffer == (char*)-1` sentinel or reads exactly the caller's
requested byte count into the supplied/allocated buffer. The filesystem fallback
keeps the native `get_stream_length_preserve_position` call even though this
fixed-size variant ignores the returned length.

Focused matcher result: 81.05%, 192 candidate instructions versus 188 target
instructions, 9-instruction prefix, and 32 clean masked operands.

Known residuals:

- native keeps the archive path cursor in `edx` and current archive byte in
  `cl`, while this C++ scratch keeps them in `ecx`/`dl`;
- native coalesces the `ftell` and `_getcwd` stack cleanup into later CRT and
  report calls, while this C++ scratch emits local `add esp` cleanup;
- the native loop exits as `jl scan; jmp filesystem_fallback`, while this
  scratch emits the equivalent inverted test plus explicit jump.
