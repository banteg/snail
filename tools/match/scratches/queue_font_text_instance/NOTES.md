# queue_font_text_instance

Initial scratch for the queued text producer at `0x44a790`.

Wibo result: 61.84%, 73 target instructions versus 79 candidate instructions,
masked operands 19 ok. The queue entry writes are pinned; remaining residual is
register ownership and return-label layout in the text-copy loop. Native keeps
the source pointer in `eax`, uses scratch `edx` for the buffer-bound check, and
only saves `esi` around the `Color4f` copy.

Recovered relationships:

- Uses the same `g_render_queue_active` gate and `g_font_queue_count` maximum
  as the queued quad helpers.
- Appends a text entry (`flags | 1`) into the shared `FontQueueEntry` array.
- Stores font id (`+0x3c`), scale (`+0x40`), x/y (`+0x04/+0x08`), horizontal
  alignment (`+0x48`), anchor x (`+0x4c`), text-wave amplitude (`+0x34`), and
  text-wave enable byte (`+0x38`).
- Copies the input text into `g_font_text_buffer` through `g_font_text_cursor`,
  capped at `0x7fe` bytes before forcing a terminator and advancing the cursor.

2026-06-17 cleanup: the queue writes now use the shared `FontQueueEntry` fields
instead of re-spelling the same offsets through local byte-pointer casts.
