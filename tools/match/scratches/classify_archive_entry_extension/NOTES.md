# classify_archive_entry_extension

- Rebuild helper used while converting `SnailMail.dam` into `SnailMail.dat`.
- Copies the entry name stem before the first dot into the caller buffer.
- Returns `1` for uppercase `TGA`, `2` for uppercase `WAV`, `3` for uppercase
  `MP3`, and `0` for anything else or an entry without an extension.
- `rebuild_game_archive_if_needed` only special-cases the `TGA` class: it writes
  the archived bytes to `0.png`, reloads them through the image path, and emits
  a TGA-style record in the rebuilt archive. The other classes currently fall
  through to the byte-copy path.
- `/Os`-style codegen naturally gives the native opening allocation
  (`eax` input cursor, `edx` output cursor, `cl` byte), but it also emits a
  compact loop/tail-return shape that does not match native. Keep the default
  compiler flags unless a source-shape explanation accounts for both halves.

2026-06-20 larger-helper pass: rewriting the function to the IDA-style
`char* cursor` / direct `stem_out++` loop was score-neutral once the native
`*++cursor` extension shape was restored (26.37%), and the no-increment variant
only reached 26.67% while moving the tail away from native offsets. The raw
`unsigned char*` source remains clearer until a real cursor-register owner lead
appears.
