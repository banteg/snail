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
