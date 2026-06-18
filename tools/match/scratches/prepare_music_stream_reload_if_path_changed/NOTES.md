# prepare_music_stream_reload_if_path_changed @ 0x4497e0

Small music-cache gate used by `cache_music_file`.

- Focused Wibo result: 2026-06-18, 100.00%, 19/19 instructions, masked
  operands 3 ok.
- If a stream is active and the requested path matches `g_cached_music_path`,
  returns 0 so the caller can reuse the cached stream/bytes.
- If the path changed, stops the current stream and returns 1 to request reload.
