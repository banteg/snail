# play_music_stream_from_bytes @ 0x449820

First tracked scratch for opening an archive-backed music stream.

- Copies the source path into `g_cached_music_path`.
- Stops and clears any active stream before opening the new memory stream.
- Rejects short paths with the native `Music Play Memory Failed %s` report.
- Uses `BASS_StreamCreateFile(mem=1, ...)` and starts playback with flag `4`
  when `play_mode` is nonzero.
- Focused Wibo result: 2026-06-18, 100.00%, 68/68 instructions, masked
  operands 11 ok.

Source-shape note:

- Like `ensure_music_stream_from_path`, native shares one bottom error tail for
  both the short-path guard and failed stream creation. Early returns or a
  `goto failed` spelling keep semantics but regress the branch layout; the
  nested success path followed by one final `report_errorf` matches.
