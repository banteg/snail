# ensure_music_stream_from_path @ 0x449720

First scratch for opening or reusing a filesystem-backed music stream.

- If the backend already has an active stream and the requested path matches
  `g_cached_music_path`, returns without reloading.
- Otherwise stops the current stream, copies the requested path into
  `g_cached_music_path`, opens it with `BASS_StreamCreateFile(mem=0, ...)`, and
  starts playback with flag `4` when `play_mode` is nonzero.
- Focused Wibo result: 2026-06-18, 100.00%, 70/70 instructions, masked
  operands 14 ok.

Source-shape note:

- Native shares one bottom `"Music Play Memory Failed %s"` error tail for both
  short paths and failed stream creation. Spelling those checks as early
  returns regressed to 80.27%; the `if (path_length > 4) { ... if (stream !=
  0) ... } return report_errorf(...)` shape is the real branch layout.
