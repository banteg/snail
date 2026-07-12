# load_file_bytes_fixed_size_from_archive_or_fs

Initial source-shaped scratch for the fixed-size archive/filesystem loader at
`0x431030`.

The helper first ticks `g_loading_bar`, scans the loaded archive index with
the same case folding as `find_archive_entry`, and either returns the archived
data offset for the `buffer == (char*)-1` sentinel or reads exactly the caller's
requested byte count into the supplied/allocated buffer. The filesystem fallback
keeps the native `get_stream_length_preserve_position` call even though this
fixed-size variant ignores the returned length.

Focused matcher result: 81.05%, 192 candidate instructions versus 188 target
instructions, 9-instruction prefix, and 32 clean masked operands.

Known residuals:

- native coalesces `_getcwd` stack cleanup into the following report call,
  while this C++ scratch emits one local `add esp` cleanup;
- the native loop exits as `jl scan; jmp filesystem_fallback`, while this
  scratch emits the equivalent inverted test plus explicit jump.

2026-06-21 archive cursor pass: spelling the compare loop as
`while (*archive_cursor != 0)` with `archive_char` declared inside the body
improves focused Wibo from `81.05%` to `85.26%`, preserving `192/188`
candidate/target instructions and the `32 ok / 0 unresolved / 0 mismatch`
masked audit. This recovers the native `edx` archive path cursor and `cl`
current archive byte lanes. Lowercase-fold spellings (`-= 32`, hex constants,
explicit signed char) were codegen-neutral and still emit `add al, 0xe0`
instead of native `sub al, 0x20`; unsigned/int byte lanes regress by growing the
frame or changing the compare loop. The same direct-cursor idiom regresses the
variable-size sibling `load_file_bytes_from_archive_or_fs` to `61.39%`, so keep
that scratch's broader control-flow shape separate.

2026-07-09 shape campaign: goto-scan loop form is codegen-neutral at 85.26%.
Typed `ArchiveEntry*` cursor regresses to 53.26% with three masked mismatches.
Retain the `char**` entry-path walk.

2026-07-12 archive data-offset and stream-position ownership:

- The sentinel, seek target, and XOR seed are all the selected 12-byte
  `ArchiveEntry::data_offset`; raw base-plus-offset expressions are replaced by
  that typed owner without caching an entry pointer or disturbing the proven
  `char**` scan cursor.
- Both archive read branches save `ftell(g_archive_file)` before constructing
  the relative `fseek`. This recovers native's stream-position lifetime and
  prevents VC6 from pre-pushing `SEEK_CUR` while evaluating the nested call.
- Focused Wibo improves from 85.26% to 92.84% (189/188 instructions, 9/188
  prefix, 32 clean masks, no unresolved operands or mismatches). Both archive
  buffer paths now normalize identically; the remaining extra instruction is
  the `_getcwd` cleanup noted above, alongside the established ASCII-fold and
  loop-layout encodings.
