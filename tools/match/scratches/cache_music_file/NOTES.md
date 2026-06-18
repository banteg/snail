# cache_music_file @ 0x432d50

Music stream cache entry point for archive-backed and filesystem-backed music.

- Focused Wibo result: 2026-06-18, 100.00%, 42/42 instructions, masked
  operands 11 ok.
- All nine native callsites push `(path, 0, g_blank_text)` and clean 12 bytes
  after the call; the helper only consumes `path`, so the remaining two source
  parameters are unused/default slots rather than separate behavior.
- Falls back to `AudioBackend::ensure_music_stream_from_path` when no archive
  index is loaded.
- When archive data is available, asks the backend whether the requested path
  needs a reload, reads bytes into `g_music_memory_buffer`, checks the native
  `0x64000` buffer limit, then starts playback from memory.
