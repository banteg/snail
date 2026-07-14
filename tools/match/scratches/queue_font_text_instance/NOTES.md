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
- Appends a text entry (`flags | 1`) into the shared `cFontPrintBuffer` array.
- Stores font id (`+0x3c`), scale (`+0x40`), x/y (`+0x04/+0x08`), horizontal
  alignment (`+0x48`), anchor x (`+0x4c`), text-wave amplitude (`+0x34`), and
  text-wave enable byte (`+0x38`).
- Copies the input text into `g_font_text_buffer` through `g_font_text_cursor`,
  capped at `0x7fe` bytes before forcing a terminator and advancing the cursor.

2026-06-17 cleanup: the queue writes now use the shared `cFontPrintBuffer` fields
instead of re-spelling the same offsets through local byte-pointer casts.

2026-06-21 text-copy owner pass: focused Wibo is now proof-grade at 100.00%,
73/73 instructions, full prefix, with 24 clean masked operands. Rewriting the
copy loop from `if (*text) do { ... } while (*text)` to a plain
`while (*source != '\0')` over a `register char* source = text` local keeps the
source pointer in `eax`, lets the buffer-bound check use `edx`, and confines
the saved `esi` lifetime to the `Color4f` aggregate copy like native. The plain
`while (*text)` spelling improved to 75.68% but still saved `esi` across the
whole function; a `for` update was codegen-neutral with that shape, while an
explicit `goto` loop regressed to the old duplicated-loop family.

## 2026-07-14 fixed text and queue bank extents

`g_font_text_buffer` starts at `0x753ce8` and ends exactly at the
`g_font_queue` base `0x7544e8`, proving its `0x800`-byte capacity. The 1024
`0x84`-byte queue entries then end exactly at `g_font3d_bods` (`0x7754e8`).
The producer now derives both its queue-full test and its two-byte
terminator/advance reserve from those shared capacities.

The exact function remains byte-identical (`73/73`, 24 clean operands), with
normalized candidate hash
`8259fdafd19a39e9657714750580a1474f2bc296f9b84087f797edf5c14597d7`.
